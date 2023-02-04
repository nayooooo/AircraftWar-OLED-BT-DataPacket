#include "bt_dp.h"

#include "usart.h"

/*=========================================================
	BT接收数据包FIFO
=========================================================*/

BT_DataPacket_Rx_t dpr[1];

/*=========================================================
	BT data packet get
=========================================================*/

/**
 * @fn void BT_Get_DataPacket_Rx(void)
 * @brief 从接收数据缓冲区中获取一包数据，并重置接收标志位USART2_RX_STA
 */
void BT_Get_DataPacket_Rx(void)
{
	uint8_t *pRxBuf = USART2_RX_BUF;
	
	if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // 接收完毕一包数据
		// 定位包头
		while (*pRxBuf != BT_DATAPACKET_HEAD_DEFAULT) pRxBuf++;
		dpr[0].packet_Head = *pRxBuf; pRxBuf++;
		// 原始数据
		dpr[0].rawData.flag = *pRxBuf; pRxBuf++;
		// 校验和
		dpr[0].check_Byte = *pRxBuf; pRxBuf++;
		// 包尾数据
		if (*pRxBuf == BT_DATAPACKET_TAIL_DEFAULT) dpr[0].packet_Tail = *pRxBuf;
		else dpr[0].packet_Tail = BT_DATAPACKET_TAIL_ERROR;
		
		// 重置接收标志位
		USART2_RX_STA &= USART2_RX_STA_OVERFLOW;
	}
}

/*=========================================================
	BT data packet show
=========================================================*/

/**
 * @fn BT_Err_Enum_t BT_DataPacket_Printf(void)
 * @brief 通过串口1打印蓝牙接收到的数据包
 * @details 接收到的数据包必须是正确的数据包
 *
 * @return [BT_Err_Enum_t] 函数执行状态
 *			BT_OK		->	函数执行正确
 *			BT_ERROR	->	函数执行错误
 *
 */
void BT_DataPacket_Printf(void)
{
	int8_t temp = dpr[0].rawData.flag;
	
	if (dpr[0].check_Byte != temp) {
		printf("\r\n");
		printf("rec dp err!\r\n");
		return;
	}
	
	printf("\r\n");
	printf("========================================\r\n");
	printf("dpr->PH:   %d\r\n", dpr[0].packet_Head);
	printf("dpr->flag: %d\r\n", dpr[0].rawData.flag);
	printf("dpr->CB:   %d\r\n", dpr[0].check_Byte);
	printf("dpr->PT:   %d\r\n", dpr[0].packet_Tail);
	printf("========================================\r\n");
	printf("\r\n");
	
	return;
}
