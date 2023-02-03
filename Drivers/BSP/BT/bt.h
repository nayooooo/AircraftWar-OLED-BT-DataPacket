#ifndef __BT_H
#define __BT_H

#include "sys.h"

#include "bt_dp.h"

typedef enum{
	BT_OK = 0,
	BT_ERROR = 1
} BT_Err_Enum_t;

/* BT micro ----------------------------------------------*/

#define BT_BOUND_RATE					(115200UL)

/* BT state table ---------------------------------------*/

#define BT_STATETABLE_FLAG_EVENT			(7)		// 标志位事件数目
#define BT_STATETABLE_VARI_EVENT			(0)		// 变量事件数目

/* BT state machine --------------------------------------*/

// BT事件枚举
typedef enum{
	BT_STATETABLE_NULL,						// BT无事件
	BT_STATETABLE_STOP,						// BT停止
	BT_STATETABLE_SETACTION,				// BT设置动作
	BT_STATETABLE_TURNUP,					// BT前进
	BT_STATETABLE_TURNDOWN,					// BT后退
	BT_STATETABLE_TURNLEFT,					// BT左转
	BT_STATETABLE_TURNRIGHT,				// BT右转
	BT_STATETABLE_SHOOT,					// BT发射子弹
}BT_StateTable_Event_Enum_t;

typedef struct BT_StateTable_Event_Arr{
	uint8_t num;			// 本次解码的事件数目
	// 本次解码的事件列表
	BT_StateTable_Event_Enum_t events[\
		BT_STATETABLE_FLAG_EVENT + BT_STATETABLE_VARI_EVENT];
}BT_StateTable_Event_Arr_t;
typedef void(*BT_StateTable_Action)(void);
typedef struct{
	BT_StateTable_Event_Enum_t event;		// BT事件
	BT_StateTable_Action act;				// BT动作
}BT_StateTable_t;

/* BT functions ------------------------------------------*/

void BT_Init(void);

void BT_DataPacket_Rx_Handle(void);

#endif /* __BLE_H */
