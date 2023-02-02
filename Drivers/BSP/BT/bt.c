#include "bt.h"
#include "stdio.h"
#include "string.h"

#include "usart.h"

/*=========================================================
	BT状态机列表
=========================================================*/

#include "bt_event.h"
static BT_StateTable_t BT_StateTable[] = {
	{ BT_STATETABLE_STOP, BT_Stop },						// BT停止
	{ BT_STATETABLE_SETACTION, BT_SetAction },				// BT设置动作
	{ BT_STATETABLE_TURNUP, BT_Up },						// BT上
	{ BT_STATETABLE_TURNDOWN, BT_Down },					// BT下
	{ BT_STATETABLE_TURNLEFT, BT_Left },					// BT左
	{ BT_STATETABLE_TURNRIGHT, BT_Right },					// BT右
	{ BT_STATETABLE_SHOOT, BT_Shoot },						// BT发射子弹
	{ BT_STATETABLE_NULL, NULL },							// 状态机列表末尾
};

/*=========================================================
	BT data packet Rx decode and handle
=========================================================*/

/**
 * @fn static BT_StateTable_Event_Arr_t *BT_DataPacket_Rx_Decode(BT_DataPacket_Rx_t dpr)
 * @brief 解码一帧正确的接收数据包，并以事件组结构体的形式返回解码信息
 * @details 该函数不会检查接收数据包的正确性，请开发人员传入数据包之前检查一下
 *
 * @return [BT_StateTable_Event_Arr_t*] BT事件列表及事件数目
 */
static BT_StateTable_Event_Arr_t *BT_DataPacket_Rx_Decode(BT_DataPacket_Rx_t dpr)
{
	static BT_StateTable_Event_Arr_t event;
	uint8_t i;
	uint8_t temp;
	
	// 初始化事件组
	event.num = 0;
	memset(event.events, 0, sizeof(event.events));
	
	// 解码
	/* 标志位 */
	i = -1;
	do {
		i++;
		temp = 0X01 << i;
		if (dpr.rawData.flag&temp) {
			event.events[event.num] = i + 1;
			event.num++;
		}
	} while(temp != BT_STATETABLE_ENDER);
	/* 变量 */
	
	return &event;
}

/**
 * @fn void BT_DataPacket_Rx_Handle(void)
 * @brief 接收数据包处理函数
 */
void BT_DataPacket_Rx_Handle(void)
{
	uint8_t i, j;
	int8_t temp;
	const BT_StateTable_Event_Arr_t *event;
	
	temp = dpr[0].rawData.flag;
	// 接收数据错误
	if ((dpr[0].packet_Tail == BT_DATAPACKET_TAIL_ERROR) || (temp != dpr[0].check_Byte)) {
		printf("Car BLE rec data packet error!\r\n");
		return;
	}
	// 接收数据正确
	event = BT_DataPacket_Rx_Decode(dpr[0]);  // 解码获取事件组
	// 回应状态机事件
	for (i = 0; i < event->num; i++) {
		for (j = 0; BT_StateTable[j].event; j++) {  // 遍历状态机列表
			if (event->events[i] == BT_StateTable[j].event) {
				BT_StateTable[j].act();
				break;
			}
		}
	}
}

/*=========================================================
	BT initialization
=========================================================*/

static void BT_USART_Init(uint32_t bound)
{
	uart2_init(bound);
}

void BT_Init(void)
{
	BT_USART_Init(BT_BOUND_RATE);
	
	printf("\r\n");
	printf("***************************************************\r\n");
	printf("         STM32G030F6P6 BT has initialized!\r\n");
	printf("***************************************************\r\n");
	printf("\r\n");
}
