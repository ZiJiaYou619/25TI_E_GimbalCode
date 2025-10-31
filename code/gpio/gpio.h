/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef _BSP_GPIO_h_
#define _BSP_GPIO_h_

#define LED1                    (P20_9)
#define LED2                    (P20_8)
#define LED3                    (P21_5)
#define LED4                    (P21_4)
#define KEY1                    (P20_6)
#define KEY2                    (P20_7)
#define KEY3                    (P11_2)
#define KEY4                    (P11_3)
#define SWITCH1                 (P33_11)
#define SWITCH2                 (P33_12)
#define BEE                     (P33_10)
#define R_1                     P22_0 //zong
#define R_2                     P22_3 //hong
#define R_3                     P22_1 //cheng

void GPIO_init(void);

#endif
