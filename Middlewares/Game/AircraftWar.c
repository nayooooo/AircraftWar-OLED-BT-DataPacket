#include "AircraftWar.h"

/*================================================================
	��ʾ������ر�����Ϣ
================================================================*/

// ������Ļ�ߴ�������˴���ΪĬ��ֵ
AW_Screen_Size AW_SS = {
	.width = AW_SCREEN_WIDTH,
	.height = AW_SCREEN_HEIGH,
	.pixelSize = AW_SCREEN_PIXEL_SIZE_DEFAULT
};

/*================================================================
	��ʾ������غ���
================================================================*/

/**
 * @fn void AW_Screen_Refresh(void)
 * @brief ˢ����ʾ����
 */
void AW_Screen_Refresh(void)
{
	OLED_Refresh_Gram();
}
