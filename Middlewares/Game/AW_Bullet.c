#define AW_BULLET_ENABLE
#include "AircraftWar.h"

#include "string.h"

/*================================================================
	已发射子弹容器
================================================================*/

/**
 * @fn void AW_Bullet_Move_CB(void)
 * @brief 已经发射的子弹的回调函数
 *		  用来更新已发射子弹的位置
 *
 */
void AW_Bullet_Move_CB(void)
{
}

/*================================================================
	子弹相关函数
================================================================*/

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
	bullet->isLaunch = 1;
	
	return AW_OK;
}
