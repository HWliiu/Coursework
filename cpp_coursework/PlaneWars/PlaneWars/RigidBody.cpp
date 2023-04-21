#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"
//现有刚体数组，用于保存各刚体及其子类实例的变量指针
RigidBody * RigidBody::existRigidBody[300];
int  RigidBody::rigidBodyCount = 0;
extern int cx;

RigidBody::RigidBody()
{
	existRigidBody[rigidBodyCount++] = this;
}


RigidBody::~RigidBody()
{
	for (int i = 0; i < rigidBodyCount; i++) {
	     	if (existRigidBody[i] == this) {
   			rigidBodyCount--;
			for (int j = i; j < rigidBodyCount; j++) {
				existRigidBody[j] = existRigidBody[j + 1];
			}
			break;//中止寻找当前对象指针过程
		}
	}
}

void RigidBody::Move() {
	xPos += xSpeed;
	if (xPos > cx + 200 || xPos < -200)
		alive = false;
}
