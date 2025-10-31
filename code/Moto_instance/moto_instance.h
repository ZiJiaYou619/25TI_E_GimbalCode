/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_MOTO_INSTANCE_MOTO_INSTANCE_H_
#define CODE_MOTO_INSTANCE_MOTO_INSTANCE_H_

#include "zf_common_headfile.h"

typedef struct {
    PIDInstance outer_params;  // 外层PID参数
    float* outer_current;
    int outer_loop_time;
    float outer_loop_output;
    float middle_position;

    PIDInstance middle_params; // 中层PID参数
    float* middle_current;
    int middle_loop_time;
    float middle_loop_output;

    PIDInstance inner_params;  // 内层PID参数
    float* inner_current;
    int inner_loop_time;
    float inner_loop_output;

    float dynamic_deadzone;//死区补偿量
} Motor_Struct;

typedef struct {
    PID_Init_Config outer_params;  // 外层PID参数
    float *outer_current;
    int outer_loop_time;
    float middle_position;

    PID_Init_Config middle_params;  // 中层PID参数
    float *middle_current;
    int middle_loop_time;

    PID_Init_Config inner_params;  // 内层PID参数
    float *inner_current;
    int inner_loop_time;

    float dynamic_deadzone;//死区补偿量
} Motor_Init_Config;

void Motor_instance_Init(Motor_Struct *motor, Motor_Init_Config *motor_config);
float Motor_Calculate(Motor_Struct *motor);
float Motor_Calculate_turn(Motor_Struct *motor);

#endif /* CODE_MOTO_INSTANCE_MOTO_INSTANCE_H_ */
