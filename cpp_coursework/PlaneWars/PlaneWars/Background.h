#pragma once
class Background
{
protected:
	int xPos, yPos;
	int xSpeed;
	bool alive;
public:
	virtual void Move() = 0;
	virtual void Paint(HDC hdc) = 0;
	bool isAlive() { return alive; };
	Background();
	~Background();
};

