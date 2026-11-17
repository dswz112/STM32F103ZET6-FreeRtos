/*
 * wheel.c
 *
 *  Created on: Dec 2, 2025
 *      Author: 86195
 */
/* USER CODE BEGIN PTD */
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "wheel.h"
//#define LF_WHEEL_ENA_ON() HAL_GPIO_WritePin(GPIOG,ENA_L_Pin, GPIO_PIN_SET)
//#define LF_WHEEL_ENA_OFF() HAL_GPIO_WritePin(GPIOG,ENA_L_Pin, GPIO_PIN_RESET)//PG11引脚
//#define LF_WHEEL_ENA_ON()   __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,999);
//#define LF_WHEEL_ENA_ON1()   __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,500);
//#define LF_WHEEL_ENA_ON2()   __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,0);
//pc9引脚
#define LF_WHEEL_IN1_ON()  HAL_GPIO_WritePin(GPIOB,IN1_L_Pin, GPIO_PIN_SET)
#define LF_WHEEL_IN1_OFF() HAL_GPIO_WritePin(GPIOB,IN1_L_Pin, GPIO_PIN_RESET)
//PG13引脚
#define LF_WHEEL_IN2_ON() HAL_GPIO_WritePin(GPIOB,IN2_L_Pin, GPIO_PIN_SET)
#define LF_WHEEL_IN2_OFF() HAL_GPIO_WritePin(GPIOB,IN2_L_Pin, GPIO_PIN_RESET)
//PB6引脚
//#define LB_WHEEL_ENB_ON() HAL_GPIO_WritePin(GPIOD,ENB_L_Pin, GPIO_PIN_SET)
//#define LB_WHEEL_ENB_OFF() HAL_GPIO_WritePin(GPIOD,ENB_L_Pin, GPIO_PIN_RESET)//PD4引脚
//#define LB_WHEEL_ENB_ON()  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,500);
//#define LB_WHEEL_ENB_ON1() __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,500);
//#define LB_WHEEL_ENB_ON2() __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,0);
//PC7引脚
#define LB_WHEEL_IN3_ON() HAL_GPIO_WritePin(GPIOG,IN3_L_Pin, GPIO_PIN_SET)
#define LB_WHEEL_IN3_OFF() HAL_GPIO_WritePin(GPIOG,IN3_L_Pin, GPIO_PIN_RESET)
//PE9引脚
#define LB_WHEEL_IN4_ON() HAL_GPIO_WritePin(GPIOD,IN4_L_Pin, GPIO_PIN_SET)
#define LB_WHEEL_IN4_OFF() HAL_GPIO_WritePin(GPIOD,IN4_L_Pin, GPIO_PIN_RESET)
//PB6引脚
//#define RF_WHEEL_ENA_ON() HAL_GPIO_WritePin(GPIOG,ENA_R_Pin, GPIO_PIN_SET)
//#define RF_WHEEL_ENA_OFF() HAL_GPIO_WritePin(GPIOG,ENA_R_Pin, GPIO_PIN_RESET)PG10引脚
//#define RF_WHEEL_ENA_ON() __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,999)
//#define RF_WHEEL_ENA_ON1() __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,500)
//#define RF_WHEEL_ENA_ON2() __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,0)
//PC8引脚
#define RF_WHEEL_IN1_ON() HAL_GPIO_WritePin(GPIOG,IN1_R_Pin, GPIO_PIN_SET)
#define RF_WHEEL_IN1_OFF() HAL_GPIO_WritePin(GPIOG,IN1_R_Pin, GPIO_PIN_RESET)
//PG12引脚
#define RF_WHEEL_IN2_ON() HAL_GPIO_WritePin(GPIOG,IN2_R_Pin, GPIO_PIN_SET)
#define RF_WHEEL_IN2_OFF() HAL_GPIO_WritePin(GPIOG,IN2_R_Pin, GPIO_PIN_RESET)
//PG14引脚
//#define RB_WHEEL_ENB_ON() HAL_GPIO_WritePin(GPIOB,ENB_R_Pin, GPIO_PIN_SET)
//#define RB_WHEEL_ENB_OFF() HAL_GPIO_WritePin(GPIOB,ENB_R_Pin, GPIO_PIN_RESET)
//#define RB_WHEEL_ENB_ON()   __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,999)
//#define RB_WHEEL_ENB_ON1()  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,500)
//#define RB_WHEEL_ENB_ON2()  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,0)
//PB3引脚
#define RB_WHEEL_IN3_ON() HAL_GPIO_WritePin(GPIOG,IN3_R_Pin, GPIO_PIN_SET)
#define RB_WHEEL_IN3_OFF() HAL_GPIO_WritePin(GPIOG,IN3_R_Pin, GPIO_PIN_RESET)
//PB5引脚改成PG10
#define RB_WHEEL_IN4_ON() HAL_GPIO_WritePin(GPIOB,IN4_R_Pin, GPIO_PIN_SET)
#define RB_WHEEL_IN4_OFF() HAL_GPIO_WritePin(GPIOB,IN4_R_Pin, GPIO_PIN_RESET)
//PB7引脚

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void down(float speed){
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
//	RF_WHEEL_ENA_ON();
//	RB_WHEEL_ENB_ON();
    //左侧前轮
	LF_WHEEL_IN1_OFF();
	LF_WHEEL_IN2_ON();
    //左侧后轮
	LB_WHEEL_IN4_ON();
	LB_WHEEL_IN3_OFF();
    //右侧前轮
	RF_WHEEL_IN1_ON();
	RF_WHEEL_IN2_OFF();
    //右侧后轮
	RB_WHEEL_IN4_OFF();
	RB_WHEEL_IN3_ON();



}
void forward(float speed){
//	    LF_WHEEL_ENA_ON();
//		LB_WHEEL_ENB_ON();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
//		RF_WHEEL_ENA_ON();
//		RB_WHEEL_ENB_ON();
	    //左侧前轮
		LF_WHEEL_IN1_ON();
		LF_WHEEL_IN2_OFF();
	    //左侧后轮
		LB_WHEEL_IN4_OFF();
		LB_WHEEL_IN3_ON();
	    //右侧前轮
		RF_WHEEL_IN1_OFF();
		RF_WHEEL_IN2_ON();
	    //右侧后轮
		RB_WHEEL_IN4_ON();
		RB_WHEEL_IN3_OFF();
}
void down1(){
//	    LF_WHEEL_ENA_ON();
//		LB_WHEEL_ENB_ON();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,700);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,700);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,700);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,700);
//		RF_WHEEL_ENA_ON();
//		RB_WHEEL_ENB_ON();
	    //左侧前轮
		LF_WHEEL_IN1_ON();
		LF_WHEEL_IN2_OFF();
	    //左侧后轮
		LB_WHEEL_IN4_OFF();
		LB_WHEEL_IN3_ON();
	    //右侧前轮
		RF_WHEEL_IN1_OFF();
		RF_WHEEL_IN2_ON();
	    //右侧后轮
		RB_WHEEL_IN4_ON();
		RB_WHEEL_IN3_OFF();
}

void stop(){
//      LF_WHEEL_ENA_ON2();
//	    LB_WHEEL_ENB_ON2();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,0);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,0);
//	    RF_WHEEL_ENA_ON2();
//	    RB_WHEEL_ENB_ON2();
                //左侧前轮子
		LF_WHEEL_IN1_OFF();
		LF_WHEEL_IN2_OFF();
			    //左侧后轮
		LB_WHEEL_IN4_OFF();
		LB_WHEEL_IN3_OFF();
			    //右侧前轮
		RF_WHEEL_IN1_OFF();
		RF_WHEEL_IN2_OFF();
			    //右侧后轮
		RB_WHEEL_IN4_OFF();
		RB_WHEEL_IN3_OFF();

}

void right(float speed){
//	    LF_WHEEL_ENA_ON1();
//		LB_WHEEL_ENB_ON1();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
//		RF_WHEEL_ENA_ON();
//		RB_WHEEL_ENB_ON();
	    //左侧前轮
		LF_WHEEL_IN1_ON();
		LF_WHEEL_IN2_OFF();
	    //左侧后轮
		LB_WHEEL_IN4_OFF();
		LB_WHEEL_IN3_ON();
	    //右侧前轮
		RF_WHEEL_IN1_ON();
		RF_WHEEL_IN2_OFF();
	    //右侧后轮
		RB_WHEEL_IN4_OFF();
		RB_WHEEL_IN3_ON();


}
void right_ON1(float speed){
//	    LF_WHEEL_ENA_ON();
//		LB_WHEEL_ENB_ON();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
//		RF_WHEEL_ENA_ON();
//		RB_WHEEL_ENB_ON();
	    //左侧前轮--向前
		LF_WHEEL_IN1_OFF();
		LF_WHEEL_IN2_ON();
//	    //左侧后轮--向后
		LB_WHEEL_IN3_ON();
		LB_WHEEL_IN4_OFF();
//	    //右侧前轮--向后
		RF_WHEEL_IN1_OFF();
		RF_WHEEL_IN2_ON();
//	    //右侧后轮--向前
		RB_WHEEL_IN3_ON();
		RB_WHEEL_IN4_OFF();



}
void left_ON1(float speed){
	//	    LF_WHEEL_ENA_ON();
	//		LB_WHEEL_ENB_ON();
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
	//		RF_WHEEL_ENA_ON();
	//		RB_WHEEL_ENB_ON();
		    //左侧前轮--向前
			LF_WHEEL_IN1_ON();
			LF_WHEEL_IN2_OFF();
	//	    //左侧后轮--向后
			LB_WHEEL_IN3_OFF();
			LB_WHEEL_IN4_ON();
	//	    //右侧前轮--向后
			RF_WHEEL_IN1_ON();
			RF_WHEEL_IN2_OFF();
	//	    //右侧后轮--向前
			RB_WHEEL_IN3_OFF();
			RB_WHEEL_IN4_ON();

}
void left(float speed){
//	        LF_WHEEL_ENA_ON();
//			LB_WHEEL_ENB_ON();
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2,speed);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,speed);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,speed);
//			RF_WHEEL_ENA_ON1();
//			RB_WHEEL_ENB_ON1();
		    //左侧前轮
			LF_WHEEL_IN1_OFF();
			LF_WHEEL_IN2_ON();
		    //左侧后轮
			LB_WHEEL_IN4_ON();
			LB_WHEEL_IN3_OFF();
		    //右侧前轮
			RF_WHEEL_IN1_OFF();
			RF_WHEEL_IN2_ON();
		    //右侧后轮
			RB_WHEEL_IN4_ON();
			RB_WHEEL_IN3_OFF();
}

