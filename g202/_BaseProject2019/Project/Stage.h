#pragma once
#include "Mof.h"
#include "Player.h"

#define		SCROLL_SPEED	1


class Stage
{
private:
	CTexture	BackGroundTex1;
	CTexture	BackGroundTex2;
	Vector2		WavePos;
	int			WaveSpeed;
	bool		turnFlg;
	CTexture	BackGroundTex3;
	CTexture	BackGroundTex4;
	CTexture	BackGroundTex5;
	CTexture	BackGroundTex6;

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
	void Initialize();
	void Update(CPlayer & pl);
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
		return BackGroundTex1.GetWidth();
	}
	float GetBackTextureHeight()
	{
		return BackGroundTex1.GetHeight();
	}
};

