#ifndef __BT_H
#define __BT_H

#include "sys.h"

#include "bt_dp.h"

/* BT micro ----------------------------------------------*/

#define BT_BOUND_RATE					(9600UL)

/* BT state machine --------------------------------------*/

// BT�¼�ö��
typedef enum{
	BT_STATEMACHINE_NULL,						// BT���¼�
	BT_STATEMACHINE_STOP,						// BTֹͣ
	BT_STATEMACHINE_SETACTION,					// BT���ö���
	BT_STATEMACHINE_TURNUP,						// BTǰ��
	BT_STATEMACHINE_TURNDOWN,					// BT����
	BT_STATEMACHINE_TURNLEFT,					// BT��ת
	BT_STATEMACHINE_TURNRIGHT,					// BT��ת
}BT_StateMachine_Event_Enum_t;
typedef struct BT_StateMachine_Event_Arr{
	uint8_t num;			// ���ν�����¼���Ŀ
	// ���ν�����¼��б�
	BT_StateMachine_Event_Enum_t events[\
		BT_STATEMACHINE_FLAG_EVENT + BT_STATEMACHINE_VARI_EVENT];
}BT_StateMachine_Event_Arr_t;
typedef void(*BT_StateMachine_Action)(void);
typedef struct{
	BT_StateMachine_Event_Enum_t event;		// BT�¼�
	BT_StateMachine_Action act;				// BT����
}BT_StateMachine_t;

/* BT functions ------------------------------------------*/

void BT_Init(void);

void BT_DataPacket_Rx_Handle(void);

#endif /* __BLE_H */
