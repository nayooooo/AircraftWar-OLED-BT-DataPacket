/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief 飞机大战
 * @details 注释了OLED除大小为8的字模，如需使用，请前往oledfont.h文件处修改
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
		// 刷新显示载体任务
		if (Refresh_Task0 == 1) {  // 30Hz
			Refresh_Task0 = 0;
			AW_Screen_Refresh();
		}
		
		// 移动子弹任务
		if (Move_Bullet_Task1 == 1) {  // 2Hz
			Move_Bullet_Task1 = 0;
			LED_Toggle();
			AW_Bullet_Move_CB();
		}
		
		// 收取数据包任务
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // 接收到了一包数据
			BT_Get_DataPacket_Rx();  // 读取接收到的这包数据
			BT_DataPacket_Printf();
			BT_DataPacket_Rx_Handle();
			AW_Screen_Refresh();
		}
	}
}
