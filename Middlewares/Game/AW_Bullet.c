#define AW_BULLET_ENABLE
#include "AircraftWar.h"

#include "string.h"

const unsigned char bullet_Map1[] = {
	0X00,0X70,0X70,0X70,0X20,0X00
};

/*================================================================
	已发射子弹容器
================================================================*/

/* 已发射子弹 */
typedef AW_Bullet_t  AW_Bullet_Shot_Node;
typedef AW_Bullet_t* AW_Bullet_Shot_Link;
static AW_Bullet_Shot_Link AW_BS_Head = NULL;

/**
 * @fn static AW_Err_Enum_t AW_Bullet_Shot_Add(
 * 	AW_Bullet_Shot_Link *head,
 * 	AW_Bullet_Shot_Node *node
 * )
 * @brief 向双向链表中添加一个子弹
 *
 * @param [head] 双向链表头指针的指针
 * @param [node] 待加入结点的指针
 * @return [AW_Err_Enum_t] 函数执行结果
 *			AW_OK		->	函数执行成功
 *			AW_ERROR	->	函数执行失败
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Add(
	AW_Bullet_Shot_Link *head,
	AW_Bullet_Shot_Node *node
)
{
	if (*head == NULL) {  // 容器中没有子弹指针
		*head = node;
		node->prev = node;
		node->next = node;
	} else {  // 容器中有子弹指针
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
 * @brief 从双向链表中删除一个子弹
 *
 * @param [head] 双向链表头指针的指针
 * @param [node] 待删除结点的指针
 * @return [AW_Err_Enum_t] 函数执行结果
 *			AW_OK		->	函数执行成功
 *			AW_ERROR	->	函数执行失败
 *
 */
static AW_Err_Enum_t AW_Bullet_Shot_Remove(
	AW_Bullet_Shot_Link *head,
	AW_Bullet_Shot_Node *node
)
{
	// 该子弹未发射
	if ((node->prev == NULL) || (node->next == NULL)) {
		return AW_ERROR;
	}
	
	// 双向链表头指针指向待删除结点，需要移动头指针
	if (*head == node) {
		/* 双向链表中只有一个结点 */
		if (node->next == node) *head = NULL;
		/* 双向链表中不只一个结点 */
		else *head = node->next;
	}
	
	// 删除该结点
	if (node->next != NULL) {  // 双向链表中不只一个结点
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	node->prev = NULL;
	node->next = NULL;
	
	return AW_OK;
}

/**
 * @fn void AW_Bullet_Move_CB(void)
 * @brief 已经发射的子弹的回调函数
 *		  用来更新已发射子弹的位置
 * @return [AW_Err_Enum_t] 函数执行结果
 *			AW_OK		->	函数执行成功
 *			AW_ERROR	->	函数执行失败
 *
 */
AW_Err_Enum_t AW_Bullet_Move_CB(void)
{
	AW_Bullet_Shot_Link *head = &AW_BS_Head;
	AW_Bullet_Shot_Node *temp = *head;
	AW_Bullet_Shot_Node *temp_next = NULL;
	
	if(*head == NULL) return AW_ERROR;
	
	do {
		// 防止出现野指针
		if (temp->next != NULL) temp_next = temp->next;
		else {  // 环形链表出现BUG！退出！
			printf("AW_Bullet two-way list has bug!\r\n");
			return AW_ERROR;
		}
		temp->p.x += temp->movementSpeed;
		if (temp->p.x * AW_SS.pixelSize + temp->mapWidth > AW_SS.width) {  // 右溢出
			temp->p.x = (AW_SS.width - temp->mapWidth) / AW_SS.pixelSize;
			if (AW_OK == AW_Bullet_Shot_Remove(head, temp)) {  // 移除溢出的子弹
				temp->isLaunch = 0;
			}
		}
		temp = temp_next;
	} while (temp != *head);
	
	return AW_OK;
}

/*================================================================
	子弹相关函数
================================================================*/

/**
 * @fn void AW_Bullet_Update(void)
 * @brief 将子弹更新到显示载体的缓存中
 * @return [AW_Err_Enum_t] 函数执行结果
 *			AW_OK		->	函数执行成功
 *			AW_ERROR	->	函数执行失败
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
 * @brief 发射一枚子弹
 *
 * @param [bullet] 待发射的子弹的指针
 * @param [p] 子弹发射的起始坐标
 * @return [AW_Err_Enum_t] 函数执行结果
 *			AW_OK		->	函数执行成功
 *			AW_ERROR	->	函数执行失败
 *
 */
AW_Err_Enum_t AW_Bullet_Shoot(AW_Bullet_t *bullet, AW_Point p)
{
	if (bullet->isLaunch != 0) {  // 子弹已发射
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
