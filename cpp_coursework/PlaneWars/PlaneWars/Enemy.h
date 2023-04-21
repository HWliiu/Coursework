#pragma once
#include "RigidBody.h"
class Enemy :
	public RigidBody
{
public:
	Enemy();
	~Enemy();
	virtual void Move() = 0;
	virtual void Paint(HDC hdc) = 0;
};

