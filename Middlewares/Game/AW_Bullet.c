#define AW_BULLET_ENABLE
#include "AircraftWar.h"

#include "string.h"

/*================================================================
	�ѷ����ӵ�����
================================================================*/

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
