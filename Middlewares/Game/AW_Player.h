#ifndef __AW_PLAYER_H
#define __AW_PLAYER_H

#include "AircraftWar.h"

#include "AW_Bullet.h"

/*================================================================
	��Ϸ��Ա������
================================================================*/

#define AW_PLAYER_BULLETS_NUM_MAX				(5)
#define AW_PLAYER_PX_DEFAULT					(0)
#define AW_PLAYER_PY_DEFAULT					(AW_SS.height / AW_SS.pixelSize / 2)
#define AW_PLAYER_BLOODVOL_DEFAULT				(100)

/*================================================================
	��Ϸ��Ա�ṹ��
================================================================*/

typedef struct{
	AW_Bullet_t bullets[AW_PLAYER_BULLETS_NUM_MAX];		// �ӵ�
	AW_Point p;					// λ������
	uint8_t bloodVol;			// Ѫ��
	const uint8_t *map;			// ��ͼ
	uint8_t mapWidth;			// ��ͼ���
	uint8_t mapHeight;			// ��ͼ�߶�
} AW_Player_t;

/*================================================================
	��Ϸ��Ա��غ���
================================================================*/

void AW_Player_Init(void);

const AW_Point *AW_Player_Get_Coor(void);
uint8_t AW_Player_Get_Width(void);
uint8_t AW_Player_Get_Height(void);

void AW_Player_Move(AW_Point p);
void AW_Player_Update(void);

#endif /* __AW_PLAYER_H */
