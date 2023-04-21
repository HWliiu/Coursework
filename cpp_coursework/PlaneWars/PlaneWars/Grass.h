#pragma once
#include "Background.h"
class Grass :
	public Background
{
public:
	Grass(int speed);
	~Grass();
	void Move();
	void Paint(HDC hdc);
};
