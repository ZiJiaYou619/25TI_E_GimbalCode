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

void GPIO_init(void)
{
    gpio_init(LED1, GPO, GPIO_LOW, GPO_PUSH_PULL);          // ��ʼ�� LED1 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED2 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    gpio_init(LED3, GPO, GPIO_LOW, GPO_PUSH_PULL);          // ��ʼ�� LED3 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    gpio_init(LED4, GPO, GPIO_HIGH, GPO_PUSH_PULL);         // ��ʼ�� LED4 ��� Ĭ�ϸߵ�ƽ �������ģʽ
    gpio_init(KEY1, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY2, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY2 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY3, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY3 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(KEY4, GPI, GPIO_HIGH, GPI_PULL_UP);           // ��ʼ�� KEY4 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);        // ��ʼ�� SWITCH1 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);        // ��ʼ�� SWITCH2 ���� Ĭ�ϸߵ�ƽ ��������
    gpio_init(BEE, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(P02_4, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(P02_5, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(P02_7, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(P20_10,GPO, GPIO_LOW,GPO_PUSH_PULL);
    gpio_init(P20_10,GPO, GPIO_LOW,GPO_PUSH_PULL);

    //22.0 22.1 22.3
    gpio_init(R_1, GPI, GPIO_LOW, GPI_PULL_DOWN);
    gpio_init(R_2,GPI, GPIO_LOW,GPI_PULL_DOWN);
    gpio_init(R_3,GPI, GPIO_LOW,GPI_PULL_DOWN);
}


