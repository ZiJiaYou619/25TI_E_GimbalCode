/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#include "zf_common_headfile.h"

//保留串级底层初始化PID 该函数跨文件 只能放在这extern
void Motor_instance_Init(Motor_Struct *motor, Motor_Init_Config *motor_config)
{
    PIDInit(&motor->outer_params, &motor_config->outer_params);
    motor->outer_current = motor_config->outer_current;
    motor->outer_loop_time = motor_config->outer_loop_time;

    PIDInit(&motor->middle_params, &motor_config->middle_params);
    motor->middle_current = motor_config->middle_current;
    motor->middle_loop_time = motor_config->middle_loop_time;

    PIDInit(&motor->inner_params, &motor_config->inner_params);
    motor->inner_current = motor_config->inner_current;
    motor->inner_loop_time = motor_config->inner_loop_time;
}

//舵机串级底层 保留串级PID底层计算逻辑 方便后续使用
float Motor_Calculate(Motor_Struct *motor)
{
    if(SoftDWT_GetCycle_ms() % motor->outer_loop_time == 0)
    {
        if(motor->outer_current == NULL)
        {
            motor->outer_loop_output = PIDCalculate(&motor->outer_params, 0, 0);
        }
        else
        {
            motor->outer_loop_output = PIDCalculate(&motor->outer_params, 0, *motor->outer_current);
        }
    }

    if(SoftDWT_GetCycle_ms() % motor->middle_loop_time == 0)
    {
        if(motor->middle_current == NULL)
        {
            motor->middle_loop_output = PIDCalculate(&motor->middle_params,0, 0);
        }
        else
        {
            motor->middle_loop_output = PIDCalculate(&motor->middle_params, 0, *motor->middle_current);
        }
    }

    if(SoftDWT_GetCycle_ms() % motor->inner_loop_time == 0)
    {
        if(motor->inner_current == NULL)
        {
            motor->inner_loop_output = PIDCalculate(&motor->inner_params, motor->middle_loop_output, 0);
        }
        else
        {
            motor->inner_loop_output = PIDCalculate(&motor->inner_params, motor->middle_loop_output, *motor->inner_current);
        }
    }

    return motor->inner_loop_output;
}
