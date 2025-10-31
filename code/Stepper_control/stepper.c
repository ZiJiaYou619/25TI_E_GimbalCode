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
#include "zf_driver_gpio.h"

stepper_motor_t motor_L = {
    .pul_pin = STEPPER_PUL_PIN_L,
    .dir_pin = STEPPER_DIR_PIN_L,
    .speed = 1000,             // Ä¬ÈÏËÙ¶È 1000Hz
    .steps_remaining = 0
};

stepper_motor_t motor_H = {
    .pul_pin = STEPPER_PUL_PIN_H,
    .dir_pin = STEPPER_DIR_PIN_H,
    .speed = 1000,
    .steps_remaining = 0
};

void stepper_init(void)
{
    gpio_init(motor_L.dir_pin, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(STEPPER_EN_PIN_L,GPO,GPIO_HIGH,GPO_PUSH_PULL);

    gpio_init(motor_H.dir_pin, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(STEPPER_EN_PIN_H,GPO,GPIO_HIGH,GPO_PUSH_PULL);

    pwm_init(motor_L.pul_pin, motor_L.speed, 5000);
    pwm_init(motor_H.pul_pin, motor_H.speed, 5000);
//    pwm_init(STEPPER_PUL_PIN_L, 0, 0);
//    pwm_init(STEPPER_PUL_PIN_H, 0, 0);
}

void stepper_set_direction(uint8_t direction_L,uint8_t direction_H)
{
    gpio_set_level(motor_L.dir_pin, direction_L);
    gpio_set_level(motor_H.dir_pin, direction_H);
}

void stepper_set_speed(uint32_t speed_hz_L,uint32_t speed_hz_H)
{
    motor_L.speed = speed_hz_L;
    motor_H.speed = speed_hz_H;

    if (motor_L.steps_remaining > 0) {
        pwm_init(motor_L.pul_pin, motor_L.speed, PWM_DUTY_MAX / 2);
    }
    if (motor_H.steps_remaining > 0) {
        pwm_init(motor_H.pul_pin, motor_H.speed, PWM_DUTY_MAX / 2);
    }
}

void stepper_move_steps(uint32_t steps_L, uint8_t direction_L,
                        uint32_t steps_H, uint8_t direction_H)
{
    if (steps_L == 0 && steps_H == 0) return;

    stepper_set_direction(direction_L,direction_H);

    motor_L.steps_remaining = steps_L;
    motor_H.steps_remaining = steps_H;

    if (steps_L > 0)
        pwm_init(motor_L.pul_pin, motor_L.speed, PWM_DUTY_MAX / 2);

    if (steps_H > 0)
        pwm_init(motor_H.pul_pin, motor_H.speed, PWM_DUTY_MAX / 2);
}

void stepper_stop(void)
{
    pwm_all_channel_close();
    motor_L.steps_remaining = 0;
    motor_H.steps_remaining = 0;
}

void stepper_move_by_angle(float angle_L_deg, float angle_H_deg)
{
    int32_t steps_L = (int32_t)(angle_L_deg * (400.0f / 45.0f));
    int32_t steps_H = (int32_t)(angle_H_deg * (400.0f / 45.0f));

    uint8_t dir_L = (steps_L >= 0) ? 0 : 1;
    uint8_t dir_H = (steps_H >= 0) ? 0 : 1;

    stepper_move_steps((uint32_t)abs(steps_L), dir_L,
                       (uint32_t)abs(steps_H), dir_H);
}

void stepper_update_handler(void)
{
    if (motor_L.steps_remaining > 0) {
        motor_L.steps_remaining--;
        if (motor_L.steps_remaining == 0) {
            pwm_set_duty(motor_L.pul_pin, 0);
        }
    }

    if (motor_H.steps_remaining > 0) {
        motor_H.steps_remaining--;
        if (motor_H.steps_remaining == 0) {
            pwm_set_duty(motor_H.pul_pin, 0);
        }
    }
}

