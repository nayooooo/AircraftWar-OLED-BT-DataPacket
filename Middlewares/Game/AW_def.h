#ifndef __AW_DEF_H
#define __AW_DEF_H

#include "stdio.h"		// �������
#include "stdint.h"
#include "oled.h"		// ��ʾ����
typedef Point AW_Point;

/*================================================================
	��ʾ������غ�
================================================================*/

#define AW_SCREEN_WIDTH						(OLED_COL_MAX)		/* ��Ļ�� */
#define AW_SCREEN_HEIGH						(OLED_ROW_MAX)		/* ��Ļ�� */

#define AW_SCREEN_PIXEL_SIZE_DEFAULT		(1)					/* Ĭ�����ش�С */

/*================================================================
	��ʾ������ؽṹ��
================================================================*/

// ��Ļ����
typedef struct{
	uint16_t width;						// ��ʾ������
	uint16_t height;					// ��ʾ����߶�
	uint8_t pixelSize;					// ��ʾ�������ش�С���������趨
	const uint8_t *bg;					// ����
}AW_Screen_t;

#endif /* __AW_DEF_H */
