#ifndef __MAIN_H
#define __MAIN_H

#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "tim.h"

#include "led.h"
#include "bt.h"
#include "oled.h"

#include "AircraftWar.h"

typedef struct{
	uint8_t refresh: 1;
	uint8_t moveBullet: 1;
}main_Task_Flag_t;

#endif /* __MAIN_H */
