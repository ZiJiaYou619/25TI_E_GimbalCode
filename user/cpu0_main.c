/*********************************************************************************************************************
* TC264 Opensourec Library ����TC264 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� TC264 ��Դ���һ����
*
* TC264 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          cpu1_main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          ADS v1.10.2
* ����ƽ̨          TC264D
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"

uint8 shoot_flag_R = 0;
uint8 shoot_flag_L = 0;
uint8 task4_flag = 0;
float now_yaw = 0;

void Task3_control_R(void);
void Task3_control_L(void);
void Task4_control(void);

void ALL_Init(void);

int core0_main(void)
{
    clock_init();
    debug_init();

    ALL_Init();

    cpu_wait_event_ready();

    now_yaw = Yaw;
    while (TRUE)
    {
        BEE_task(500);

        if(gpio_get_level(KEY4) == 0)
        {
            system_delay_ms(2);
            while(gpio_get_level(KEY4) == 0);
            shoot_flag_R = 1;
        }
        else if(gpio_get_level(KEY3) == 0)
        {
            system_delay_ms(2);
            while(gpio_get_level(KEY3) == 0);
            shoot_flag_L = 1;
        }
        else if(gpio_get_level(KEY2) == 0)
        {
            system_delay_ms(2);
            while(gpio_get_level(KEY2) == 0);
            task4_flag = 1;
        }
        //show_imu_data();
       // uart_show_recv_data();
    }
}


IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
    interrupt_global_enable(0);
    pit_clear_flag(CCU60_CH0);

    //stepper_update_handler();
    uart_io();
    if(shoot_flag_L)
    {
        Task3_control_L();
        steps_Pitch_task_basic();
        steps_Yaw_task_basic();
        shoot_laser();
    }
    else if(shoot_flag_R)
    {
        Task3_control_R();
        steps_Pitch_task_basic();
        steps_Yaw_task_basic();
        shoot_laser();
    }
    else if(task4_flag)
    {
        Task4_control();
        steps_Pitch_task();
        steps_Yaw_task();
        shoot_laser();
    }
    //UART_JY61P_INST_IRQHandler();�Ұ����������cpu1��ȡ�о�����

    SoftDWT_IRQHandler_ms();
}

IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
    interrupt_global_enable(0);
    pit_clear_flag(CCU60_CH1);
    delay_task(4000);
    SoftDWT_IRQHandler_us();
}

IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
    interrupt_global_enable(0);

//    if(shoot_flag_L||shoot_flag_R||task4_flag)
//    {
        uart_rx_interrupt_handler();
//    }
}

uint8_t find_cnt = 0;

void Task3_control_R(void)
{

    Bias_X = ReceiverData.BX;
    Bias_Y = ReceiverData.BY;

    if(ReceiverData.BX == 0 && ReceiverData.BY == 0)
    {
        if(Shoot_flag == 1)
        {
            Bias_X = 0;
            Bias_Y = 0;
        }
        else
        {
            Bias_X = -60;
            Bias_Y = -Roll;
            find_cnt = 0;
        }
        //BEE_ON;
    }
    else
    {
        find_cnt++;
        if(find_cnt>200)
        {
            find_cnt = 200;
        }
        Bias_X -= 176;
        Bias_Y -= 144;
    }
}

void Task3_control_L(void)
{

    Bias_X = ReceiverData.BX;
    Bias_Y = ReceiverData.BY;

    if(ReceiverData.BX == 0 && ReceiverData.BY == 0)
    {
        if(Shoot_flag == 1)
        {
            Bias_X = 0;
            Bias_Y = 0;
        }
        else
        {
            Bias_X = 60;
            Bias_Y = -Roll;
            find_cnt = 0;
        }
        //BEE_ON;
    }
    else
    {
        find_cnt++;
        if(find_cnt>200)
        {
            find_cnt = 200;
        }
        Bias_X -= 176;
        Bias_Y -= 144;
    }
}
float last_Bias_x = 0;
float last_Bias_y = 0;
uint8_t big_flag = 0;
uint8 corner = 0;
uint8 TI_last_data = 0;
uint8_t sleep_flag = 0;
void Task4_control(void)
{


    Bias_X = ReceiverData.BX;
    Bias_Y = ReceiverData.BY;

    if(ReceiverData.BX == 0 && ReceiverData.BY == 0 && find_cnt>0)
    {
        Bias_X = last_Bias_x/2;
        Bias_Y = 0;
    }
    else
    {
        find_cnt++;
        if(find_cnt>200)
        {
            find_cnt = 200;
        }
        Bias_X -= 176;
        Bias_Y -= 144;
        last_Bias_x = Bias_X;
    }
    if(corner==0)
    {
        if(TI_data==1)
        {
            sleep_flag = 1;
        }
        if(sleep_flag == 1)
        {
//            Steps_Yaw.middle_params.Kp = 4.3;
//            Steps_Yaw.inner_params.Kp = 4.8;
//            Steps_Yaw.middle_params.Ki = 0.20;
            Bias_X -= 25;
        }
        big_flag = 1;
    }
    else if(TI_data==1)
    {
        Bias_X-=5;
    }
//    else if(corner==1)
//    {
//        Bias_X-=1;
//    }
    else if(corner!=1)
    {
        Steps_Yaw.middle_params.ITerm = 0;
    }

//    else
//    {
//        Steps_Yaw.inner_params.Kp = 3.2;
//        Steps_Yaw.middle_params.Ki = 0.0;
//
//    }
//    if(d2==1)
//    {
//        Bias_X = ReceiverData.BX - (176-laser_bias);
//        BEE_ON;
//    }
    if(TI_last_data == 1&& TI_data ==0)
    {
        corner++;
    }

    last_Bias_x = Bias_X;
    TI_last_data = TI_data;

}

void ALL_Init(void)
{
    steps_Yaw_bias_init();
    steps_Pitch_bias_init();

    UART_init();
    uart_init(UART_3, 9600, UART3_TX_P15_6, UART3_RX_P15_7);
    uart_rx_interrupt(UART_3 ,1);

    steps_Pitch_init();
    steps_Yaw_init();
    stepper_init();

    SoftDWT_Init();
    GPIO_init();
    //ips_init();

    pit_ms_init(CCU60_CH0, CH0_TIME_MS);
    pit_us_init(CCU60_CH1, CH1_TIME_US);
}

#pragma section all restore
