#ifndef __BT_EVENT_H
#define __BT_EVENT_H

#include "bt.h"

/*=========================================================
	BT config micro
=========================================================*/

#define BT_EVENT_AW_MOVE_XPIXEL_STEP			(6)			/* ��ҽ�ɫx�᷽��λ�Ʋ��� */
#define BT_EVENT_AW_MOVE_YPIXEL_STEP			(4)			/* ��ҽ�ɫy�᷽��λ�Ʋ��� */

/*=========================================================
	extern BT action
=========================================================*/

void BT_Up(void);
void BT_Down(void);
void BT_Left(void);
void BT_Right(void);

void BT_SetAction(void);

void BT_Move(void);
void BT_Stop(void);

#endif /* __BT_EVENT_H */
