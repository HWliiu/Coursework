#include "stdafx.h"
#include "Bulletin.h"
Bulletin::Bulletin(int x,int y,int speed)
{
	xPos = x;
	yPos = y;
	xSpeed = speed;
	alive = true;
	health = 1;
}


Bulletin::~Bulletin()
{
}

void Bulletin::Paint(HDC hdc)
{
	Ellipse(hdc, xPos, yPos, 15 + xPos, 5 + yPos);
}

void Bulletin::collisionDectection() {
	collider.UpdateRegion(xPos, xPos + 15, yPos, yPos + 5);
	for (int i = 0; i < rigidBodyCount; i++) {
		if (existRigidBody[i] != this && collider.CollidTo(&(existRigidBody[i]->collider))) {
			alive = false;
			existRigidBody[i]->health--;
			if(existRigidBody[i]->health <= 0)
				existRigidBody[i]->alive = false;
			break;
		}
	}
}