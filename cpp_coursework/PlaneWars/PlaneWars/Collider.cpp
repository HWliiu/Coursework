#include "stdafx.h"
#include "Collider.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}
bool Collider::CollidTo(Collider * other) {
	if (other->left>this->right ||
		other->right<this->left ||
		other->top>this->bottom ||
		other->bottom<this->top) {
		return false;
	}
	return true;
}