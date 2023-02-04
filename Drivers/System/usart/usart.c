#include "sys.h"
#include "usart.h"

#include "string.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2019/9/17
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1

#if (__ARMCC_VERSION >= 6010050)				/* 使用AC6编译器 */
__asm (".global __use_no_semihosting\n\t");		/* 声明不使用半主机模式 */
__asm (".global __ARM_use_no_argv \n\t");		/* AC6不需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */
#else											/* 使用AC5编译器 */
#pragma import(__use_no_semihosting)

struct __FILE
{
	int handle;
}
#endif

// 不使用半主机模式，至少需要重定义__ttywrch\_sys_exit\_sys_command_string函数，以同时兼容AC6和AC5模式
int _ttywrch(int ch)
{
	ch = ch;
	return ch;
}

// 定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}

char *_sys_command_string(char *cmd, int len)
{
	return NULL;
}

// FILE在stdio.h里面定义
FILE __stdout;
#endif  /* 代码法 */

#if 1
// 重定义fputc函数
int fputc(int ch, FILE *f)
{
	// 循环发送,直到发送完毕
	while((USART1->ISR&0X40)==0){}
    USART1->TDR = (uint8_t) ch;
	return ch;
}
#endif /* 重定义fputc */


#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t USART_RX_STA=0;       //接收状态标记	  

uint8_t aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲
UART_HandleTypeDef UART1_Handler; //UART句柄
  
//初始化IO 串口1 
//bound:波特率
void uart_init(uint32_t bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
	
	printf("\r\n");
	printf("***************************************************\r\n");
	printf("       STM32G030F6P6 USART1 has initialized!\r\n");
	printf("***************************************************\r\n");
	printf("\r\n");
}
 
//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART1_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY)//等待就绪
	{
	 timeout++;////超时处理
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	 timeout++; //超时处理
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 
#endif /* EN_USART1_RX */

#if EN_USART2_RX   //如果使能了接收

uint8_t USART2_RX_BUF[USART2_REC_LEN];  // 接收缓冲,最大USART2_REC_LEN个字节.
//接收状态
//bit15，	接收完成但未读取(1)
//bit14，	接收溢出(1)
//bit13~0，	接收到的有效字节数目
uint16_t USART2_RX_STA = 0X0000;
uint8_t _2RxBuffer[_2RXBUFFERSIZE];  // HAL库使用的串口接收缓冲
// UART2句柄
UART_HandleTypeDef UART2_Handler;
  
//初始化IO 串口1 
//bound:波特率
void uart2_init(uint32_t bound)
{	
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    //USART2
	UART2_Handler.Init.BaudRate=bound;				    //波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()会使能UART2
	
	HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)_2RxBuffer, _2RXBUFFERSIZE);//该函数会开启接收中断，并且设置接收缓冲以及接收缓冲接收最大数据量
	
	printf("\r\n");
	printf("***************************************************\r\n");
	printf("       STM32G030F6P6 USART2 has initialized!\r\n");
	printf("***************************************************\r\n");
	printf("\r\n");
}
 
//串口1中断服务程序
void USART2_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART2_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY)//等待就绪
	{
	 timeout++;////超时处理
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)_2RxBuffer, _2RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	 timeout++; //超时处理
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 

#endif /* EN_USART2_RX */

#include "bt_dp.h"  // BT所用的串口二需要数据包中的原数据数目信息

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t errTimes = 0;  // 数据包错误次数
	// 接收小车相关数据包 Car_DataPacket_Rx_t 的标志位
	// bit2~0	->	接收到的原始数据和校验和的字节数
	// bit3		->	接收到了包头数据
	// bit4		->	接收完了原始数据
	static uint8_t car_DataPacket_Rx_Flag = 0X00;
	uint8_t Res = 0;
	
	if(huart->Instance==USART1)//如果是串口1
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}

	}
	if(huart->Instance==USART2)//如果是串口2
	{
		Res = _2RxBuffer[0];	// 读取接收到的数据
		USART2_RX_BUF[USART2_RX_STA&USART2_RX_STA_REC_NUM] = Res;
		USART2_RX_STA++;
		USART2_RX_BUF[USART2_RX_STA&USART2_RX_STA_REC_NUM] = 0;
		USART2_RX_STA |= USART2_RX_STA_HAS_REC;
		
		// 接收数据包
		// 接收未完成
		if (!(USART2_RX_STA&USART2_RX_STA_REC_END)) {
			if (car_DataPacket_Rx_Flag&0X08) {  // 接收到了包头数据
				// 接收原始数据和校验和
				// 接收完成
				if ((car_DataPacket_Rx_Flag&0X10) || ((car_DataPacket_Rx_Flag&0X07) == BT_DP_TOTAL_BYTE_NUM-2)) {
					car_DataPacket_Rx_Flag |= 0X10;
					// 接收包尾数据
					if (Res == BT_DATAPACKET_TAIL_DEFAULT) {  // 接收到了包尾数据
						USART2_RX_STA |= USART2_RX_STA_REC_END;
					} else {  // 数据包接收失败
						errTimes++;
						printf("BT rec failed!\r\n");
						USART2_RX_STA &= USART2_RX_STA_OVERFLOW;
					}
					car_DataPacket_Rx_Flag = 0X00;
				} else car_DataPacket_Rx_Flag++;
			} else {
				if (Res == BT_DATAPACKET_HEAD_DEFAULT)  // 正在接收的是包头数据
					car_DataPacket_Rx_Flag |= 0X08;
			}
		}
		
		if (errTimes >= 20) {  // 接收错误次数超过20次将重置USART3接收
			errTimes = 0;
			car_DataPacket_Rx_Flag = 0;
			USART2_RX_STA = 0;
			USART2_RX_BUF[0] = 0;
		}
		
		// 接收缓存溢出，重新开始接收
		if ((USART2_RX_STA&USART2_RX_STA_REC_NUM)>(USART2_REC_LEN-1)) {
			printf("USART2 Rx Buff overflow!\r\n");
			// 清空接收数据位数统计位，溢出位置位
			USART2_RX_STA &= ~USART2_RX_STA_REC_NUM;
			USART2_RX_STA |=\
			((((USART2_RX_STA&USART2_RX_STA_OVERFLOW) >> 12) + 1)\
			<< 12) & USART2_RX_STA_OVERFLOW;
			// 清空接收缓冲区
			memset(USART2_RX_BUF, 0, USART2_REC_LEN);
		}
	}
}

//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOB时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
	
		GPIO_Initure.Pin=GPIO_PIN_6;			//PB6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB6

		GPIO_Initure.Pin=GPIO_PIN_7;			//PB7
		GPIO_Initure.Mode=GPIO_MODE_AF_OD;		//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB7
		
#if EN_USART1_RX
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//抢占优先级3，子优先级3
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
#endif	
	}
	if(huart->Instance==USART2)//如果是串口2，进行串口2 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
		GPIO_Initure.Mode=GPIO_MODE_AF_OD;		//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA3
		
#if EN_USART2_RX
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//使能USART2中断通道
#endif	
	}
}








