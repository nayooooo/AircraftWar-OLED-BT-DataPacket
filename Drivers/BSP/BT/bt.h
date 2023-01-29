#ifndef __BT_H
#define __BT_H

#include "sys.h"

#include "bt_dp.h"

/* BT micro ----------------------------------------------*/

#define BT_BOUND_RATE					(9600UL)

/* BT state machine --------------------------------------*/

// BT事件枚举
typedef enum{
	BT_STATEMACHINE_NULL,						// BT无事件
	BT_STATEMACHINE_STOP,						// BT停止
	BT_STATEMACHINE_SETACTION,					// BT设置动作
	BT_STATEMACHINE_TURNUP,						// BT前进
	BT_STATEMACHINE_TURNDOWN,					// BT后退
	BT_STATEMACHINE_TURNLEFT,					// BT左转
	BT_STATEMACHINE_TURNRIGHT,					// BT右转
}BT_StateMachine_Event_Enum_t;
typedef struct BT_StateMachine_Event_Arr{
	uint8_t num;			// 本次解码的事件数目
	// 本次解码的事件列表
	BT_StateMachine_Event_Enum_t events[\
		BT_STATEMACHINE_FLAG_EVENT + BT_STATEMACHINE_VARI_EVENT];
}BT_StateMachine_Event_Arr_t;
typedef void(*BT_StateMachine_Action)(void);
typedef struct{
	BT_StateMachine_Event_Enum_t event;		// BT事件
	BT_StateMachine_Action act;				// BT动作
}BT_StateMachine_t;

/* BT functions ------------------------------------------*/

void BT_Init(void);

void BT_DataPacket_Rx_Handle(void);

#endif /* __BLE_H */
