/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief �ɻ���ս
 * @details ע����OLED����СΪ8����ģ������ʹ�ã���ǰ��oledfont.h�ļ����޸�
 *
 */

#include "main.h"

int main()
{
	HAL_Init();
	
	sys_stm32_clock_init();
	delay_Init(MAIN_Fosc_M);
	uart_init(115200UL);
	
	LED_Init();
	BT_Init();
	OLED_Init();
	
	OLED_ShowString(0, 0 * 8, (uint8_t*)"dp_head: ", 8, FILL);
	OLED_ShowString(0, 1 * 8, (uint8_t*)"dp_flag: ", 8, FILL);
	OLED_ShowString(0, 2 * 8, (uint8_t*)"dp_cheB: ", 8, FILL);
	OLED_ShowString(0, 3 * 8, (uint8_t*)"dp_tail: ", 8, FILL);
	
	while(1)
	{
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // ���յ���һ������
			BT_Get_DataPacket_Rx();  // ��ȡ���յ����������
			printf("\r\n");
			printf("========================================\r\n");
			printf("dpr->packet_Head:  %d\r\n", dpr[0].packet_Head);
			printf("dpr->flag:         %d\r\n", dpr[0].rawData.flag);
			printf("dpr->check_Byte:   %d\r\n", dpr[0].check_Byte);
			printf("dpr->packet_Tail:  %d\r\n", dpr[0].packet_Tail);
			printf("========================================\r\n");
			printf("\r\n");
			OLED_ShowNum(9 * 8, 0 * 8, (uint8_t)dpr[0].packet_Head, 3, 8, FILL);
			OLED_ShowNum(9 * 8, 1 * 8, (uint8_t)dpr[0].rawData.flag, 3, 8, FILL);
			OLED_ShowNum(9 * 8, 2 * 8, (uint8_t)dpr[0].check_Byte, 3, 8, FILL);
			OLED_ShowNum(9 * 8, 3 * 8, (uint8_t)dpr[0].packet_Tail, 3, 8, FILL);
			OLED_Refresh_Gram();
			BT_DataPacket_Rx_Handle();
		}
	}
}
