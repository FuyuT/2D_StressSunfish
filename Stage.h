#pragma once
#include "Mof.h"
#include "Enemy.h"
#include "Player.h"

#define		SCROLL_SPEED	1

typedef struct tag_ENEMYSTART {
	float posX;
	float scroll;
	int type;
}ENEMYSTART;

class Stage
{
private:
	CTexture	texture;
	//float		scroll;
	ENEMYSTART* enemyStart;
	int			enemyCount;
	CTexture	enemyTexture;
	int			enemyNo;

	//’Ç‰Á
	float scrollValueX;
	float scrollValueY;

public:
	Stage();
	~Stage();
	bool Load();
	void Initialize(/*ENEMYSTART* pSt, int cnt*/);
	void Update(/*Enemy* ene, int ecnt */ CPlayer & pl);
	void Render();
	void Release();

	//’Ç‰Á
	float GetScrollX()
	{
		return scrollValueX;
	};
	float GetScrollY()
	{
		return scrollValueY;
	}

	float GetBackTextureWidth()
	{
		return texture.GetWidth();
	}
	float GetBackTextureHeight()
	{
		return texture.GetHeight();
	}
};

