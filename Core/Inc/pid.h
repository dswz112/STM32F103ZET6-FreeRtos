/*
 * pid.h
 *
 *  Created on: Apr 13, 2026
 *      Author: 86195
 */

#ifndef INC_PID_H_
#define INC_PID_H_

float pid_whool(float target,float current);
typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float set;
	float actual;
	float err;
	float err_last;
	float err_sum;
	float output;
	float out_min;
	float out_max;
} PID_TypeDef;

void PID_Init(PID_TypeDef *pid, float p, float i, float d, float min, float max);
float PID_Calc(PID_TypeDef *pid, float target, float feedback);

#endif /* INC_PID_H_ */
