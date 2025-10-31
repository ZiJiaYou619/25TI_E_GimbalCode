/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_STEPPER_CONTROL_FOLLOW_CONTROL_H_
#define CODE_STEPPER_CONTROL_FOLLOW_CONTROL_H_

void steps_Pitch_init(void);
void steps_motor_set_freq(int freq_L, int freq_H);
void steps_Pitch_task(void);
void stepper_set_direction_H(uint8_t dir);
void stepper_set_direction_L(uint8_t dir);
void steps_Yaw_task(void);
void steps_Yaw_init(void);
void steps_Yaw_bias_init(void);
void steps_Pitch_bias_init(void);
void steps_Pitch_task_basic(void);
void steps_Yaw_task_basic(void);

extern float Steps_Freq_L,Steps_Freq_H;
extern float Steps_Freq_LB,Steps_Freq_HB;

extern Motor_Struct Steps_Pitch;
extern Motor_Struct Steps_Yaw;
extern Motor_Struct Steps_Pitch_basic;
extern Motor_Struct Steps_Yaw_basic;

#endif /* CODE_STEPPER_CONTROL_FOLLOW_CONTROL_H_ */
