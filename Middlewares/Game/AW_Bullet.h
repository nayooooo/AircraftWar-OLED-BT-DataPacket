#ifndef __AW_BULLET_H
#define __AW_BULLET_H

#include "AW_def.h"

/*================================================================
	�ӵ��ṹ��
================================================================*/

typedef struct AW_Bullet{
	uint8_t isLaunch: 1;		// �ӵ������ȥ��
	AW_Point p;					// λ������
} AW_Bullet_t;

#endif /* __AW_BULLET_H */
