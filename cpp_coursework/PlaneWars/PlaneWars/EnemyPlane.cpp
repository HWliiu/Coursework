#include "stdafx.h"
#include "EnemyPlane.h"
#include <math.h>

extern int cx;
time_t lastShootTime1;

EnemyPlane::EnemyPlane(int y,int speed)
{
	xPos = cx + rand() % 800;
	yPos = y;
	xSpeed = speed;
	health = 8;
	bulletinCount = 0;
	for (int i = 0; i < 5; i++)
		bulletins[i] = NULL;
}


EnemyPlane::~EnemyPlane()
{
	for (int i = 0; i < bulletinCount; i++) {
		delete bulletins[i];
		bulletins[i] = NULL;
	}
	bulletinCount = 0;
}

void EnemyPlane::Move() {
	xPos += xSpeed;
	if (xPos < -200)
		alive = false;
	collisionDectection();
	int seed = rand() % 10;
	if (seed == 0 || seed == 1)
		Shoot();
}

void EnemyPlane::Paint(HDC hdc) {
	Move();
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 128, 255));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 128, 255));
	HBRUSH hOldBrush1 = (HBRUSH)SelectObject(hdc, hBrush1);
	POINT points1[4] = { 54 + xPos, 1 + yPos, 29 + xPos, 17 + yPos, 57 + xPos, 18 + yPos, 73 + xPos, 2 + yPos };
	Polygon(hdc, points1, 4);
	SelectObject(hdc, hOldBrush1);
	DeleteObject(hBrush1);

	HBRUSH hBrush2 = CreateHatchBrush(HS_DIAGCROSS,RGB(255, 0, 255));
	HBRUSH hOldBrush2 = (HBRUSH)SelectObject(hdc, hBrush2);
	POINT points2[9] = { 0 + xPos, 32 + yPos, 14 + xPos, 21 + yPos, 43 + xPos, 15 + yPos, 76 + xPos, 15 + yPos,
						98 + xPos, 20 + yPos, 97 + xPos, 33 + yPos, 79 + xPos, 39 + yPos, 36 + xPos, 40 + yPos,12 + xPos,37 + yPos };
	Polygon(hdc, points2, 9);
	SelectObject(hdc, hOldBrush2);
	DeleteObject(hBrush2);

	HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 128, 255));
	HBRUSH hOldBrush3 = (HBRUSH)SelectObject(hdc, hBrush3);
	POINT points3[4] = { 72 + xPos, 24 + yPos, 82 + xPos, 8 + yPos, 98 + xPos, 2 + yPos, 88 + xPos, 23 + yPos };
	Polygon(hdc, points3, 4);

	for (int i = 0; i < bulletinCount; i++) {
		bulletins[i]->Move();
		bulletins[i]->collisionDectection();
		bulletins[i]->Paint(hdc);
		if (!bulletins[i]->isAlive()) {
			delete bulletins[i];
			bulletinCount--;
			for (int j = i; j < bulletinCount; j++)
				bulletins[j] = bulletins[j + 1];
		}
	}

	SelectObject(hdc, hOldBrush3);
	DeleteObject(hBrush3);

	HBRUSH hBrush4 = CreateSolidBrush(RGB(255, 128, 255));
	HBRUSH hOldBrush4 = (HBRUSH)SelectObject(hdc, hBrush4);
	POINT points4[6] = { 36 + xPos, 33 + yPos, 65 + xPos, 30 + yPos, 81 + xPos, 41 + yPos, 93 + xPos, 56 + yPos, 74 + xPos, 55 + yPos, 54 + xPos,47 + yPos };
	Polygon(hdc, points4, 6);
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

void EnemyPlane::collisionDectection() {
	collider.UpdateRegion(xPos, xPos + 100, yPos, yPos + 55);
	for (int i = 0; i < rigidBodyCount; i++) {
		if (existRigidBody[i] != this && collider.CollidTo(&(existRigidBody[i]->collider))) {
			if (health <= 0)
				alive = false;
			existRigidBody[i]->health--;
			if (existRigidBody[i]->health <= 0)
				existRigidBody[i]->alive = false;
			break;
		}
	}
}

void EnemyPlane::Shoot()
{
	time_t t = time_t(GetTickCount());
	if (fabs(lastShootTime1 - t) < 2000) {
		return;
	}
	else {
		lastShootTime1 = t;
	}

	if (bulletinCount < 2) {
		//运行一段时间后会有bug，弄了好久不知道解决，暂将敌机发射子弹的功能取消
		//bulletins[bulletinCount] = new Bulletin(xPos - 20, yPos + 32, -12);
		//bulletinCount++;
	}
}