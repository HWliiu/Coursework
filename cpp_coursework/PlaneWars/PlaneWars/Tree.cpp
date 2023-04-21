#include "stdafx.h"
#include "Tree.h"

extern int cx;

Tree::Tree(int speed)
{
	xPos = cx + rand() % 500;
	yPos = 583;
	xSpeed = speed;
	alive = true;
}


Tree::~Tree()
{
}

void Tree::Move() {
	xPos -= xSpeed;
	if (xPos < -200)
		alive = false;
}

void Tree::Paint(HDC hdc) {
	Move();
	HBRUSH hBrush = CreateSolidBrush(RGB(128, 64, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, xPos + 33, yPos + 75, xPos + 48, yPos + 99);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	HBRUSH hBrush1 = CreateSolidBrush(RGB(0, 128, 0));
	HBRUSH hOldBrush1 = (HBRUSH)SelectObject(hdc, hBrush1);
	POINT points[13] = { 34 + xPos,1 + yPos,7 + xPos,28 + yPos,23 + xPos,31 + yPos,4 + xPos,51 + yPos,22 + xPos,55 + yPos,2 + xPos,70 + yPos,
		27 + xPos,77 + yPos,53 + xPos,77 + yPos,76 + xPos,70 + yPos,53 + xPos,55 + yPos,71 + xPos,45 + yPos,49 + xPos,29 + yPos,65 + xPos,24 + yPos };
	Polygon(hdc, points, 13);
	SelectObject(hdc, hOldBrush1);
	DeleteObject(hBrush1);
}
