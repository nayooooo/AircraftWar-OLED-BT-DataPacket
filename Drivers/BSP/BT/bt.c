#include "bt.h"
#include "stdio.h"
#include "string.h"

#include "usart.h"

/*=========================================================
	extern BT action
=========================================================*/

static void BT_Up(void);
static void BT_Down(void);
static void BT_Left(void);
static void BT_Right(void);

static void BT_SetAction(void);

static void BT_Move(void);
static void BT_Stop(void);

/*=========================================================
	BT״̬���б�
=========================================================*/

static BT_StateTable_t BT_StateTable[] = {
	{ BT_STATETABLE_STOP, BT_Stop },									// BTֹͣ
	{ BT_STATETABLE_SETACTION, BT_SetAction },							// BT���ö���
	{ BT_STATETABLE_TURNUP, BT_Up },									// BT��
	{ BT_STATETABLE_TURNDOWN, BT_Down },								// BT��
	{ BT_STATETABLE_TURNLEFT, BT_Left },								// BT��
	{ BT_STATETABLE_TURNRIGHT, BT_Right },								// BT��
	{ BT_STATETABLE_NULL, NULL },										// ״̬���б�ĩβ
};

/*=========================================================
	BT action
=========================================================*/

static void BT_Up(void)
{
	printf("BT_Up\r\n");
}

static void BT_Down(void)
{
	printf("BT_Down\r\n");
}

static void BT_Left(void)
{
	printf("BT_Left\r\n");
}

static void BT_Right(void)
{
	printf("BT_Right\r\n");
}

static void BT_SetAction(void)
{
	printf("BT_SetAction\r\n");
}

static void BT_Move(void)
{
	printf("BT_Move\r\n");
}

static void BT_Stop(void)
{
	printf("BT_Stop\r\n");
}

/*=========================================================
	BT data packet Rx decode and handle
=========================================================*/

/**
 * @fn static BT_StateTable_Event_Arr_t *BT_DataPacket_Rx_Decode(BT_DataPacket_Rx_t dpr)
 * @brief ����һ֡��ȷ�Ľ������ݰ��������¼���ṹ�����ʽ���ؽ�����Ϣ
 * @details �ú���������������ݰ�����ȷ�ԣ��뿪����Ա�������ݰ�֮ǰ���һ��
 *
 * @return [BT_StateTable_Event_Arr_t*] BT�¼��б��¼���Ŀ
 */
static BT_StateTable_Event_Arr_t *BT_DataPacket_Rx_Decode(BT_DataPacket_Rx_t dpr)
{
	static BT_StateTable_Event_Arr_t event;
	uint8_t i;
	uint8_t temp;
	
	// ��ʼ���¼���
	event.num = 0;
	memset(event.events, 0, sizeof(event.events));
	
	// ����
	/* ��־λ */
	i = -1;
	do {
		i++;
		temp = 0X01 << i;
		if (dpr.rawData.flag&temp) {
			event.events[event.num] = i + 1;
			event.num++;
		}
	} while(temp != BT_DATAPACKET_RX_FLAG_RIGHT);
	/* ���� */
	
	return &event;
}

/**
 * @fn void BT_DataPacket_Rx_Handle(void)
 * @brief �������ݰ�������
 */
void BT_DataPacket_Rx_Handle(void)
{
	uint8_t i, j;
	int8_t temp;
	const BT_StateTable_Event_Arr_t *event;
	
	temp = dpr[0].rawData.flag;
	// �������ݴ���
	if ((dpr[0].packet_Tail == BT_DATAPACKET_TAIL_ERROR) || (temp != dpr[0].check_Byte)) {
		printf("Car BLE rec data packet error!\r\n");
		return;
	}
	// ����������ȷ
	event = BT_DataPacket_Rx_Decode(dpr[0]);  // �����ȡ�¼���
	// ��Ӧ״̬���¼�
	for (i = 0; i < event->num; i++) {
		for (j = 0; BT_StateTable[j].event; j++) {  // ����״̬���б�
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
