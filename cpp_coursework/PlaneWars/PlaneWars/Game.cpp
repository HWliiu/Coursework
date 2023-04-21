#include "stdafx.h"
#include "Game.h"
#include <ctime>
#include "Emitter.h"
#include "Ground.h"
#include "Warplane.h"
#include "KeyControl.h"
#include "Enemy.h"

int Game::killCount = 0;
int Game::surviveTime = 0;
bool isClick = false;
Emitter emitter;
Warplane *warplane = new Warplane();
extern int cx;
extern int cy;
extern KeyControl keyControl;


clock_t start;
clock_t end;

Game::Game()
{
}


Game::~Game()
{
}

void Game::startMenu(HDC hdc,int x,int y) {
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(rand() % 255, 64, 0));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, 100, 80, 0.9*cx, 0.4*cy);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

	start = clock();
	SetTextColor(hdc, RGB(rand() % 128, rand() % 128, rand() % 255));
	TextOut(hdc, 100, 50, L"PLANEWAR 2.0", 12);
	RECT rect;
	rect.left = 0.4*cx, rect.right = 0.4*cx + 200;
	rect.top = 300; rect.bottom = 320;
	SetTextColor(hdc, RGB(128, 255, 128));
	DrawText(hdc, L"点击此处开始游戏", -1, &rect, DT_LEFT);
	SetTextColor(hdc, RGB(255, 128, 128));
	TextOut(hdc, 0.3*cx, 200, L"提示：上下左右控制方向，空格或Ctrl发射子弹，按住Shift可以加速", 35);
	TextOut(hdc, 0.3*cx+45, 230, L"注意当飞机头部与敌机碰撞时会造成两倍损伤", 20);

	POINT points[7] = { 0 + x,0 + y,30 + x,0 + y,20 + x,10 + y,40 + x,28 + y,28 + x,40 + y,10 + x,20 + y,0 + x,30 + y };
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Polygon(hdc, points, 7);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void Game::restartMenu(HDC hdc) {
	SetTextColor(hdc, RGB(0, 0, 64));
	TextOut(hdc, 0.4*cx, 400, L"游戏结束！按TAB键复活！", 13);
	TextOut(hdc, 0.4*cx+20, 450, L"按ESC键退出程序！", 10);

	emitter.clear();
	
	if (keyControl.IsKeyDown(VK_TAB)) {
		start = clock();
		warplane = new Warplane();
		Game::killCount = 0;
	}
	if (keyControl.IsKeyDown(VK_ESCAPE))
		exit(0);
}

void Game::State(HDC hdc) {
	SetTextColor(hdc, RGB(255, 0, 128));
	SetBkColor(hdc, RGB(128, 255, 255));
	wchar_t  score[10];
	swprintf(score, 255, _T("击毁数:%d"), killCount);
	RECT rect;
	rect.left = 10, rect.right = 300;
	rect.top = 10; rect.bottom = 50;
	DrawText(hdc, score, -1, &rect, DT_LEFT);

	wchar_t  hp[10];
	swprintf(hp, 255, _T("生命值:%d"), warplane->health);
	rect.left = 200, rect.right = 400;
	rect.top = 10; rect.bottom = 50;
	DrawText(hdc, hp, -1, &rect, DT_LEFT);

	wchar_t  time[10];
	end = clock();
	Game::surviveTime = (end - start) / CLOCKS_PER_SEC;
	swprintf(time, 255, _T("存活时间:%ds"), Game::surviveTime);
	rect.left = 600, rect.right = 800;
	rect.top = 10; rect.bottom = 50;
	DrawText(hdc, time, -1, &rect, DT_LEFT);
}

void Game::Paint(HDC hdc) {
	emitter.backgroundObjectEmitter(hdc);
	Ground::Paint(hdc);
	warplane->Paint(hdc);
	emitter.enemyEmitter(hdc);
	Game::State(hdc);
}

bool Game::Contains(int x,int y) {
	if (x<0.4*cx+120 && x>0.4*cx && y<320 && y>300) {
		return true;
	}
	else {
		return false;
	}
}

void Game::ClickPosition(int x,int y) {
	if (Game::Contains(x, y))
		isClick = true;
}
