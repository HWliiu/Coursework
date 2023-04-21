#pragma once
#include "Background.h"
class Cloud :
	public Background
{
public:
	void Move();
	void Paint(HDC hdc);
	Cloud(int y, int speed);
	~Cloud();
	
};

