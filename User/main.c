/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 * @brief 飞机大战
 * @details 注释了OLED除大小为8的字模，如需使用，请前往oledfont.h文件处修改
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
	
	while(1)
	{
		if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // 接收到了一包数据
			BT_Get_DataPacket_Rx();  // 读取接收到的这包数据
			BT_DataPacket_Rx_Handle();
		}
	}
}
