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

//float Kp_x = 5.5,Kp_y = 7.5;

void BEE_task(uint32 time)
{
    uint32 now_time;
    uint8 on_flag = 0;
    if(gpio_get_level(P33_10) == 1 && on_flag==0)
    {
        on_flag = 1;
        now_time = SoftDWT_GetCycle_ms();
    }
    if(on_flag)
    {
        if(SoftDWT_GetCycle_ms() - now_time > time)
            BEE_OFF;
    }
}
uint8_t delay_flag = 0;
uint8_t delay_final = 0;
void delay_task(uint32 time)
{
    uint32 now_time;
    uint8 on_flag = 0;
    if(on_flag==0&&delay_flag == 1)
    {
        on_flag = 1;
        delay_final = 0;
        now_time = SoftDWT_GetCycle_us();
    }
    if(on_flag)
    {
        if(SoftDWT_GetCycle_us() - now_time > time)
        {
            delay_final = 1;
            delay_flag = 0;
        }

    }
}

void Light_task(void)
{
    RED_ON;
    GREEN_ON;
    YELLOW_ON;
}
