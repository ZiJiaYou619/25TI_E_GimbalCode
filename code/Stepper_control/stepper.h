/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_STEPPER_CONTROL_STEPPER_H_
#define CODE_STEPPER_CONTROL_STEPPER_H_

#define STEPPER_EN_PIN_L      P00_9
#define STEPPER_DIR_PIN_L     P33_6
#define STEPPER_PUL_PIN_L     ATOM0_CH4_P02_4

#define STEPPER_EN_PIN_H      P02_8
#define STEPPER_DIR_PIN_H     P33_7
#define STEPPER_PUL_PIN_H     ATOM0_CH5_P02_5

void stepper_init(void);
void stepper_set_direction(uint8_t direction_L,uint8_t direction_H);
void stepper_set_speed(uint32_t speed_hz_L,uint32_t speed_hz_H);
void stepper_move_steps(uint32_t steps_L, uint8_t direction_L,uint32_t steps_H, uint8_t direction_H);
void stepper_stop(void);
void stepper_update_handler(void);
void stepper_move_by_angle(float angle_L_deg, float angle_H_deg);
void stepper_move_once(float angle_L_deg, float angle_H_deg);
void reset_move_flag(void);
void draw_square(void);

// 步进电机控制结构体
typedef struct {
    pwm_channel_enum pul_pin;  // PWM脉冲引脚
    gpio_pin_enum dir_pin;     // 方向控制引脚
    uint32_t speed;            // 当前速度 (Hz)
    uint32_t steps_remaining;  // 剩余步数
} stepper_motor_t;

extern stepper_motor_t motor_L;
extern stepper_motor_t motor_H;

#endif /* CODE_STEPPER_CONTROL_STEPPER_H_ */
