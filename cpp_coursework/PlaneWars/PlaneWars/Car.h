#pragma once
#include "Enemy.h"
class Car :
	public Enemy
{
public:
	Car(int speed);
	~Car();
	void Move();
	void Paint(HDC hdc);
	void collisionDectection();
};

