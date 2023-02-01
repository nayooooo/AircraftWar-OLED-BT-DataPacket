#include "AW_Player.h"

static AW_Player_t player;

const unsigned char player_Map1[] = {
	0X00,0X50,0X50,0X70,0X20,0X20,0X00
};

/**
 * @fn static void AW_Player_Update(void)
 * @brief ����ҽ�ɫ���µ���ʾ����Ļ�����
 *
 */
static void AW_Player_Update(void)
{
	OLED_ShowBMP(player.p.x * AW_SS.pixelSize, player.p.y * AW_SS.pixelSize,
					player.map, player.mapWidth, player.mapHeight, FILL);
}

/**
 * @fn void AW_Player_Move(Point p)
 * @brief ��Ϸ��ɫ�ƶ����µ�����
 *
 * @param [p] �µ�����
 *
 */
void AW_Player_Move(Point p)
{
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
