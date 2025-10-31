/*
 * @Author: ZiJiaYou 2468493894@qq.com
 * @Date: 2025-07-27 00:12:46
 * @LastEditors: ZiJiaYou 2468493894@qq.com
 * @LastEditTime: 2025-07-27 06:02:47
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef CODE_PID_PID_H_
#define CODE_PID_PID_H_

#include "zf_common_headfile.h"

#ifndef abs
#define abs(x) ((x > 0) ? x : -x)
#endif

typedef struct
{
    // config parameter
    float Kp;
    float Ki;
    float Kd;
    float MaxOut;
    float DeadBand;

    float IntegralLimit;     // �����޷�
    float Output_LPF_RC;     // ����˲��� RC
    float Derivative_LPF_RC; // ΢���˲���ϵ��

    //-----------------------------------
    // for calculating
    float Measure;
    float Last_Measure;
    float Err;
    float Last_Err;
    float Prev_Err;
    float Last_ITerm;

    float Pout;
    float Iout;
    float Dout;
    float ITerm;

    float Output;
    float Last_Output;
    float Last_Dout;

    float Ref;

    uint32 DWT_CNT;
    float dt;

    float Filtered_Dout;     // �������˲����΢����
    float Filtered_Output;   // �������˲�����������
} PIDInstance;

typedef struct // config parameter
{
    // basic parameter
    float Kp;
    float Ki;
    float Kd;
    float MaxOut;   // ����޷�
    float DeadBand; // ����

    float IntegralLimit; // �����޷�
    float Output_LPF_RC; // RC = 1/omegac
    float Derivative_LPF_RC;
} PID_Init_Config;


void PIDInit(PIDInstance *pid, PID_Init_Config *config);
float PIDCalculate(PIDInstance *pid, float ref, float measure);
float PIDCalculate_Incremental(PIDInstance *pid, float ref, float measure);

#endif /* CODE_PID_PID_H_ */
