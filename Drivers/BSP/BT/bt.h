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

#define BT_STATETABLE_FLAG_EVENT			(7)		// ��־λ�¼���Ŀ
#define BT_STATETABLE_VARI_EVENT			(0)		// �����¼���Ŀ

/* BT state machine --------------------------------------*/

// BT�¼�ö��
typedef enum{
	BT_STATETABLE_NULL,						// BT���¼�
	BT_STATETABLE_STOP,						// BTֹͣ
	BT_STATETABLE_SETACTION,				// BT���ö���
	BT_STATETABLE_TURNUP,					// BTǰ��
	BT_STATETABLE_TURNDOWN,					// BT����
	BT_STATETABLE_TURNLEFT,					// BT��ת
	BT_STATETABLE_TURNRIGHT,				// BT��ת
	BT_STATETABLE_SHOOT,					// BT�����ӵ�
}BT_StateTable_Event_Enum_t;

typedef struct BT_StateTable_Event_Arr{
	uint8_t num;			// ���ν�����¼���Ŀ
	// ���ν�����¼��б�
	BT_StateTable_Event_Enum_t events[\
		BT_STATETABLE_FLAG_EVENT + BT_STATETABLE_VARI_EVENT];
}BT_StateTable_Event_Arr_t;
typedef void(*BT_StateTable_Action)(void);
typedef struct{
	BT_StateTable_Event_Enum_t event;		// BT�¼�
	BT_StateTable_Action act;				// BT����
}BT_StateTable_t;

/* BT functions ------------------------------------------*/

void BT_Init(void);

void BT_DataPacket_Rx_Handle(void);

#endif /* __BLE_H */
