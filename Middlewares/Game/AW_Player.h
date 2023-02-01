#ifndef __AW_PLAYER_H
#define __AW_PLAYER_H

#include "AircraftWar.h"

#include "AW_Bullet.h"

/*================================================================
	游戏成员参数宏
================================================================*/

#define AW_PLAYER_BULLETS_NUM_MAX				(5)
#define AW_PLAYER_PX_DEFAULT					(0)
#define AW_PLAYER_PY_DEFAULT					(AW_SS.height / AW_SS.pixelSize / 2)
#define AW_PLAYER_BLOODVOL_DEFAULT				(100)

/*================================================================
	游戏成员结构体
================================================================*/

typedef struct{
	AW_Bullet_t bullets[AW_PLAYER_BULLETS_NUM_MAX];		// 子弹
	AW_Point p;					// 位置坐标
	uint8_t bloodVol;			// 血量
	const uint8_t *map;			// 贴图
	uint8_t mapWidth;			// 贴图宽度
	uint8_t mapHeight;			// 贴图高度
} AW_Player_t;

/*================================================================
	游戏成员相关函数
================================================================*/

void AW_Player_Init(void);

const AW_Point *AW_Player_Get_Coor(void);
uint8_t AW_Player_Get_Width(void);
uint8_t AW_Player_Get_Height(void);

void AW_Player_Move(AW_Point p);
void AW_Player_Update(void);

#endif /* __AW_PLAYER_H */
