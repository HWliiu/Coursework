#pragma once

class Emitter
{
public:
	int EnemyCount;
	int ObjectCount;
	Emitter();
	~Emitter();
	void backgroundObjectEmitter(HDC hdc);
	void enemyEmitter(HDC hdc);
	void clear();
};


