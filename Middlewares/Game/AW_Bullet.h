#ifndef __AW_BULLET_H
#define __AW_BULLET_H

#include "AW_def.h"

/*================================================================
	子弹结构体
================================================================*/

typedef struct AW_Bullet{
	struct AW_Bullet *prev;
	struct AW_Bullet *next;
	uint8_t isLaunch: 1;		// 子弹发射出去了
	uint8_t shootDir;			// 子弹发射方向
	AW_Point p;					// 位置坐标
} AW_Bullet_t;

/*================================================================
	子弹相关宏
================================================================*/

typedef enum{
	AW_Bullet_Shoot_Right,				// 从左往右
	AW_Bullet_Shoot_left,				// 从右往左
}AW_Bullet_Shoot_Dir_Enum_t;
#define AW_BULLET_PLAYER_SHOOT_DIR				(AW_Bullet_Shoot_Right)		/* 玩家角色发射子弹方向 */
#define AW_BULLET_ENEMY_SHOOT_DIR				(AW_Bullet_Shoot_left)		/* 敌机发射子弹方向 */

/*================================================================
	子弹相关函数
================================================================*/

AW_Err_Enum_t AW_Bullet_Init(AW_Bullet_t *bullet);

AW_Err_Enum_t AW_Bullet_Shoot(AW_Bullet_t *bullet, AW_Point p);

#endif /* __AW_BULLET_H */
