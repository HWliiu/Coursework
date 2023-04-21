#pragma once
#include "Background.h"
class Tree:
	public Background
{
public:
	Tree(int speed);
	~Tree();
	void Move();
	void Paint(HDC hdc);
};

