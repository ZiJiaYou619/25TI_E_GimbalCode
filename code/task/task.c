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

uint8 Shoot_flag = 0;

void shoot_laser(void)
{
    if(abs(Bias_Y) <= 1 && abs(Bias_X) <= 1)
    {
        Shoot_flag = 1;
        //BEE_ON;
        gpio_set_level(P20_10,1);
    }
    if(Shoot_flag == 1)
    {
        gpio_set_level(P20_10,1);
    }
}


