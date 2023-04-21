#pragma once
#include "Enemy.h"
#include "Bulletin.h"
class EnemyPlane :
	public Enemy
{
public:
	int bulletinCount;
	Bulletin * bulletins[5];
	EnemyPlane(int y,int speed);
	~EnemyPlane();
	void Move();
	void Paint(HDC hdc);
	void collisionDectection();
	void Shoot();
};

