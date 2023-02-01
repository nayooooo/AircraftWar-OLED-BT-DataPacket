/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief �ɻ���ս
 * @details ע����OLED����СΪ8����ģ������ʹ�ã���ǰ��oledfont.h�ļ����޸�
 *
 */

#include "main.h"

#include "AW_Player.h"

int main()
{
	Point p = { 0, 20 };
	
	HAL_Init();
	
	sys_stm32_clock_init();
	delay_Init(MAIN_Fosc_M);
	uart_init(115200UL);
	
	LED_Init();
	BT_Init();
	AW_Game_Init(); AW_Screen_Refresh();
	
	while(1)
	{
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // ���յ���һ������
			BT_Get_DataPacket_Rx();  // ��ȡ���յ����������
			BT_DataPacket_Show_USART1();
			BT_DataPacket_Rx_Handle();
		}
	}
}
