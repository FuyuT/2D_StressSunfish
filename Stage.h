#pragma once
#include "Mof.h"
#include "Enemy.h"

#define		SCROLL_SPEED	1

typedef struct tag_ENEMYSTART {
	float posX;
	float scroll;
}ENEMYSTART;

class Stage
{
private:
	CTexture	texture;
	float		scroll;
	ENEMYSTART* enemyStart;
	int			enemyCount;
	CTexture	enemyTexture;
	int			enemyNo;
public:
	Stage();
	~Stage();
	bool Load();
	void Initialize(ENEMYSTART* pSt, int cnt);
	void Update(Enemy* ene,int ecnt);
	void Render();
	void Release();
};

