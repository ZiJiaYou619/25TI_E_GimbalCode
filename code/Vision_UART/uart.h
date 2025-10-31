/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_VISION_UART_UART_H_
#define CODE_VISION_UART_UART_H_

#define UART_INDEX              (UART_2)                           // 默认 UART_0
#define UART_BAUDRATE           (115200)                           // 默认 115200
#define UART_TX_PIN             (UART2_TX_P10_5  )
#define UART_RX_PIN             (UART2_RX_P10_6  )

#define HEADER1   0x2C
#define HEADER2   0x12
#define RECV_END1 0x5A
#define RECV_END2 0x2C

#define laser_bias 5

typedef enum {
    RX_STATE_IDLE = 0,
    RX_STATE_HEADER1,
    RX_STATE_HEADER2,
    RX_STATE_RECEIVING,
    RX_STATE_COMPLETE
} RxState_v;

typedef struct {
    uint8_t header1;
    uint8_t header2;

    uint8_t data[8];      // 实际数据部分

    uint8_t comm_end1;
    uint8_t comm_end2;
} __attribute__((packed))Recvpacket_t;

typedef struct {
    uint8_t BXL;
    uint8_t BXH;
    int16_t BX;
    int16_t BY;
    uint8_t BYL;
    uint8_t BYH;
    uint8_t dx;
    uint8_t dxL;
    uint8_t dxH;
} ReceiverData_t;

void UART_init(void);
void uart_rx_interrupt_handler(void);
void Recv_data(uint8 Res);
void uart_show_recv_data(void);
void caculate_data();
void uart_io(void);

extern float Bias_X,Bias_Y;
extern uint8 uart_get_data[64];                                                        // 串口接收数据缓冲区
extern uint8  get_data;                                                                // 接收数据变量
extern ReceiverData_t ReceiverData;
extern uint8 TI_data;
extern uint8 d1;
extern uint8 d2;

#endif /* CODE_VISION_UART_UART_H_ */
