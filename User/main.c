/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief �ɻ���ս
 * @details ע����OLED����СΪ8����ģ������ʹ�ã���ǰ��oledfont.h�ļ����޸�
 *
 */

#include "main.h"

extern uint32_t Global_Timer_Tick_Ms;

extern AW_Err_Enum_t AW_Bullet_Move_CB(void);

uint8_t Refresh_Task0 = 0;
uint8_t Move_Bullet_Task1 = 0;

int main()
{
	HAL_Init();
	
	sys_stm32_clock_init();
	delay_Init(MAIN_Fosc_M);
	uart_init(115200UL);
	
	TIM14_Init(9, 1599);		// 16000000 / (1599 + 1) / (9 + 1) = 1000(Hz)
	
	LED_Init();
	BT_Init();
	AW_Game_Init();
	
	while(1)
	{
		// ˢ����ʾ��������
		if (Refresh_Task0 == 1) {  // 30Hz
			Refresh_Task0 = 0;
			AW_Screen_Refresh();
		}
		
		// �ƶ��ӵ�����
		if (Move_Bullet_Task1 == 1) {  // 2Hz
			Move_Bullet_Task1 = 0;
			LED_Toggle();
			AW_Bullet_Move_CB();
		}
		
		// ��ȡ���ݰ�����
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // ���յ���һ������
			BT_Get_DataPacket_Rx();  // ��ȡ���յ����������
			BT_DataPacket_Printf();
			BT_DataPacket_Rx_Handle();
			AW_Screen_Refresh();
		}
	}
}
