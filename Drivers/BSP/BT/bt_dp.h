#ifndef __BT_DP_H
#define __BT_DP_H

#include "bt.h"

#define BT_DATAPACKET_RX_FLAG_NULL						(0X00)
#define BT_DATAPACKET_RX_FLAG_ISSTOP					(0X01)
#define BT_DATAPACKET_RX_FLAG_ISSETACTION				(0X02)
#define BT_DATAPACKET_RX_FLAG_UP						(0X04)
#define BT_DATAPACKET_RX_FLAG_DOWN						(0X08)
#define BT_DATAPACKET_RX_FLAG_LEFT						(0X10)
#define BT_DATAPACKET_RX_FLAG_RIGHT						(0X20)
#define BT_DATAPACKET_RX_FLAG_SHOOT						(0X40)
/* Rx */
#define BT_DP_RAWDATA_BYTE_NUM				(1)								// 数据包中原数据字节数
#define BT_DP_TOTAL_BYTE_NUM				(BT_DP_RAWDATA_BYTE_NUM+3)		// 数据包字节数
typedef struct BT_DataPacket_Rx_RawData{
	// bit6		->	shoot
	// bit5		->	right
	// bit4		->	left
	// bit3		->	down
	// bit2		->	up
	// bit1		->	isSetAction
	// bit0		->	isStop
	int8_t flag;
}BT_DataPacket_Rx_RawData_t;
typedef struct BT_DataPacket_Rx{
	uint8_t packet_Head;
	BT_DataPacket_Rx_RawData_t rawData;
	int8_t check_Byte;
	uint8_t packet_Tail;
}BT_DataPacket_Rx_t;

/* BT接收数据包FIFO */

extern BT_DataPacket_Rx_t dpr[1];

/* BT data packet ---------------------------------------*/

#define BT_DATAPACKET_HEAD_DEFAULT		(0XA5)
#define BT_DATAPACKET_TAIL_DEFAULT		(0X5A)
#define BT_DATAPACKET_TAIL_ERROR		(0X00)

/* BT functions -----------------------------------------*/

void BT_Get_DataPacket_Rx(void);

void BT_DataPacket_Show_USART1(void);

#endif /* __BT_DP_H */
