#include "AircraftWar.h"

#include "AW_Bmp.h"

/*================================================================
	显示载体相关变量信息
================================================================*/

// 显示载体参数
AW_Screen_Size AW_SS = {0};

/*================================================================
	显示载体相关函数声明
================================================================*/

static void AW_Screen_Show_BG(const uint8_t *bg);

/*================================================================
	显示载体相关函数
================================================================*/

/**
 * @fn static void AW_Screen_Show_BG(const uint8_t *bg)
 * @brief 显示载体显示指定背景
 *
 * @param [bg] 背景图片的数组的指针
 *
 */
static void AW_Screen_Show_BG(const uint8_t *bg)
{
	OLED_ShowBMP(0, 0, bg, AW_SS.width-1, AW_SS.height-1, FILL);
}

/**
 * @fn static void AW_Screen_Infor_Init
 * (
 * 	uint16_t scWidth, uint16_t scHeight, uint8_t scPixelSize
 * )
 * @brief 初始化显示载体参数
 *
 * @param [scWidth] 显示载体宽度
 * @param [scHeight] 显示载体高度
 * @param [scPixelSize] 显示载体像素大小
 *
 */
static void AW_Screen_Infor_Init
(
	uint16_t scWidth, uint16_t scHeight, uint8_t scPixelSize
)
{
	AW_SS.width = scWidth;
	AW_SS.height = scHeight;
	AW_SS.pixelSize = scPixelSize;
}

/**
 * @fn void AW_Game_Init(void)
 * @brief 初始化飞机大战游戏
 *
 */
void AW_Game_Init(void)
{
	// 初始化显示载体
	OLED_Init();
	// 初始化游戏参数
	AW_Screen_Infor_Init(AW_SCREEN_WIDTH, AW_SCREEN_HEIGH, AW_SCREEN_PIXEL_SIZE_DEFAULT);
	// 初始化游戏场景
	AW_Screen_Show_BG(AW_BG_Bmp1);
	// 初始化玩家角色
}

/**
 * @fn void AW_Screen_Refresh(void)
 * @brief 刷新显示载体
 *
 */
void AW_Screen_Refresh(void)
{
	OLED_Refresh_Gram();
}
