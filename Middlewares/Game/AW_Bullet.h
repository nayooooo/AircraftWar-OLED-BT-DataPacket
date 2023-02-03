#ifndef __AW_BULLET_H
#define __AW_BULLET_H

#include "AW_def.h"

/*================================================================
	�ӵ��ṹ��
================================================================*/

typedef struct AW_Bullet{
	struct AW_Bullet *prev;
	struct AW_Bullet *next;
	uint8_t isLaunch: 1;		// �ӵ������ȥ��
	uint8_t shootDir;			// �ӵ����䷽��
	AW_Point p;					// λ������
} AW_Bullet_t;

/*================================================================
	�ӵ���غ�
================================================================*/

typedef enum{
	AW_Bullet_Shoot_Right,				// ��������
	AW_Bullet_Shoot_left,				// ��������
}AW_Bullet_Shoot_Dir_Enum_t;
#define AW_BULLET_PLAYER_SHOOT_DIR				(AW_Bullet_Shoot_Right)		/* ��ҽ�ɫ�����ӵ����� */
#define AW_BULLET_ENEMY_SHOOT_DIR				(AW_Bullet_Shoot_left)		/* �л������ӵ����� */

/*================================================================
	�ӵ���غ���
================================================================*/

AW_Err_Enum_t AW_Bullet_Init(AW_Bullet_t *bullet);

AW_Err_Enum_t AW_Bullet_Shoot(AW_Bullet_t *bullet, AW_Point p);

#endif /* __AW_BULLET_H */
