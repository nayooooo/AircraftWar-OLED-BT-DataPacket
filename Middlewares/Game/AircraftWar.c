#define AW_ALL_ENABLE
#include "AircraftWar.h"

#include "AW_Bg.h"

/*================================================================
	��ʾ������ر�����Ϣ
================================================================*/

// ��ʾ�������
AW_Screen_t AW_SS = {0};

/*================================================================
	��ʾ������غ�������
================================================================*/

static void AW_Screen_Show_BG(const uint8_t *bg);

/*================================================================
	��ʾ������غ���
================================================================*/

/**
 * @fn static void AW_Screen_Show_BG(const uint8_t *bg)
 * @brief ��ʾ������ʾָ������
 *
 * @param [bg] ����ͼƬ�������ָ��
 *
 */
static void AW_Screen_Show_BG(const uint8_t *bg)
{
	OLED_ShowBMP(0, 0, bg, AW_SS.width-1, AW_SS.height-1, FILL);
}

/**
 * @fn static void AW_Screen_Infor_Init
 * (
 * 	uint16_t scWidth, uint16_t scHeight, uint8_t scPixelSize,
 * 	const uint8_t *bg
 * )
 * @brief ��ʼ����ʾ�������
 *
 * @param [scWidth] ��ʾ������
 * @param [scHeight] ��ʾ����߶�
 * @param [scPixelSize] ��ʾ�������ش�С
 * @param [bg] ����
 *
 */
static void AW_Screen_Infor_Init
(
	uint16_t scWidth, uint16_t scHeight, uint8_t scPixelSize,
	const uint8_t *bg
)
{
	AW_SS.width = scWidth;
	AW_SS.height = scHeight;
	AW_SS.pixelSize = scPixelSize;
	AW_SS.bg = bg;
}

/**
 * @fn void AW_Game_Init(void)
 * @brief ��ʼ���ɻ���ս��Ϸ
 *
 */
void AW_Game_Init(void)
{
	// ��ʼ����ʾ����
	OLED_Init();
	// ��ʼ����Ϸ����
	AW_Screen_Infor_Init(AW_SCREEN_WIDTH, AW_SCREEN_HEIGH, AW_SCREEN_PIXEL_SIZE_DEFAULT, AW_BG_Bmp1);
	// ��ʼ����Ϸ����
	AW_Screen_Show_BG(AW_SS.bg);
	// ��ʼ����ҽ�ɫ
	AW_Player_Init();
	// ˢ����ʾ����
	AW_Screen_Refresh();
}

/**
 * @fn void AW_Screen_Refresh(void)
 * @brief ˢ����ʾ����
 *
 */
void AW_Screen_Refresh(void)
{
	AW_Screen_Show_BG(AW_SS.bg);
	AW_Player_Update();
	
	OLED_Refresh_Gram();
}
