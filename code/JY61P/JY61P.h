#ifndef __JY61P_H
#define __JY61P_H

void Serial_JY61P_Zero_Yaw(void);
void UART_JY61P_INST_IRQHandler(void);
void show_imu_data(void);
void jy61p_process_byte(uint8_t uartdata);

extern float Pitch,Roll,Yaw;
extern float Pitch_gyro,Roll_gyro,Yaw_gyro;
#endif
