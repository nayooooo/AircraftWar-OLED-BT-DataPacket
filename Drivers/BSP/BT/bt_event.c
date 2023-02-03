#include "bt_event.h"

#include "stdio.h"
#include "string.h"

#include "AircraftWar.h"
#include "AW_Player.h"

/*=========================================================
	BT action
=========================================================*/

void BT_Up(void)
{
	Point p;
	
	printf("BT_Up\r\n");
	
	memcpy(&p, AW_Player_Get_Coor(), sizeof(Point));
	p.y -= BT_EVENT_AW_MOVE_YPIXEL_STEP;
	if (p.y * AW_SS.pixelSize > AW_SS.height) p.y = 0;
	AW_Player_Move(p);
}

void BT_Down(void)
{
	Point p;
	
	printf("BT_Down\r\n");
	
	memcpy(&p, AW_Player_Get_Coor(), sizeof(Point));
	p.y += BT_EVENT_AW_MOVE_YPIXEL_STEP;
	if (p.y * AW_SS.pixelSize + AW_Player_Get_Height() > AW_SS.height)
		p.y = (AW_SS.height - AW_Player_Get_Height()) / AW_SS.pixelSize;
	AW_Player_Move(p);
}

void BT_Left(void)
{
	Point p;
	
	printf("BT_Left\r\n");
	
	memcpy(&p, AW_Player_Get_Coor(), sizeof(Point));
	p.x -= BT_EVENT_AW_MOVE_XPIXEL_STEP;
	if (p.x * AW_SS.pixelSize > AW_SS.width) p.x = 0;
	AW_Player_Move(p);
}

void BT_Right(void)
{
	Point p;
	
	printf("BT_Right\r\n");
	
	memcpy(&p, AW_Player_Get_Coor(), sizeof(Point));
	p.x += BT_EVENT_AW_MOVE_XPIXEL_STEP;
	if (p.x * AW_SS.pixelSize + AW_Player_Get_Width() > AW_SS.width)
		p.x = (AW_SS.width - AW_Player_Get_Width()) / AW_SS.pixelSize;
	AW_Player_Move(p);
}

void BT_Shoot(void)
{
	AW_Bullet_t *b = NULL;
	b = AW_Player_Get_First_Ready_Bullet();
	if (b != NULL) {
		AW_Bullet_Shoot(b, *AW_Player_Get_Coor());
		printf("player have shot a bullet!\r\n");
	} else printf("player have no bullet!\r\n");
}

void BT_SetAction(void)
{
	printf("BT_SetAction\r\n");
}

void BT_Move(void)
{
	printf("BT_Move\r\n");
}

void BT_Stop(void)
{
	printf("BT_Stop\r\n");
}
