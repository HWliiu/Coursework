#include "stdafx.h"
#include "Grass.h"

extern int cx;

Grass::Grass(int speed)
{
	xPos = cx + rand() % 500;
	yPos = 650;
	xSpeed = speed;
	alive = true;
}


Grass::~Grass()
{
}

void Grass::Move() {
	xPos -= xSpeed;
	if (xPos < -200)
		alive = false;
}

void Grass::Paint(HDC hdc) {
	Move();
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 128, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	POINT points[11] = { 11 + xPos,29 + yPos,1 + xPos ,18 + yPos,11 + xPos ,23 + yPos,6 + xPos ,11 + yPos,14 + xPos ,20 + yPos,17 + xPos ,0 + yPos,
	18 + xPos ,19 + yPos,26 + xPos ,5 + yPos,22 + xPos,21 + yPos,30 + xPos ,14 + yPos,19 + xPos ,29 + yPos };
	Polygon(hdc, points, 11);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

