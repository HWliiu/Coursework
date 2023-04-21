#include "stdafx.h"
#include "Ufo.h"

extern int cx;

Ufo::Ufo(int y,int speed)
{
	xPos = cx + rand()%800;
	yPos = y;
	xSpeed = speed;
	health = 10;
}


Ufo::~Ufo()
{
}

void Ufo::Move() {
	xPos += xSpeed;
	if (xPos < -200)
		alive = false;
	collisionDectection();
}

void Ufo::Paint(HDC hdc) {
	Move();
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(128, 128, 255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Chord(hdc, 20 + xPos, 0 + yPos, 80 + xPos, 50 + yPos, 100 + xPos, 20 + yPos, 0 + xPos, 20 + yPos);
	Ellipse(hdc,10 + xPos,35 + yPos,40 + xPos,55 + yPos);
	Ellipse(hdc,60 + xPos,35 + yPos,90 + xPos,55 + yPos);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);


	Ellipse(hdc, 0 + xPos, 10 + yPos, 100 + xPos, 50 + yPos);
	
	HBRUSH hBrush1 = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
	HBRUSH hOldBrush1 = (HBRUSH)SelectObject(hdc, hBrush1);
	Ellipse(hdc, 15 + xPos, 25 + yPos, 25 + xPos, 35 + yPos);
	SelectObject(hdc, hOldBrush1);
	DeleteObject(hBrush1);
	HBRUSH hBrush2 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	HBRUSH hOldBrush2 = (HBRUSH)SelectObject(hdc, hBrush2);
	Ellipse(hdc, 35 + xPos, 30 + yPos, 45 + xPos, 40 + yPos);
	SelectObject(hdc, hOldBrush2);
	DeleteObject(hBrush2);
	HBRUSH hBrush3 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	HBRUSH hOldBrush3 = (HBRUSH)SelectObject(hdc, hBrush3);
	Ellipse(hdc, 55 + xPos, 30 + yPos, 65 + xPos, 40 + yPos);
	SelectObject(hdc, hOldBrush3);
	DeleteObject(hBrush3);
	HBRUSH hBrush4 = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	HBRUSH hOldBrush4 = (HBRUSH)SelectObject(hdc, hBrush4);
	Ellipse(hdc, 75 + xPos, 25 + yPos, 85 + xPos, 35 + yPos);
	SelectObject(hdc, hOldBrush4);
	DeleteObject(hBrush4);
	

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);


	wchar_t  hp[10];
	RECT rect;
	SetTextColor(hdc, RGB(255, 0, 64));
	swprintf(hp, 255, _T("hp:%d"), health);
	rect.left = xPos, rect.right = xPos + 100;
	rect.top = yPos - 20; rect.bottom = yPos;
	DrawText(hdc, hp, -1, &rect, DT_CENTER);
	
}

void Ufo::collisionDectection() {
	collider.UpdateRegion(xPos, xPos + 100, yPos, yPos + 55);
	for (int i = 0; i < rigidBodyCount; i++) {
		if (existRigidBody[i] != this && collider.CollidTo(&(existRigidBody[i]->collider))) {
			if(health <= 0)
				alive = false;
			existRigidBody[i]->health--;
			if(existRigidBody[i]->health <= 0)
				existRigidBody[i]->alive = false;
				break;
		}
	}
}
