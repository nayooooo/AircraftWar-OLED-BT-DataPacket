#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"

void delay_Init(uint8_t SYSCLK_M);

uint32_t delay_Get_SysTick_Val(void);
void delay_Set_SysTick_Val(uint32_t val);

void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#endif /* __DELAY_H */
