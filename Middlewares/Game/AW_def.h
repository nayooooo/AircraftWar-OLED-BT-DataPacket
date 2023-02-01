#ifndef __AW_DEF_H
#define __AW_DEF_H

#include "stdio.h"		// 调试输出
#include "stdint.h"
#include "oled.h"		// 显示载体
typedef Point AW_Point;

/*================================================================
	显示载体相关宏
================================================================*/

#define AW_SCREEN_WIDTH						(OLED_COL_MAX)		/* 屏幕宽 */
#define AW_SCREEN_HEIGH						(OLED_ROW_MAX)		/* 屏幕高 */

#define AW_SCREEN_PIXEL_SIZE_DEFAULT		(1)					/* 默认像素大小 */

/*================================================================
	显示载体相关结构体
================================================================*/

// 屏幕参数
typedef struct{
	uint16_t width;						// 显示载体宽度
	uint16_t height;					// 显示载体高度
	uint8_t pixelSize;					// 显示载体像素大小，可自行设定
	const uint8_t *bg;					// 背景
}AW_Screen_t;

#endif /* __AW_DEF_H */
