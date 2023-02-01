#ifndef __AW_BULLET_H
#define __AW_BULLET_H

#include "AircraftWar.h"

/*================================================================
	子弹结构体
================================================================*/

typedef struct{
	uint8_t isLaunch: 1;		// 子弹发射出去了
	Point p;					// 位置坐标
} AW_Bullet_t;

#endif /* __AW_BULLET_H */
