/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_ROBET_DEF_DEF_H_
#define CODE_ROBET_DEF_DEF_H_

//∫Í∂®“Â
#define CH0_TIME_MS 2
#define CH1_TIME_US 10

#define   BEE_ON     gpio_set_level(P33_10, 1);
#define   BEE_OFF    gpio_set_level(P33_10, 0);

#define   RED_ON        gpio_set_level(P02_4, 0);
#define   RED_OFF       gpio_set_level(P02_4, 1);
#define   YELLOW_ON     gpio_set_level(P02_5, 0);
#define   YELLOW_OFF    gpio_set_level(P02_5, 1);
#define   GREEN_ON      gpio_set_level(P02_7, 0);
#define   GREEN_OFF     gpio_set_level(P02_7, 1);

typedef enum
{
    go = 0,
    imgshow_mode,
    paramshow_mode,
    paramchange_mode,
    nav_mode
} Mode_t;

typedef enum
{
    flag_zero = 0,

    mt9v034_flag,
    binary_flag,
    visualize_flag,

    beacon_info_flag,
    balance_info_flag,
    move_info_flag,

    blance_change_flag,
    move_change_flag,
    beacon_change_flag

} mode_flag_t;

typedef struct
{
    Mode_t        mode;
    mode_flag_t   mode_flag;
    uint16        board_num;
    int16         target_speed;
    int16         quick_speed;
    int16         slow_speed;
    int16         normal_speed;
    float         now_speed;
    int           yaw_bias;
    float         battery_voltage;
    float         run_time;
} robot_state_t;

extern uint8_t delay_flag;
extern uint8_t delay_final;

void BEE_task(uint32 time);
void Light_task(void);
void delay_task(uint32 time);




#endif /* CODE_ROBET_DEF_DEF_H_ */
