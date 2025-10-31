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
#include "zf_driver_pwm.h"
#include "IfxGtm_Atom_Pwm.h"
#include "ifxGtm_PinMap.h"
#include "zf_common_debug.h"

#define STEPS_FREQ_MAX 5000
#define STEPS_FREQ_MIN 50

float Steps_Freq_L,Steps_Freq_H;
float Steps_Freq_LB,Steps_Freq_HB;

float a = 0;

Motor_Struct Steps_Pitch;
Motor_Struct Steps_Yaw;
Motor_Struct Steps_Pitch_basic;
Motor_Struct Steps_Yaw_basic;

void stepper_set_direction_L(uint8_t dir)
{
    gpio_set_level(motor_L.dir_pin, dir);
}

void stepper_set_direction_H(uint8_t dir)
{
    gpio_set_level(motor_H.dir_pin, dir);
}

void steps_motor_set_freq(int freq_L, int freq_H)
{
//    if (abs(freq_L) < STEPS_FREQ_MIN) freq_L = 0;
//    if (abs(freq_H) < STEPS_FREQ_MIN) freq_H = 0;
//
//    if (freq_L > STEPS_FREQ_MAX) freq_L = STEPS_FREQ_MAX;
//    if (freq_L < -STEPS_FREQ_MAX) freq_L = -STEPS_FREQ_MAX;
//    if (freq_H > STEPS_FREQ_MAX) freq_H = STEPS_FREQ_MAX;
//    if (freq_H < -STEPS_FREQ_MAX) freq_H = -STEPS_FREQ_MAX;

    //限幅还没加
    if(freq_L >= 0)
    {
        stepper_set_direction_L(0);
        pwm_init(STEPPER_PUL_PIN_L, freq_L, PWM_DUTY_MAX / 2);
    }
    else
    {
        stepper_set_direction_L(1);
        pwm_init(STEPPER_PUL_PIN_L, -freq_L, PWM_DUTY_MAX / 2);
    }

    if(freq_H >= 0)
    {
        stepper_set_direction_H(0);
        pwm_init(STEPPER_PUL_PIN_H, freq_H, PWM_DUTY_MAX / 2);
    }
    else
    {
        stepper_set_direction_H(1);
        pwm_init(STEPPER_PUL_PIN_H, -freq_H, PWM_DUTY_MAX / 2);
    }
}

void steps_Pitch_init(void)
{
    Motor_Init_Config motor_stepsP_config = {
        .inner_params = {
            .Kp = 4.5f,//6.5
            .Ki = 0.0f,
            .Kd = 0.0f,
            .MaxOut = 20000.0f,
        },
        .inner_current = &Bias_Y,
        .inner_loop_time = 2,
    };
    Motor_instance_Init(&Steps_Pitch, &motor_stepsP_config);
}



//.Kp = 5.6f,
//.Ki = 5.0f,
//.Kd = -36.0f,//-
//.IntegralLimit = 5000.0f,
//.MaxOut = 10000.0f,
//},
//.middle_current = &Bias_X,
//.middle_loop_time = 1,
//
//.inner_params = {
//.Kp = 4.4f,
//.Ki = 0.0f,
//.Kd = -16.0f,

//.Kp = 6.8f,
//.Ki = 0.07f,
//.Kd = -38.0f,//-
//.IntegralLimit = 2500.0f,
//.MaxOut = 10000.0f,
//},
//.middle_current = &Bias_X,
//.middle_loop_time = 1,
//
//.inner_params = {
//.Kp = 3.4f,
//.Ki = 0.0f,
//.Kd = -6.0f,
void steps_Yaw_init(void)
{
    Motor_Init_Config motor_stepsY_config = {
            .middle_params = {
                    .Kp = 6.8f,
                    .Ki = 0.35f,
                    .Kd = -38.0f,//-
                    .IntegralLimit = 2500.0f,
                    .MaxOut = 10000.0f,
                    },
                    .middle_current = &Bias_X,
                    .middle_loop_time = 1,

                    .inner_params = {
                    .Kp = 3.4f,
                    .Ki = 0.0f,
                    .Kd = -6.0f,
               .MaxOut = 10000.0f,
            },
            .inner_current = &Yaw_gyro,
            .inner_loop_time = 1,
    };
    Motor_instance_Init(&Steps_Yaw, &motor_stepsY_config);
}

void steps_Pitch_task(void)
{
    Steps_Freq_L = (int16)Motor_Calculate(&Steps_Pitch);
    steps_motor_set_freq(0,Steps_Freq_L);
}

void steps_Yaw_task(void)
{
    Steps_Freq_H = (int16)Motor_Calculate(&Steps_Yaw);
//    if (Steps_Freq_H > -50 && Steps_Freq_H < 0)
//    {
//        steps_motor_set_freq(-50,0);
//    }
//    else if(Steps_Freq_H > 0 && Steps_Freq_H < 50)
//    {
//        steps_motor_set_freq(50,0);
//    }
//    else
        steps_motor_set_freq(Steps_Freq_H,0);
}

void steps_Pitch_bias_init(void)
{
    Motor_Init_Config motor_stepsPb_config = {
        .inner_params = {
            .Kp = 5.5f,
            .Ki = 0.0f,
            .Kd = 0.0f,
            .MaxOut = 20000.0f,
        },
        .inner_current = &Bias_Y,
        .inner_loop_time = 2,
    };
    Motor_instance_Init(&Steps_Pitch_basic, &motor_stepsPb_config);
}

void steps_Yaw_bias_init(void)
{
    Motor_Init_Config motor_stepsYb_config = {
        .inner_params = {
            .Kp = 10.5f,
            .Ki = 0.0f,
            .Kd = 0.0f,
            .MaxOut = 10000.0f,
        },
        .inner_current = &Bias_X,
        .inner_loop_time = 2,
    };
    Motor_instance_Init(&Steps_Yaw_basic, &motor_stepsYb_config);
}

void steps_Pitch_task_basic(void)
{
    Steps_Freq_LB = (int16)Motor_Calculate(&Steps_Pitch_basic);
    steps_motor_set_freq(0,Steps_Freq_LB);
}

void steps_Yaw_task_basic(void)
{
    Steps_Freq_HB = (int16)Motor_Calculate(&Steps_Yaw_basic);
    steps_motor_set_freq(Steps_Freq_HB,0);
}
