#include "stdafx.h"
#include "Warplane.h"
#include "KeyControl.h"
#include <cmath>

extern KeyControl keyControl;
int cx = GetSystemMetrics(SM_CXSCREEN);
int cy = GetSystemMetrics(SM_CYSCREEN);
time_t lastShootTime;
int k = 0;

Warplane::Warplane()
{
	xPos = 100;
	yPos = 300;
	xSpeed = 0;
	ySpeed = 0;
	health = 10;
	bulletinCount = 0;
	for (int i = 0; i < 50; i++)
		bulletins[i] = NULL;
}


Warplane::~Warplane()
{
	for (int i = 0; i < bulletinCount; i++) {
		delete bulletins[i];
	}
}

void Warplane::Move() {
	if (keyControl.IsKeyDown(VK_LEFT)) {
		xSpeed = -10;
		if (keyControl.IsKeyDown(VK_SHIFT)) {
			xSpeed = -20;
		}
	}else if (keyControl.IsKeyDown(VK_RIGHT)) {
		xSpeed = 10;
		if (keyControl.IsKeyDown(VK_SHIFT)) {
			xSpeed = 20;
		}
	}else {
		xSpeed = 0;
	}	
	if (keyControl.IsKeyDown(VK_UP)) {
		ySpeed = -10;
		if (keyControl.IsKeyDown(VK_SHIFT)) {
			ySpeed = -20;
		}
	}else if (keyControl.IsKeyDown(VK_DOWN)) {
		ySpeed = 10;
		if (keyControl.IsKeyDown(VK_SHIFT)) {
			ySpeed = 20;
		}
	}else {
		ySpeed = 0;
	}
			
	if (keyControl.IsKeyDown(VK_CONTROL) || keyControl.IsKeyDown(VK_SPACE))
		Shoot();

	xPos += (xPos + xSpeed > (cx-100) || xPos + xSpeed < -100) ? 0 : xSpeed;
	yPos += (yPos + ySpeed > 600 || yPos + ySpeed < -20) ? 0 : ySpeed;

	collisionDectection();

}
void Warplane::collisionDectection() {
	collider.UpdateRegion(xPos, xPos + 200, yPos, yPos + 60);
	for (int i = 0; i < rigidBodyCount; i++) {
		if (existRigidBody[i] != this && collider.CollidTo(&(existRigidBody[i]->collider))) {
			health--;
			existRigidBody[i]->health = 0;
			existRigidBody[i]->alive = false;
			if( health <= 0)
				alive = false;
			
			break;
		}
	}
}

void Warplane::Paint(HDC hdc) {

	Move();

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 24, 128));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 24, 128));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

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
	//绘制warPlane
	POINT points1[20] = {1 + xPos,26+yPos,12 + xPos,23 + yPos,20 + xPos,40 + yPos,42 + xPos,34 + yPos,64 + xPos,30 + yPos,91 + xPos,29 + yPos,107 + xPos,37 + yPos,136 + xPos,35 + yPos,153 + xPos,26 + yPos,173 + xPos,27 + yPos,
	175 + xPos,37 + yPos,175 + xPos,48 + yPos,172 + xPos,57 + yPos,153 + xPos,62 + yPos,127 + xPos,63 + yPos,136 + xPos,46 + yPos,67 + xPos,53 + yPos,62 + xPos,65 + yPos,6 + xPos,65 + yPos,6 + xPos,45 + yPos };
	Polygon(hdc,points1,20);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	POINT points2[4] = { 65 + xPos,30 + yPos,47 + xPos,6 + yPos,97 + xPos,2 + yPos,123 + xPos,21 + yPos };
	Polyline(hdc, points2, 4);
	POINT points3[4] = { 91 + xPos,29 + yPos,106 + xPos,21 + yPos,134 + xPos,21 + yPos,154 + xPos,25 + yPos };
	Polyline(hdc, points3, 4);
	POINT points4[4] = { 173 + xPos,28 + yPos,183 + xPos,31 + yPos,183 + xPos,53 + yPos,171 + xPos,59 + yPos };
	Polyline(hdc, points4, 4);
	POINT points5[4] = { 137 + xPos,46 + yPos,93 + xPos,111 + yPos,43 + xPos,113 + yPos,67 + xPos,53 + yPos };
	Polygon(hdc, points5, 4);
	POINT points6[3] = { 134 + xPos,21 + yPos,133 + xPos,26 + yPos,136 + xPos,34 + yPos };
	Polyline(hdc, points6, 3);
	POINT points7[2] = { 107 + xPos,21 + yPos,107 + xPos,37 + yPos };
	Polyline(hdc, points7, 2);
	POINT points8[3] = { 183 + xPos,38 + yPos,194 + xPos,40 + yPos,183 + xPos,42 + yPos };
	Polyline(hdc, points8, 3);

	int x1 = 10 * sin(k);   int x2 = 10 * sin(k + 90);
	int y1 = 20 * cos(k);   int y2 = 20 * cos(k + 90);

	MoveToEx(hdc, 194 + xPos, 40 + yPos, nullptr);//螺旋桨中点
	LineTo(hdc, x1 + 194 + xPos, y1 + 40 + yPos);
	MoveToEx(hdc, 194 + xPos, 40 + yPos, nullptr);
	LineTo(hdc, -x1 + 194 + xPos, -y1 + 40 + yPos);
	MoveToEx(hdc, 194 + xPos, 40 + yPos, nullptr);//螺旋桨中点
	LineTo(hdc, x2 + 194 + xPos, y2 + 40 + yPos);
	MoveToEx(hdc, 194 + xPos, 40 + yPos, nullptr);
	LineTo(hdc, -x2 + 194 + xPos, -y2 + 40 + yPos);
	k++;

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	
}

void Warplane::Shoot()
{
	//为控制发射速率，比较和记录当前发射时间
	time_t t = time_t(GetTickCount());
	if (fabs(lastShootTime - t) < 100) {
		return;
	}
	else {
		lastShootTime = t;
	}

	if (bulletinCount < 40) {
		bulletins[bulletinCount] = new Bulletin(xPos+215, yPos+50, 35);
		bulletinCount++;
	}
}