#include "bt_dp.h"

#include "usart.h"

/*=========================================================
	BT�������ݰ�FIFO
=========================================================*/

BT_DataPacket_Rx_t dpr[1];

/*=========================================================
	BT data packet get
=========================================================*/

/**
 * @fn void BT_Get_DataPacket_Rx(void)
 * @brief �ӽ������ݻ������л�ȡһ�����ݣ������ý��ձ�־λUSART2_RX_STA
 */
void BT_Get_DataPacket_Rx(void)
{
	uint8_t *pRxBuf = USART2_RX_BUF;
	
	if (USART2_RX_STA&USART2_RX_STA_REC_END) {  // �������һ������
		// ��λ��ͷ
		while (*pRxBuf != BT_DATAPACKET_HEAD_DEFAULT) pRxBuf++;
		dpr[0].packet_Head = *pRxBuf; pRxBuf++;
		// ԭʼ����
		dpr[0].rawData.flag = *pRxBuf; pRxBuf++;
		// У���
		dpr[0].check_Byte = *pRxBuf; pRxBuf++;
		// ��β����
		if (*pRxBuf == BT_DATAPACKET_TAIL_DEFAULT) dpr[0].packet_Tail = *pRxBuf;
		else dpr[0].packet_Tail = BT_DATAPACKET_TAIL_ERROR;
		
		// ���ý��ձ�־λ
		USART2_RX_STA &= USART2_RX_STA_OVERFLOW;
	}
}
