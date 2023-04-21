#pragma once
#include "Collider.h"
class RigidBody
{
protected:
	static RigidBody * existRigidBody[300];
	static int  rigidBodyCount;
	int ySpeed;
	int xSpeed;
	
public:
	Collider collider;
	bool alive;
	int health;
	int xPos, yPos;
	RigidBody();
	~RigidBody();
	void Move();
	bool isAlive() { return alive; };
};

