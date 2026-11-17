/*
 * pid.c
 *
 *  Created on: Apr 13, 2026
 *      Author: 86195
 */
#include "pid.h"

void PID_Init(PID_TypeDef *pid, float p, float i, float d, float min, float max)
{
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;
	pid->out_min = min;
	pid->out_max = max;
	pid->err = 0;
	pid->err_last = 0;
	pid->err_sum = 0;
	pid->output = 0;
}

float PID_Calc(PID_TypeDef *pid, float target, float feedback)
{
	pid->set = target;
	pid->actual = feedback;

	pid->err = pid->set - pid->actual;
	pid->err_sum += pid->err;

	// 积分限幅
	if(pid->Ki != 0)
	{
		if(pid->err_sum > pid->out_max / pid->Ki) pid->err_sum = pid->out_max / pid->Ki;
		if(pid->err_sum < pid->out_min / pid->Ki) pid->err_sum = pid->out_min / pid->Ki;
	}

	// 位置式PID
	pid->output = pid->Kp * pid->err
				+ pid->Ki * pid->err_sum
				+ pid->Kd * (pid->err - pid->err_last);

	// 输出限幅
	if(pid->output > pid->out_max) pid->output = pid->out_max;
	if(pid->output < pid->out_min) pid->output = pid->out_min;

	pid->err_last = pid->err;
	return pid->output;
}

// 轮子速度环独立位置式PID
float pid_whool(float target,float current){
	float kp = 19,ki = 14,kd=1;
	static float integral = 0,last_error = 0;
	float error = target-current;
	integral =integral + error;
	if(integral>100){
		integral=100;
	}
	if(integral<-100){
		integral=-100;
	}
	float derivative = error -last_error;
	last_error =error;
	float out = (kp*error)+(ki*integral)+(kd*derivative);
	if(out>999){
	    out=999;
	}
	if(out<0){
	    out=0;
	}
	return out;
}
