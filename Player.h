#pragma once

#include "Mof.h"

//移動速度
#define		PLAYER_SPEED		0.3f
//最大速度
#define		PLAYER_MAXSPEED		5.0f
//エサ
#define		FEED_SEARCHRANGE	60.0f

class CPlayer
{
private:
	CTexture	texture;
	float		posX;
	float		posY;

	float		moveX;
	float		moveY;
	float		scrollX;

	//仮エサ
	int	feedPosX = 2000;
	CRectangle feedRect = CRectangle(feedPosX, 300, feedPosX + 50, 350);
	bool feedDeadFlg = false;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove();
	void Update();
	void Render();
	void Release();
	int GetPosX()
	{
		return (int)posX;
	};
	int GetPosY()
	{
		return (int)posY;
	};
	//プレイヤー自身の当たり判定を返す
	CRectangle GetRect()
	{
		return CRectangle(
			posX - scrollX,
			posY,
			posX + texture.GetWidth() - scrollX,
			posY + texture.GetHeight()
		);
	}
	//エサが食べられる範囲にあるかを判断するための当たり判定
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX - FEED_SEARCHRANGE - scrollX,
			posY - FEED_SEARCHRANGE,
			posX + texture.GetWidth() + FEED_SEARCHRANGE - scrollX,
			posY + texture.GetHeight() + FEED_SEARCHRANGE
		);
	}
	//仮エサ
	CRectangle GetFeedRect()
	{
		return CRectangle(
			feedPosX - scrollX,
			feedRect.Top,
			feedPosX + 50 - scrollX,
			feedRect.Bottom
		);
	}
};

