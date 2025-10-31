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

uint8  get_data = 0;                // 用于临时存储每次串口接收到的一个字节数据
Recvpacket_t Recv_packet;           // 用于保存完整接收到的数据包（结构体类型）
uint8_t recv_idx = 0, send_idx = 0; // 接收和发送缓冲区的索引变量
uint8_t rx_buf[256];                // 串口接收缓冲区，最多存储256字节
uint8_t tx_buf[256];                // 串口发送缓冲区，最多存储256字节
ReceiverData_t ReceiverData;
uint8 TI_data;

float Bias_X,Bias_Y;

void UART_init(void)
{
    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);
    uart_rx_interrupt(UART_INDEX, 1);
}

void uart_rx_interrupt_handler (void)
{
    get_data = uart_read_byte(UART_INDEX);
    Recv_data(get_data);
}

void Recv_data(uint8 Res)
{
    static uint8_t RxBuffer[sizeof(Recvpacket_t)];
    static uint8_t RxIndex = 0;
    static uint8_t RxState = 0;

    switch (RxState) {
        case 0:
            if (Res == HEADER1) {
                RxBuffer[RxIndex++] = Res;
                RxState = 1;
            } else {
                RxIndex = 0;
            }
            break;

        case 1:
            if (Res == HEADER2) {
                RxBuffer[RxIndex++] = Res;
                RxState = 2;
            } else {
                RxIndex = 0;
                RxState = 0;
            }
            break;

        case 2:
            RxBuffer[RxIndex++] = Res;
            if (RxIndex >= sizeof(Recvpacket_t)) {
                if (RxBuffer[sizeof(Recvpacket_t) - 2] == RECV_END1 &&
                    RxBuffer[sizeof(Recvpacket_t) - 1] == RECV_END2) {
                    memcpy(&Recv_packet, RxBuffer, sizeof(Recvpacket_t));
                    caculate_data();
                }
                RxIndex = 0;
                RxState = 0;
            }
            break;

        default:
            RxIndex = 0;
            RxState = 0;
            break;
    }
}

void caculate_data()
{
    ReceiverData.BXL = Recv_packet.data[0];
    ReceiverData.BXH = Recv_packet.data[1];
    ReceiverData.BYL = Recv_packet.data[2];
    ReceiverData.BYH = Recv_packet.data[3];
    ReceiverData.dxL = Recv_packet.data[4];
    ReceiverData.dxH = Recv_packet.data[5];

    ReceiverData.BX = (int16_t)(((uint16_t)ReceiverData.BXH << 8) | ReceiverData.BXL) - 1000;
    ReceiverData.BY = (int16_t)(((uint16_t)ReceiverData.BYH << 8) | ReceiverData.BYL) - 1000;
    ReceiverData.dx = (int16_t)(((uint16_t)ReceiverData.dxH << 8) | ReceiverData.dxL) - 1000;
}

void uart_show_recv_data(void)
{   
    ips200_show_string(0, 0, "data[0]:");ips200_show_float(100,0,Recv_packet.data[0],4,2);
    ips200_show_string(0, 15, "data[1]:");ips200_show_float(100,15,Recv_packet.data[1],4,2);
    ips200_show_string(0, 30, "data[2]:");ips200_show_float(100,30,Recv_packet.data[2],4,2);
    ips200_show_string(0, 45, "data[3]:");ips200_show_float(100,45,Recv_packet.data[3],4,2);
    ips200_show_string(0, 60, "data[4]:");ips200_show_int(100,60,Bias_X,4);
    ips200_show_string(0, 75, "data[5]:");ips200_show_int(100,75,Bias_Y,4);
    ips200_show_string(0, 90, "data[6]:");ips200_show_float(100,90,ReceiverData.dx,4,2);
    ips200_show_string(0, 105, "data[7]:");ips200_show_int(100,105,TI_data,4);
}
uint8 d2;
uint8 d1;
void uart_io(void)
{
    TI_data = 0;
    uint8 d0 = gpio_get_level(R_1);
    uint8 d1 = gpio_get_level(R_2);
    uint8 d2 = gpio_get_level(R_3);

    TI_data = d0;
}
