/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef __SOFT_DWT_H
#define __SOFT_DWT_H

void SoftDWT_Init(void);
uint32 SoftDWT_GetCycle_us(void);
void SoftDWT_Clear_us(void);
void SoftDWT_IRQHandler_us(void); 

uint32 SoftDWT_GetCycle_ms(void);
void SoftDWT_Clear_ms(void);
void SoftDWT_IRQHandler_ms(void);
uint32 SoftDWT_GetNow_us(void);

#endif
