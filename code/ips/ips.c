#include "zf_common_headfile.h"

#define IPS200_TYPE     (IPS200_TYPE_SPI)                                 // 双排排针 并口两寸屏 这里宏定义填写 IPS200_TYPE_PARALLEL8
                                                                                // 单排排针 SPI 两寸屏 这里宏定义填写 IPS200_TYPE_SPI

void ips_init(void)
{
    ips200_set_dir(IPS200_PORTAIT);
    ips200_set_color(RGB565_RED, RGB565_BLACK);
    ips200_init(IPS200_TYPE);
}

/*
使用示例
display_text(0, 0, "lef:%d", motor_value.receive_left_speed_data);
display_text(0, 16, "rig:%.d", motor_value.receive_right_speed_data);
display_text(0, 32, "mid:%.d", wheel_encoder_num);
*/

void display_text(int x, int y, const char* format, ...) {

    char txt[100];  // 适当设置缓冲区大小
    va_list args;
    va_start(args, format);

    // 使用vprintf来处理格式化参数
    vsprintf(txt, format, args);

    va_end(args);

    // 显示字符串
    ips200_show_string((unsigned short)x, (unsigned short)y, txt);
}

void ips_clear(void)
{
        static int counter = 0;
        const int threshold = 5;

        if (++counter >= threshold)
        {
            counter = 0;
            ips200_clear();
        }
}
