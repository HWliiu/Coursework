#pragma once
class Collider
{
private:
	int left, right, top, bottom;
public:
	Collider();
	~Collider();
	void UpdateRegion(int l, int r, int t, int b) {
		left = l;
		right = r;
		top = t;
		bottom = b;
	}
	bool CollidTo(Collider * other);
};

