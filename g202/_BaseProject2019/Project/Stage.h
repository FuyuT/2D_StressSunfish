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

	//í«â¡
	float scrollValueX;
	float scrollValueY;

public:
	Stage();
	~Stage();
	bool Load();
	void Initialize();

	void Update(CPlayer& pl);


	//ScrollSpeedÇÕëÂÇ´Ç¢ÇŸÇ«ÉXÉNÉçÅ[ÉãÇ™íxÇ≠Ç»ÇÈ
	void Scroll(CTexture tex, int scrollSpeedX, int scrollSpeedY);
	void WaveRender();
	void BackGroundRender();
	void ForGroundRender();
	void Render();

	void Release();


	//í«â¡
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

