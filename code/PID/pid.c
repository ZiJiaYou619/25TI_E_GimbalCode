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

static void f_Output_Limit(PIDInstance *pid)
{
    if (pid->Output > pid->MaxOut)
    {
        pid->Output = pid->MaxOut;
    }
    if (pid->Output < -(pid->MaxOut))
    {
        pid->Output = -(pid->MaxOut);
    }
}
void PIDInit(PIDInstance *pid, PID_Init_Config *config)
{
    if (pid == NULL || config == NULL)
        zf_log(0, "*PID == NULL");

    pid->Kp = config->Kp;
    pid->Ki = config->Ki;
    pid->Kd = config->Kd;
    pid->MaxOut = config->MaxOut;
    pid->DeadBand = config->DeadBand;
    pid->IntegralLimit = config->IntegralLimit;
    pid->Output_LPF_RC = config->Output_LPF_RC;
    pid->Derivative_LPF_RC = config->Derivative_LPF_RC;

    pid->Measure = 0.0f;
    pid->Last_Measure = 0.0f;
    pid->Err = 0.0f;
    pid->Last_Err = 0.0f;
    pid->Last_ITerm = 0.0f;

    pid->Pout = 0.0f;
    pid->Iout = 0.0f;
    pid->Dout = 0.0f;
    pid->ITerm = 0.0f;

    pid->Output = 0.0f;
    pid->Last_Output = 0.0f;
    pid->Last_Dout = 0.0f;

    pid->Ref = 0.0f;

    pid->DWT_CNT = 0;
    pid->dt = 0.0f;
}

float PIDCalculate(PIDInstance *pid, float ref, float measure)
{
    //pid->dt = (float)SoftDWT_GetCycle_us()*0.001;
//    if(pid->dt == 0)
//    {
//        pid->dt = CH1_TIME_US;
//    }

    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;

    pid->Pout = pid->Kp * pid->Err;
    pid->ITerm = pid->Ki * pid->Err * 0.002;
    pid->Dout = pid->Kd * (pid->Err - pid->Last_Err);

    pid->Iout += pid->ITerm;
    pid->Output = pid->Pout + pid->Iout + pid->Dout;

    f_Output_Limit(pid);

    pid->Last_Measure = pid->Measure;
    pid->Last_Output = pid->Output;
    pid->Last_Dout = pid->Dout;
    pid->Last_Err = pid->Err;
    pid->Last_ITerm = pid->ITerm;

    return pid->Output;
}

float PIDCalculate_Incremental(PIDInstance *pid, float ref, float measure)
{
    pid->dt = (float)SoftDWT_GetCycle_us();
    if(pid->dt == 0)
    {
        pid->dt = CH1_TIME_US;
    }

    pid->Measure = measure;
    pid->Ref = ref;
    pid->Err = pid->Ref - pid->Measure;

    pid->Pout = pid->Kp * (pid->Err - pid->Last_Err);
    pid->Iout = pid->Ki * pid->Err * pid->dt;
    pid->Dout = pid->Kd * (pid->Err - 2*pid->Last_Err + pid->Prev_Err)/pid->dt;

    float delta_output = pid->Pout + pid->Iout + pid->Dout;

    pid->Output = pid->Last_Output + delta_output;

    if(pid->Output > pid->MaxOut) {
        pid->Output = pid->MaxOut;
    } else if(pid->Output < -pid->MaxOut) {
        pid->Output = -pid->MaxOut;
    }

    pid->Prev_Err = pid->Last_Err;
    pid->Last_Err = pid->Err;
    pid->Last_Output = pid->Output;

    return pid->Output;
}
