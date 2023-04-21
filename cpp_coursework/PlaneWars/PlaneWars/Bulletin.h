#pragma once
#include "RigidBody.h"
class Bulletin:public RigidBody
{	
	public:
		Bulletin(int x, int y, int speed);
		~Bulletin();
		void Paint(HDC hdc);
		void collisionDectection();
};
