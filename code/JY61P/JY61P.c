#include "zf_common_headfile.h"


uint8_t RollL, RollH, PitchL, PitchH, YawL, YawH, VL, VH, SUM_angle;
float Pitch,Roll,Yaw;
uint8_t WxL,WxH,WyL,WyH,WzL,WzH,VolL,VolH,SUM_gyro;
float Pitch_gyro,Roll_gyro,Yaw_gyro;

#define WAIT_HEADER1 0
#define WAIT_HEADER2 1
#define RECEIVE_ANGLE_DATA 2
#define RECEIVE_W_DATA 3
#define RECEIVE_A_DATA 4

#define RECEIVE_GYRO_DATA 5

uint8_t RxState = WAIT_HEADER1;
uint8_t receivedData[9];
uint8_t dataIndex = 0;

void Serial_JY61P_Zero_Yaw(void){
    uart_write_byte(UART_3,0XFF);
    uart_write_byte(UART_3,0XAA);
    uart_write_byte(UART_3,0X69);
    uart_write_byte(UART_3,0X88);
    uart_write_byte(UART_3,0XB5);
    system_delay_ms(100);
	uart_write_byte(UART_3,0XFF);
	uart_write_byte(UART_3,0XAA);
	uart_write_byte(UART_3,0X01);
	uart_write_byte(UART_3,0X04);
	uart_write_byte(UART_3,0X00);
	system_delay_ms(100);
	uart_write_byte(UART_3,0XFF);
	uart_write_byte(UART_3,0XAA);
	uart_write_byte(UART_3,0X00);
	uart_write_byte(UART_3,0X00);
	uart_write_byte(UART_3,0X00);
}



void show_imu_data(void)
{
    ips200_show_string(0, 0, "Yaw_gyro:");ips200_show_float(100,0,Yaw_gyro,4,2);
    ips200_show_string(0, 15, "Roll:");ips200_show_float(100,15,Roll,4,2);
    ips200_show_string(0, 30, "Yaw:");ips200_show_float(100,30,Yaw,4,2);
}

void jy61p_process_byte(uint8_t uartdata)
{
    switch (RxState) 
    {
        case WAIT_HEADER1:
            if (uartdata == 0x55)
            {
                RxState = WAIT_HEADER2;
            }
            break;

        case WAIT_HEADER2:
            if (uartdata == 0x53)
            {
                RxState = RECEIVE_ANGLE_DATA;
                dataIndex = 0;
            }
            else if(uartdata == 0x52)
            {
                RxState = RECEIVE_GYRO_DATA;
                dataIndex = 0;
            }
            else
            {
                RxState = WAIT_HEADER1;
            }
            break;

        case RECEIVE_ANGLE_DATA:
            receivedData[dataIndex++] = uartdata;
            if (dataIndex == 9)
            {
                RollL = receivedData[0];
                RollH = receivedData[1];
                PitchL = receivedData[2];
                PitchH = receivedData[3];
                YawL = receivedData[4];
                YawH = receivedData[5];
                VL = receivedData[6];
                VH = receivedData[7];
                SUM_angle = receivedData[8];

                uint8_t calculatedSuma = 0x55 + 0x53 + RollH + RollL + PitchH + PitchL + YawH + YawL + VH + VL;

                if (calculatedSuma == SUM_angle)
                {
                    float rawRoll  = ((uint16_t)RollH << 8) | RollL;
                    float rawPitch = ((uint16_t)PitchH << 8) | PitchL;
                    float rawYaw   = ((uint16_t)YawH << 8) | YawL;

                    Roll  = rawRoll  / 32768.0f * 180.0f;
                    Pitch = rawPitch / 32768.0f * 180.0f;
                    Yaw   = rawYaw   / 32768.0f * 180.0f;

                    if (Roll  > 180.0f) Roll  -= 360.0f;
                    if (Pitch > 180.0f) Pitch -= 360.0f;
                    if (Yaw   > 180.0f) Yaw   -= 360.0f;
                }

                // 无论校验成功与否，都重置状态机
                RxState = WAIT_HEADER1;
            }
            break;
       case RECEIVE_GYRO_DATA:
           receivedData[dataIndex++] = uartdata;
           if (dataIndex == 9)
           {
               WxL = receivedData[0];
               WxH = receivedData[1];
               WyL = receivedData[2];
               WyH = receivedData[3];
               WzL = receivedData[4];
               WzH = receivedData[5];
               VolL = receivedData[6];
               VolH = receivedData[7];
               SUM_gyro = receivedData[8];

               uint8_t calculatedSumg = 0x55 + 0x52 + WxL + WxH + WyL + WyH + WzL + WzH + VolL + VolH;
               if (calculatedSumg == SUM_gyro)
               {
                   Roll_gyro = (float)((WxH<<8)|WxL)/32768*2000;
                   Pitch_gyro = (float)((WyH<<8)|WyL)/32768*2000;
                   Yaw_gyro = (float)((WzH<<8)|WzL)/32768*2000;
                   if(Roll_gyro>2000)Roll_gyro-=4000;
                   if(Pitch_gyro>2000)Pitch_gyro-=4000;
                   if(Yaw_gyro>2000)Yaw_gyro-=4000;
               }
               RxState = WAIT_HEADER1;
           }
           break;
    }
}

