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

/*=========================================================
	BT data packet show
=========================================================*/

/**
 * @fn BT_Err_Enum_t BT_DataPacket_Printf(void)
 * @brief ͨ������1��ӡ�������յ������ݰ�
 * @details ���յ������ݰ���������ȷ�����ݰ�
 *
 * @return [BT_Err_Enum_t] ����ִ��״̬
 *			BT_OK		->	����ִ����ȷ
 *			BT_ERROR	->	����ִ�д���
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
