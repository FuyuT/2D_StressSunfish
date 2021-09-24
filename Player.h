#pragma once

#include "Mof.h"

//移動速度
#define		PLAYER_SPEED		0.3f
//最大速度
#define		PLAYER_MAXSPEED		5.0f
//エサ
//#define		

class CPlayer
{
private:
	CTexture	texture;
	float		posX;
	float		posY;
	float		moveX;
	float		moveY;
	float		scrollX;

public:
	CPlayer();
	~CPlayer();
	void Initialize();
	void Update();
	void Render();
	void Release();
	float GetPosX()
	{
		return posX;
	};
	float GetPosY()
	{
		return posY;
	};
	//プレイヤー自身の当たり判定を返す
	CRectangle GetRect()
	{
		return CRectangle(posX, posY, posX + texture.GetWidth(), posY + texture.GetHeight());
	}
	//エサが食べられる範囲にあるかを判断するための当たり判定
	CRectangle GetSearchRect()
	{
		return CRectangle(posX, posY, posX + texture.GetWidth(), posY + texture.GetHeight());
	}
};

