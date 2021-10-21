#pragma once
#include "Mof.h"
#include "Player.h"

#define		SCROLL_SPEED	1


class Stage
{
private:
	CTexture	texture;
	int			enemyCount;
	CTexture	enemyTexture;
	int			enemyNo;

	//�ǉ�
	float scrollValueX;
	float scrollValueY;

public:
	Stage();
	~Stage();
	bool Load();
	void Initialize();
	void Update(CPlayer & pl);
	void Render();
	void Release();

	//�ǉ�
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

