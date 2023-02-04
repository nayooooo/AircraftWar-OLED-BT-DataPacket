/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief �ɻ���ս
 * @details ע����OLED����СΪ8����ģ������ʹ�ã���ǰ��oledfont.h�ļ����޸�
 *
 */

#include "main.h"

extern AW_Err_Enum_t AW_Bullet_Move_CB(void);

main_Task_Flag_t main_Task_Flag = {
	.refresh = 0,
	.moveBullet = 0,
};

int main()
{
	HAL_Init();
	
	sys_stm32_clock_init();
	delay_Init(MAIN_Fosc_M);
	uart_init(115200UL);
	
	LED_Init();
	BT_Init();
	AW_Game_Init();
	
	TIM14_Init(9, 1599);		// 16000000 / (1599 + 1) / (9 + 1) = 1000(Hz)
	
	while(1)
	{
		// ˢ����ʾ��������
		if (main_Task_Flag.refresh == 1) {  // 30Hz
			main_Task_Flag.refresh = 0;
			AW_Screen_Refresh();
		}
		
		// �ƶ��ӵ�����
		if (main_Task_Flag.moveBullet == 1) {  // 5Hz
			main_Task_Flag.moveBullet = 0;
			AW_Bullet_Move_CB();
		}
		
		// ��ȡ���ݰ�����
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // ���յ���һ������
			BT_Get_DataPacket_Rx();  // ��ȡ���յ����������
			BT_DataPacket_Printf();
			BT_DataPacket_Rx_Handle();
		}
	}
}
