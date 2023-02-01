#ifndef __AIRCRAFTWAR_H
#define __AIRCRAFTWAR_H

/*================================================================
	includes
================================================================*/

#include "AW_def.h"

#ifdef AW_BULLET_ENABLE
	#include "AW_Bullet.h"
#endif /* AW_BULLET_ENABLE */
#ifdef AW_PLAYER_ENABLE
	#include "AW_Bullet.h"
	#include "AW_Player.h"
#endif /* AW_PLAYER_ENABLE */
#ifdef AW_ALL_ENABLE
	#include "AW_Bullet.h"
	#include "AW_Player.h"
#endif /* AW_ALL_ENABLE */

/*================================================================
	声明显示载体相关变量信息
================================================================*/

extern AW_Screen_t AW_SS;

/*================================================================
	声明显示载体相关函数
================================================================*/

void AW_Game_Init(void);

void AW_Screen_Refresh(void);

#endif /* __AIRCRAFTWAR_H */
