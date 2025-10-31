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

volatile uint32_t soft_dwt_counter_ms = 0;
volatile uint32_t soft_dwt_counter_us = 0;

void SoftDWT_Init(void)
{
    soft_dwt_counter_ms = 0;
    soft_dwt_counter_us = 0;
}

uint32 SoftDWT_GetCycle_us(void)
{
    uint32_t counter = soft_dwt_counter_us;
    SoftDWT_Clear_us();
    return counter;
}

uint32 SoftDWT_GetNow_us(void)
{
    uint32_t counter = soft_dwt_counter_us;
    return counter;
}

void SoftDWT_Clear_us(void)
{
    soft_dwt_counter_us = 0;
}

void SoftDWT_IRQHandler_us(void)
{
    soft_dwt_counter_us += CH1_TIME_US;
}


uint32 SoftDWT_GetCycle_ms(void)
{
    return soft_dwt_counter_ms;
}

void SoftDWT_Clear_ms(void)
{
    soft_dwt_counter_ms = 0;
}

void SoftDWT_IRQHandler_ms(void)
{
    soft_dwt_counter_ms += CH0_TIME_MS;
}
