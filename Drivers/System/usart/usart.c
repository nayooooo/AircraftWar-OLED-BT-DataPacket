#include "sys.h"
#include "usart.h"

#include "string.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2019/9/17
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1

#if (__ARMCC_VERSION >= 6010050)				/* ʹ��AC6������ */
__asm (".global __use_no_semihosting\n\t");		/* ������ʹ�ð�����ģʽ */
__asm (".global __ARM_use_no_argv \n\t");		/* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */
#else											/* ʹ��AC5������ */
#pragma import(__use_no_semihosting)

struct __FILE
{
	int handle;
}
#endif

// ��ʹ�ð�����ģʽ��������Ҫ�ض���__ttywrch\_sys_exit\_sys_command_string��������ͬʱ����AC6��AC5ģʽ
int _ttywrch(int ch)
{
	ch = ch;
	return ch;
}

// ����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}

char *_sys_command_string(char *cmd, int len)
{
	return NULL;
}

// FILE��stdio.h���涨��
FILE __stdout;
#endif  /* ���뷨 */

#if 1
// �ض���fputc����
int fputc(int ch, FILE *f)
{
	// ѭ������,ֱ���������
	while((USART1->ISR&0X40)==0){}
    USART1->TDR = (uint8_t) ch;
	return ch;
}
#endif /* �ض���fputc */


#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
uint8_t USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
uint16_t USART_RX_STA=0;       //����״̬���	  

uint8_t aRxBuffer[RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���
UART_HandleTypeDef UART1_Handler; //UART���
  
//��ʼ��IO ����1 
//bound:������
void uart_init(uint32_t bound)
{	
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
	
	printf("\r\n");
	printf("***************************************************\r\n");
	printf("       STM32G030F6P6 USART1 has initialized!\r\n");
	printf("***************************************************\r\n");
	printf("\r\n");
}
 
//����1�жϷ������
void USART1_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART1_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntExit();  											 
#endif
} 
#endif /* EN_USART1_RX */

#if EN_USART2_RX   //���ʹ���˽���

uint8_t USART2_RX_BUF[USART2_REC_LEN];  // ���ջ���,���USART2_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɵ�δ��ȡ(1)
//bit14��	�������(1)
//bit13~0��	���յ�����Ч�ֽ���Ŀ
uint16_t USART2_RX_STA = 0X0000;
uint8_t _2RxBuffer[_2RXBUFFERSIZE];  // HAL��ʹ�õĴ��ڽ��ջ���
// UART2���
UART_HandleTypeDef UART2_Handler;
  
//��ʼ��IO ����1 
//bound:������
void uart2_init(uint32_t bound)
{	
	//UART ��ʼ������
	UART2_Handler.Instance=USART2;					    //USART2
	UART2_Handler.Init.BaudRate=bound;				    //������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()��ʹ��UART2
	
	HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)_2RxBuffer, _2RXBUFFERSIZE);//�ú����Ὺ�������жϣ��������ý��ջ����Լ����ջ���������������
	
	printf("\r\n");
	printf("***************************************************\r\n");
	printf("       STM32G030F6P6 USART2 has initialized!\r\n");
	printf("***************************************************\r\n");
	printf("\r\n");
}
 
//����1�жϷ������
void USART2_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART2_Handler);	//����HAL���жϴ����ú���
	
	timeout=0;
    while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY)//�ȴ�����
	{
	 timeout++;////��ʱ����
     if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)_2RxBuffer, _2RXBUFFERSIZE) != HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
	 timeout++; //��ʱ����
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//ʹ��OS
	OSIntExit();  											 
#endif
} 

#endif /* EN_USART2_RX */

#include "bt_dp.h"  // BT���õĴ��ڶ���Ҫ���ݰ��е�ԭ������Ŀ��Ϣ

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static uint8_t errTimes = 0;  // ���ݰ��������
	// ����С��������ݰ� Car_DataPacket_Rx_t �ı�־λ
	// bit2~0	->	���յ���ԭʼ���ݺ�У��͵��ֽ���
	// bit3		->	���յ��˰�ͷ����
	// bit4		->	��������ԭʼ����
	static uint8_t car_DataPacket_Rx_Flag = 0X00;
	uint8_t Res = 0;
	
	if(huart->Instance==USART1)//����Ǵ���1
	{
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}

	}
	if(huart->Instance==USART2)//����Ǵ���2
	{
		Res = _2RxBuffer[0];	// ��ȡ���յ�������
		USART2_RX_BUF[USART2_RX_STA&USART2_RX_STA_REC_NUM] = Res;
		USART2_RX_STA++;
		USART2_RX_BUF[USART2_RX_STA&USART2_RX_STA_REC_NUM] = 0;
		USART2_RX_STA |= USART2_RX_STA_HAS_REC;
		
		// �������ݰ�
		// ����δ���
		if (!(USART2_RX_STA&USART2_RX_STA_REC_END)) {
			if (car_DataPacket_Rx_Flag&0X08) {  // ���յ��˰�ͷ����
				// ����ԭʼ���ݺ�У���
				// �������
				if ((car_DataPacket_Rx_Flag&0X10) || ((car_DataPacket_Rx_Flag&0X07) == BT_DP_TOTAL_BYTE_NUM-2)) {
					car_DataPacket_Rx_Flag |= 0X10;
					// ���հ�β����
					if (Res == BT_DATAPACKET_TAIL_DEFAULT) {  // ���յ��˰�β����
						USART2_RX_STA |= USART2_RX_STA_REC_END;
					} else {  // ���ݰ�����ʧ��
						errTimes++;
						printf("BT rec failed!\r\n");
						USART2_RX_STA &= USART2_RX_STA_OVERFLOW;
					}
					car_DataPacket_Rx_Flag = 0X00;
				} else car_DataPacket_Rx_Flag++;
			} else {
				if (Res == BT_DATAPACKET_HEAD_DEFAULT)  // ���ڽ��յ��ǰ�ͷ����
					car_DataPacket_Rx_Flag |= 0X08;
			}
		}
		
		if (errTimes >= 20) {  // ���մ����������20�ν�����USART3����
			errTimes = 0;
			car_DataPacket_Rx_Flag = 0;
			USART2_RX_STA = 0;
			USART2_RX_BUF[0] = 0;
		}
		
		// ���ջ�����������¿�ʼ����
		if ((USART2_RX_STA&USART2_RX_STA_REC_NUM)>(USART2_REC_LEN-1)) {
			printf("USART2 Rx Buff overflow!\r\n");
			// ��ս�������λ��ͳ��λ�����λ��λ
			USART2_RX_STA &= ~USART2_RX_STA_REC_NUM;
			USART2_RX_STA |=\
			((((USART2_RX_STA&USART2_RX_STA_OVERFLOW) >> 12) + 1)\
			<< 12) & USART2_RX_STA_OVERFLOW;
			// ��ս��ջ�����
			memset(USART2_RX_BUF, 0, USART2_REC_LEN);
		}
	}
}

//UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//�˺����ᱻHAL_UART_Init()����
//huart:���ھ��

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//ʹ��GPIOBʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_6;			//PB6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB6

		GPIO_Initure.Pin=GPIO_PIN_7;			//PB7
		GPIO_Initure.Mode=GPIO_MODE_AF_OD;		//ģʽҪ����Ϊ��������ģʽ��	
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB7
		
#if EN_USART1_RX
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
#endif	
	}
	if(huart->Instance==USART2)//����Ǵ���2�����д���2 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART2_CLK_ENABLE();			//ʹ��USART2ʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA2
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA2

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA3
		GPIO_Initure.Mode=GPIO_MODE_AF_OD;		//ģʽҪ����Ϊ��������ģʽ��	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA3
		
#if EN_USART2_RX
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART2�ж�ͨ��
#endif	
	}
}








