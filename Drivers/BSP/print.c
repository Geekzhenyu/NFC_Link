//
// Created by MaoZhenYu on 24-9-13.
//
#include <stdarg.h>		  //  标准头文件
#include <stdio.h>
#include <string.h>
#include "print.h"

void print(const char* buf, ...)
{
    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(&UART, str, strlen(str), 0xff);
    va_end(v);
}