#define AW_BULLET_ENABLE
#include "AircraftWar.h"

#include "string.h"

/*================================================================
	�ѷ����ӵ�����
================================================================*/

/* �ѷ����ӵ� */
typedef struct AW_Bullet_Shot{
	struct AW_Bullet_Shot *prev;
	struct AW_Bullet_Shot *next;
	AW_Bullet_t *bullet;
}AW_Bullet_Shot_Node, *AW_Bullet_Shot_Link;
static AW_Bullet_Shot_Link AW_BS_Head = NULL;

/**
 * @fn static AW_Err_Enum_t AW_Bullet_Shot_Add(
 * 	AW_Bullet_Shot_Link head,
 * 	AW_Bullet_Shot_Node *node
 * )
 * @brief ��˫�����������һ���ӵ�
 *
 * @param [head] ˫������ͷָ��
 * @param [node] ���������ָ��
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Add(
	AW_Bullet_Shot_Link head,
	AW_Bullet_Shot_Node *node
)
{
	if (head == NULL) {  // ������û���ӵ�ָ��
		head = node;
		node->prev = node;
		node->next = node;
	} else {  // ���������ӵ�ָ��
		node->prev = head->prev;
		node->next = head;
		head->prev->next = node;
		head->prev = node;
	}
	return AW_OK;
}

/**
 * @fn static AW_Err_Enum_t AW_Bullet_Shot_Remove(
 * 	AW_Bullet_Shot_Link head,
 * 	AW_Bullet_Shot_Node *node
 * )
 * @brief ��˫��������ɾ��һ���ӵ�
 *
 * @param [head] ˫������ͷָ��
 * @param [node] ��ɾ������ָ��
 * @return [AW_Err_Enum_t] ����ִ�н��
 *			AW_OK		->	����ִ�гɹ�
 *			AW_ERROR	->	����ִ��ʧ��
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Remove(
	AW_Bullet_Shot_Link head,
	AW_Bullet_Shot_Node *node
)
{
	// ���ӵ�δ����
	if ((node->prev == NULL) || (node->next == NULL)) {
		return AW_ERROR;
	}
	
	// ˫������ͷָ��ָ���ɾ����㣬��Ҫ�ƶ�ͷָ��
	if (head == node) {
		/* ˫��������ֻ��һ����� */
		if (node->next == node) head = NULL;
		/* ˫�������в�ֻһ����� */
		else head = node->next;
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
 *
 */
void AW_Bullet_Move_CB(void)
{
}

/*================================================================
	�ӵ���غ���
================================================================*/

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
	bullet->isLaunch = 1;
	
	return AW_OK;
}
