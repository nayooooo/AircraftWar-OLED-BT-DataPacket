#define AW_BULLET_ENABLE
#include "AircraftWar.h"

#include "string.h"

const unsigned char bullet_Map1[] = {
	0X00,0X70,0X70,0X70,0X20,0X00
};

/*================================================================
	�ѷ����ӵ�����
================================================================*/

/* �ѷ����ӵ� */
typedef AW_Bullet_t  AW_Bullet_Shot_Node;
typedef AW_Bullet_t* AW_Bullet_Shot_Link;
static AW_Bullet_Shot_Link AW_BS_Head = NULL;

/**
 * @fn static AW_Err_Enum_t AW_Bullet_Shot_Add(
 * 	AW_Bullet_Shot_Link *head,
 * 	AW_Bullet_Shot_Node *node
 * )
 * @brief ��˫�����������һ���ӵ�
 *
 * @param [head] ˫������ͷָ���ָ��
 * @param [node] ���������ָ��
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Add(
	AW_Bullet_Shot_Link *head,
	AW_Bullet_Shot_Node *node
)
{
	if (*head == NULL) {  // ������û���ӵ�ָ��
		*head = node;
		node->prev = node;
		node->next = node;
	} else {  // ���������ӵ�ָ��
		node->prev = (*head)->prev;
		node->next = *head;
		(*head)->prev->next = node;
		(*head)->prev = node;
	}
	return AW_OK;
}

/**
 * @fn static AW_Err_Enum_t AW_Bullet_Shot_Remove(
 * 	AW_Bullet_Shot_Link *head,
 * 	AW_Bullet_Shot_Node *node
 * )
 * @brief ��˫��������ɾ��һ���ӵ�
 *
 * @param [head] ˫������ͷָ���ָ��
 * @param [node] ��ɾ������ָ��
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Remove(
	AW_Bullet_Shot_Link *head,
	AW_Bullet_Shot_Node *node
)
{
	// ���ӵ�δ����
	if ((node->prev == NULL) || (node->next == NULL)) {
		return AW_ERROR;
	}
	
	// ˫������ͷָ��ָ���ɾ����㣬��Ҫ�ƶ�ͷָ��
	if (*head == node) {
		/* ˫��������ֻ��һ����� */
		if (node->next == node) *head = NULL;
		/* ˫�������в�ֻһ����� */
		else *head = node->next;
	}
	
	// ɾ���ý��
	if (node->next != NULL) {  // ˫�������в�ֻһ�����
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	node->prev = NULL;
	node->next = NULL;
	
	return AW_OK;
}

/**
 * @fn void AW_Bullet_Move_CB(void)
 * @brief �Ѿ�������ӵ��Ļص�����
 *		  ���������ѷ����ӵ���λ��
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
AW_Err_Enum_t AW_Bullet_Move_CB(void)
{
	AW_Bullet_Shot_Link *head = &AW_BS_Head;
	AW_Bullet_Shot_Node *temp = *head;
	AW_Bullet_Shot_Node *temp_next = NULL;
	
	if(*head == NULL) return AW_ERROR;
	
	do {
		// ��ֹ����Ұָ��
		if (temp->next != NULL) temp_next = temp->next;
		else {  // �����������BUG���˳���
			printf("AW_Bullet two-way list has bug!\r\n");
			return AW_ERROR;
		}
		temp->p.x += temp->movementSpeed;
		if (temp->p.x * AW_SS.pixelSize + temp->mapWidth > AW_SS.width) {  // �����
			temp->p.x = (AW_SS.width - temp->mapWidth) / AW_SS.pixelSize;
			if (AW_OK == AW_Bullet_Shot_Remove(head, temp)) {  // �Ƴ�������ӵ�
				temp->isLaunch = 0;
			}
		}
		temp = temp_next;
	} while (temp != *head);
	
	return AW_OK;
}

/*================================================================
	�ӵ���غ���
================================================================*/

/**
 * @fn void AW_Bullet_Update(void)
 * @brief ���ӵ����µ���ʾ����Ļ�����
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
AW_Err_Enum_t AW_Bullet_Update(void)
{
	AW_Bullet_Shot_Link *head = &AW_BS_Head;
	AW_Bullet_Shot_Node *temp = *head;
	
	if(*head == NULL) return AW_ERROR;
	
	do {
		OLED_ShowBMP(temp->p.x * AW_SS.pixelSize, temp->p.y * AW_SS.pixelSize,
						temp->map, temp->mapWidth, temp->mapHeight, FILL);
		temp = temp->next;
	} while (temp != *head);
	
	return AW_OK;
}

/**
 * @fn AW_Err_Enum_t AW_Bullet_Shoot(AW_Bullet_t *bullet, AW_Point p)
 * @brief ����һö�ӵ�
 *
 * @param [bullet] ��������ӵ���ָ��
 * @param [p] �ӵ��������ʼ����
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
AW_Err_Enum_t AW_Bullet_Shoot(AW_Bullet_t *bullet, AW_Point p)
{
	if (bullet->isLaunch != 0) {  // �ӵ��ѷ���
		return AW_ERROR;
	}
	
	memcpy(&(bullet->p), &p, sizeof(AW_Point));
	if (AW_OK == AW_Bullet_Shot_Add(&AW_BS_Head, bullet))
		bullet->isLaunch = 1;
	else return AW_ERROR;
	
	return AW_OK;
}

AW_Err_Enum_t AW_Bullet_Init(AW_Bullet_t *bullet)
{
	bullet->prev = NULL;
	bullet->next = NULL;
	bullet->isLaunch = 0;
	bullet->shootDir = AW_BULLET_PLAYER_SHOOT_DIR;
	bullet->movementSpeed = 5;
	bullet->p.x = 0;
	bullet->p.y = 0;
	bullet->map = bullet_Map1;
	bullet->mapWidth = 6;
	bullet->mapHeight = 5;
	
	return AW_OK;
}
