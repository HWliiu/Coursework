#include "stdafx.h"
#include "Emitter.h"
#include "Background.h"
#include "Cloud.h"
#include "Enemy.h"
#include "Game.h"
#include "Ufo.h"
#include "Car.h"
#include "EnemyPlane.h"
#include "Tree.h"
#include "Grass.h"
#include <vector>

std::vector<Enemy *>enemys(20);
std::vector<Background *>objects(20);
DWORD lastTime1;
DWORD lastTime2;
DWORD lastTime3;
bool flag = false;//.......................
extern int cx;

Emitter::Emitter()
{
	ObjectCount = 0;
	EnemyCount = 0;
}


Emitter::~Emitter()
{
}

void Emitter::backgroundObjectEmitter(HDC hdc) {
	if (ObjectCount < 20) {
		DWORD now = GetTickCount();
		if (now - lastTime2 > 2000) {
			int seed = rand() % 10;
			if (seed == 0 || seed == 1) {
				objects[ObjectCount] = new Tree(5);
			}else if (seed == 2 || seed==3 || seed == 4) {
				objects[ObjectCount] = new Grass(5);
			}
			else {
				objects[ObjectCount] = new Cloud(rand() % 320, rand() % 8 + 1);
			}
			ObjectCount++;
			lastTime2 = now;
		}
	}
	for (int i = 0; i < ObjectCount; i++) {
		if (!objects[i]->isAlive()) {
			delete objects[i];
			ObjectCount--;
			for (int j = i; j < ObjectCount; j++)
				objects[j] = objects[j + 1];
		}
		else {
			objects[i]->Paint(hdc);
		}

	}
}

void Emitter::enemyEmitter(HDC hdc) {
	if (EnemyCount < 30) {
		DWORD now = GetTickCount();
		int seed=rand() % 8;
		if (now - lastTime3 > 1500) {
			if (seed == 0 || seed == 1 || seed == 2) {
				enemys[EnemyCount] = new EnemyPlane(rand() % 540, -8);
			}else if (seed == 3 || seed == 4) {
				enemys[EnemyCount] = new Car(-7);
			}
			else {
				enemys[EnemyCount] = new Ufo(rand() % 540, -8);
			}
			EnemyCount++;
			lastTime3 = now;
		}
	}
	for (int i = 0; i < EnemyCount; i++) {
		if (!enemys[i]->isAlive()) {
			if (enemys[i]->xPos < cx && enemys[i]->xPos > 0 && !flag) {
				Game::killCount++;
				flag = false;//..........................
			}
			delete enemys[i];
			EnemyCount--;
			for (int j = i; j < EnemyCount; j++)
				enemys[j] = enemys[j + 1];
			
		}
		else {
			enemys[i]->Paint(hdc);
		}
	}
}

void Emitter::clear() {
	flag = true;//............................
	for (int i = 0; i < EnemyCount; i++)
		enemys[i]->alive = false;
}
