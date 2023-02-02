#define AW_PLAYER_ENABLE
#include "AircraftWar.h"

static AW_Player_t player;

const unsigned char player_Map1[] = {
	0X00,0X50,0X50,0X70,0X20,0X20,0X00
};

/**
 * @fn void AW_Player_Update(void)
 * @brief ����ҽ�ɫ���µ���ʾ����Ļ�����
 *
 */
void AW_Player_Update(void)
{
	OLED_ShowBMP(player.p.x * AW_SS.pixelSize, player.p.y * AW_SS.pixelSize,
					player.map, player.mapWidth, player.mapHeight, FILL);
}

/**
 * @fn const AW_Point *AW_Player_Get_Coor(void)
 * @brief �����Ϸ��ɫ����
 *
 * @return [const Point*] ��ҽ�ɫ�����ָ��
 *
 */
const AW_Point *AW_Player_Get_Coor(void)
{
	return ((const AW_Point*)&player.p);
}

/**
 * @fn uint8_t AW_Player_Get_Width(Point p)
 * @brief �����Ϸ��ɫ���
 *
 * @return [uint8_t] ��Ϸ��ɫ���
 *
 */
uint8_t AW_Player_Get_Width(void)
{
	return player.mapWidth;
}

/**
 * @fn uint8_t AW_Player_Get_Height(Point p)
 * @brief �����Ϸ��ɫ�߶�
 *
 * @return [uint8_t] ��Ϸ��ɫ�߶�
 *
 */
uint8_t AW_Player_Get_Height(void)
{
	return player.mapHeight;
}

/**
 * @fn AW_Bullet_t *AW_Player_Get_First_Ready_Bullet(void)
 * @brief �����Ϸ��ɫ�ĵ�һ����׼���õ��ӵ�ָ��
 *
 * @return [AW_Bullet_t*] ��Ϸ��ɫ�ĵ�һ����׼���õ��ӵ�ָ��
 *
 */
AW_Bullet_t *AW_Player_Get_First_Ready_Bullet(void)
{
	uint8_t i;
	
	for (i = 0; i < AW_PLAYER_BULLETS_NUM_MAX; i++) {
		if (player.bullets[i].isLaunch == 0) {  // ��׼���õ��ӵ�
			return &(player.bullets[i]);
		}
	}
	
	return NULL;
}

/**
 * @fn void AW_Player_Move(AW_Point p)
 * @brief ��Ϸ��ɫ�ƶ����µ�����
 *
 * @param [p] �µ�����
 *
 */
void AW_Player_Move(AW_Point p)
{
	if (p.x * AW_SS.pixelSize + player.mapWidth > AW_SS.width) return;
	if (p.y * AW_SS.pixelSize + player.mapHeight > AW_SS.height) return;
	
	player.p.x = p.x;
	player.p.y = p.y;
	AW_Player_Update();
}

/**
 * @fn void AW_Player_Init(void)
 * @brief ��ʼ����Ϸ��ɫ
 *
 */
void AW_Player_Init(void)
{
	for(uint8_t i = 0; i < AW_PLAYER_BULLETS_NUM_MAX; i++) {
		player.bullets[i].isLaunch = 0;
		player.bullets[i].shootDir = AW_BULLET_PLAYER_SHOOT_DIR;
		player.bullets[i].p.x = 0;
		player.bullets[i].p.y = 0;
	}
	player.p.x = AW_PLAYER_PX_DEFAULT;
	player.p.y = AW_PLAYER_PY_DEFAULT;
	player.bloodVol = AW_PLAYER_BLOODVOL_DEFAULT;
	player.map = player_Map1;
	player.mapWidth = 7;
	player.mapHeight = 5;
	
	AW_Player_Update();
}
