#pragma once

#include "Mof.h"

//�ړ����x
#define		PLAYER_SPEED		0.3f
//�ő呬�x
#define		PLAYER_MAXSPEED		5.0f
//�G�T
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

	//���G�T
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
	//�v���C���[���g�̓����蔻���Ԃ�
	CRectangle GetRect()
	{
		return CRectangle(
			posX - scrollX,
			posY,
			posX + texture.GetWidth() - scrollX,
			posY + texture.GetHeight()
		);
	}
	//�G�T���H�ׂ���͈͂ɂ��邩�𔻒f���邽�߂̓����蔻��
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX - FEED_SEARCHRANGE - scrollX,
			posY - FEED_SEARCHRANGE,
			posX + texture.GetWidth() + FEED_SEARCHRANGE - scrollX,
			posY + texture.GetHeight() + FEED_SEARCHRANGE
		);
	}
	//���G�T
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

