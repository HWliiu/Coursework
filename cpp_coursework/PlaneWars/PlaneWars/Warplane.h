#pragma once
#include "RigidBody.h"
#include "Bulletin.h"
class Warplane :
	public RigidBody
{
public:
	int bulletinCount;
	Bulletin * bulletins[50];
	Warplane();
	~Warplane();
	void Move();
	void Paint(HDC);
	void collisionDectection();
	void Shoot();
};

