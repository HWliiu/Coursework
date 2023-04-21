#include "stdafx.h"
#include "Car.h"

extern int cx;

Car::Car(int speed)
{
	xPos = cx + rand() % 800;
	yPos = 640;
	xSpeed = speed;
	health = 5;
}


Car::~Car()
{
}

void Car::Move() {
	xPos += xSpeed;
	if (xPos < -200)
		alive = false;
	collisionDectection();
}

void Car::Paint(HDC hdc) {
	Move();
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 128, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 192, 64));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, 35 + xPos, -11 + yPos, 76 + xPos, -8 + yPos);
	Rectangle(hdc, 75 + xPos, -15 + yPos, 85 + xPos, -4 + yPos);
	Rectangle(hdc, 60 + xPos, -5 + yPos, 100 + xPos, 1 + yPos);
	POINT points1[5] = { 1 + xPos,17 + yPos,27 + xPos,0 + yPos,120 + xPos,0 + yPos,120 + xPos,33 + yPos,14 + xPos,33 + yPos };
	Polygon(hdc, points1, 5);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);

	POINT points2[4] = { 30 + xPos,4 + yPos,13 + xPos,14 + yPos,40 + xPos,14 + yPos,40 + xPos,4 + yPos };
	Polygon(hdc, points2, 4);
	POINT points3[4] = { 48 + xPos,4 + yPos,60 + xPos,4 + yPos,60 + xPos,14 + yPos,48 + xPos,14 + yPos };
	Polygon(hdc, points3, 4);

	HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 128, 64));
	HBRUSH hOldBrush1 = (HBRUSH)SelectObject(hdc, hBrush1);
	Ellipse(hdc, 20 + xPos, 24 + yPos, 40 + xPos, 44 + yPos);
	Ellipse(hdc, 45 + xPos, 24 + yPos, 65 + xPos, 44 + yPos);
	Ellipse(hdc, 70 + xPos, 24 + yPos, 90 + xPos, 44 + yPos);
	Ellipse(hdc, 95 + xPos, 24 + yPos, 115 + xPos, 44 + yPos);
	SelectObject(hdc, hOldBrush1);
	DeleteObject(hBrush1);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	wchar_t  hp[10];
	RECT rect;
	SetTextColor(hdc, RGB(255, 0, 64));
	swprintf(hp, 255, _T("hp:%d"), health);
	rect.left = xPos, rect.right = xPos + 100;
	rect.top = yPos - 35; rect.bottom = yPos;
	DrawText(hdc, hp, -1, &rect, DT_CENTER);
}

void Car::collisionDectection() {
	collider.UpdateRegion(xPos, xPos + 100, yPos, yPos + 50);
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