#include "remote.h"
#include "tim.h"  // 引入CubeMX全局TIM4句柄
#include "gpio.h"
// 删除自建 TIM_HandleTypeDef g_tim4_handle;
uint8_t g_remote_sta = 0;
uint32_t g_remote_data = 0;
uint8_t  g_remote_cnt = 0;
#define RDATA  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)
#define REMOTE_ID 0

void remote_init(void)
{
    TIM_IC_InitTypeDef tim_ic_init_handle;
    // 仅配置捕获极性，时基已由MX_TIM4_Init完成
    tim_ic_init_handle.ICPolarity = TIM_ICPOLARITY_RISING;
    tim_ic_init_handle.ICSelection = TIM_ICSELECTION_DIRECTTI;
    tim_ic_init_handle.ICPrescaler = TIM_ICPSC_DIV1;
    tim_ic_init_handle.ICFilter = 0x03; // 和CubeMX滤波参数保持一致
    HAL_TIM_IC_ConfigChannel(&htim4, &tim_ic_init_handle, TIM_CHANNEL_4);
    
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);
}

// 自定义中断处理函数，解决多重定义
void remote_tim4_irq_callback(void)
{
    HAL_TIM_IRQHandler(&htim4);
}
// TIM溢出超时回调，判断一帧红外接收结束
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM4)
    {
        if (g_remote_sta & 0x80)
        {
            g_remote_sta &= ~0X10;
            if ((g_remote_sta & 0X0F) == 0X00)
                g_remote_sta |= 1 << 6;
            if ((g_remote_sta & 0X0F) < 14)
                g_remote_sta++;
            else
            {
                g_remote_sta &= ~(1 << 7);
                g_remote_sta &= 0XF0;
            }
        }
    }
}

// 捕获跳变沿回调，计算高低电平时间，区分引导码/0/1数据位
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM4)
    {
        uint16_t dval;
        if (RDATA)
        {
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);
            __HAL_TIM_SET_COUNTER(&htim4, 0);
            g_remote_sta |= 0X10;
        }
        else
        {
            dval=HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_4);
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_4, TIM_ICPOLARITY_RISING);

            if (g_remote_sta & 0X10)
            {
                if (g_remote_sta & 0X80)
                {
                    if (dval > 300 && dval < 800)
                    {
                        g_remote_data >>= 1;
                        g_remote_data &= ~(0x80000000);
                    }
                    else if (dval > 1400 && dval < 1800)
                    {
                        g_remote_data >>= 1;
                        g_remote_data |= 0x80000000;
                    }
                    else if (dval > 2000 && dval < 3000)
                    {
                        g_remote_cnt++;
                        g_remote_sta &= 0XF0;
                    }
                }
                else if (dval > 4200 && dval < 4700)
                {
                    g_remote_sta |= 1 << 7;
                    g_remote_cnt = 0;
                }
            }
            g_remote_sta&=~(1<<4);
        }
    }
}
uint8_t remote_scan(void)
{
    uint8_t sta = 0;
    uint8_t t1, t2;

    if (g_remote_sta & (1 << 6))    /* 收到一帧完整红外信息 */
    {
        t1 = g_remote_data;                 /* 获取地址 */
        t2 = (g_remote_data >> 8) & 0xff;   /* 地址反码 */

        if ((t1 == (uint8_t)~t2) && t1 == REMOTE_ID)    /* 匹配遥控器ID */
        {
            t1 = (g_remote_data >> 16) & 0xff;
            t2 = (g_remote_data >> 24) & 0xff;

            if (t1 == (uint8_t)~t2)
            {
                sta = t1;           /* 有效按键值 */
            }
        }

        // 关键修复：读取完成直接清除接收完成标志，下次必须等新帧才会再次输出
        g_remote_sta &= ~(1 << 6);
        g_remote_cnt = 0;
    }

    return sta;
}

