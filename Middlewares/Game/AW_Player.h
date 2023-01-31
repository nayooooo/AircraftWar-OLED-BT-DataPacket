#ifndef __AW_PLAYER_H
#define __AW_PLAYER_H

#include "AircraftWar.h"

/*================================================================
	游戏成员结构体
================================================================*/

typedef struct{
	Point p;					// 位置坐标
	uint8_t bloodVol;			// 血量
} AW_Player_t;

#endif /* __AW_PLAYER_H */
