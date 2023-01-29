#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
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

/* USART1 ---------------------------------------------------------------------------*/

#define EN_USART1_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1����
#if EN_USART1_RX

#define USART_REC_LEN  			200  		//�����������ֽ��� 200
	  	
extern uint8_t  USART_RX_BUF[USART_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern uint16_t USART_RX_STA;         			//����״̬���	
extern UART_HandleTypeDef UART1_Handler; 	//UART���

#define RXBUFFERSIZE   1 					//�����С
extern uint8_t aRxBuffer[RXBUFFERSIZE];			//HAL��USART����Buffer

#endif /* EN_USART1_RX */

/* USART2 ---------------------------------------------------------------------------*/

#define EN_USART2_RX			(1)			// ʹ�ܴ��ڶ�����
#if EN_USART2_RX

#define USART2_REC_LEN  		(200)  		// �����������ֽ��� 200

extern uint8_t USART2_RX_BUF[USART2_REC_LEN]; 	//���ջ���,���USART2_REC_LEN���ֽ�
#define USART2_RX_STA_REC_END			(0X8000)		// bit15		�������һ������
#define USART2_RX_STA_HAS_REC			(0X4000)		// bit14		�н���
#define USART2_RX_STA_OVERFLOW			(0X3000)		// bit13~12		�������������
#define USART2_RX_STA_REC_NUM			(0X0FFF)		// bit11~0		�����������ַ���
extern uint16_t USART2_RX_STA;         			//����״̬���	
extern UART_HandleTypeDef UART2_Handler; 		//UART2���

#define _2RXBUFFERSIZE   		(1)			// �����С
extern uint8_t _2RxBuffer[_2RXBUFFERSIZE];

#endif /* EN_USART2_RX */

/* function -------------------------------------------------------------------------*/

//����봮���жϽ��գ��벻Ҫע�����º궨��
#if EN_USART1_RX

void uart_init(uint32_t bound);

#endif /* EN_USART1_RX */

#if EN_USART2_RX

void uart2_init(uint32_t bound);

#endif /* EN_USART2_RX */

#endif /* __USART_H */


