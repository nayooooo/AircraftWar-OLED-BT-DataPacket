#include "AircraftWar.h"

/*================================================================
	显示载体相关变量信息
================================================================*/

// 设置屏幕尺寸参数，此处设为默认值
AW_Screen_Size AW_SS = {
	.width = AW_SCREEN_WIDTH,
	.height = AW_SCREEN_HEIGH,
	.pixelSize = AW_SCREEN_PIXEL_SIZE_DEFAULT
};

/*================================================================
	显示载体相关函数
================================================================*/

/**
 * @fn void AW_Screen_Refresh(void)
 * @brief 刷新显示载体
 */
void AW_Screen_Refresh(void)
{
	OLED_Refresh_Gram();
}
