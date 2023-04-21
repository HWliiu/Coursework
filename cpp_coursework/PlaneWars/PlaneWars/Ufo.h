#pragma once
#include "Enemy.h"
class Ufo :
	public Enemy
{
public:
	Ufo(int y,int speed);
	~Ufo();
	void Move();
	void Paint(HDC hdc);
	void collisionDectection();
};

