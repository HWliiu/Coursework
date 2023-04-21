#pragma once
class Game
{
public:
	static int killCount;
	static int surviveTime;
	Game();
	~Game();
	static void Paint(HDC hdc);
	static void State(HDC hdc);
	static void startMenu(HDC hdc,int x,int y);
	static void restartMenu(HDC hdc);
	static void ClickPosition(int x, int y);
	static bool Contains(int x, int y);

};

