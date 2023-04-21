#include "stdafx.h"
#include "Cloud.h"

extern int cx;

Cloud::Cloud(int y, int speed)
{
	xPos = cx + rand()%800;
	yPos = y;
	xSpeed = speed;
	alive = true;
}


Cloud::~Cloud()
{
}
void Cloud::Move() {
	xPos -= xSpeed;
	if (xPos < -200)
		alive = false;
}

void Cloud::Paint(HDC hdc) {
	Move();
	HPEN hPen = CreatePen(PS_JOIN_ROUND, 1, RGB(192, 192, 192));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	Arc(hdc, xPos + 40, yPos + 10, xPos + 120, yPos + 60, xPos + 120, yPos + 30, xPos + 40, yPos + 30);
	Arc(hdc, xPos, yPos + 30, xPos + 90, yPos + 80, xPos + 100, yPos + 30, xPos + 90, yPos + 70);
	Arc(hdc, xPos + 70, yPos + 30, xPos + 160, yPos + 80, xPos + 70, yPos + 70, xPos + 110, yPos + 30);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}

