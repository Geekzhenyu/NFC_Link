//
// Created by MaoZhenYu on 24-9-13.
//

#ifndef PRINT_H
#define PRINT_H

#include "main.h"

extern UART_HandleTypeDef huart1;

#define UART    huart1

void print(const char* buf, ...);

#endif //PRINT_H
