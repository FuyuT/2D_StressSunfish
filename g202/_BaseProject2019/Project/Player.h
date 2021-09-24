#pragma once

#include "Mof.h"

//�ړ����x
#define		PLAYER_SPEED		0.3f
//�ő呬�x
#define		PLAYER_MAXSPEED		5.0f
//�G�T
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
	//�v���C���[���g�̓����蔻���Ԃ�
	CRectangle GetRect()
	{
		return CRectangle(posX, posY, posX + texture.GetWidth(), posY + texture.GetHeight());
	}
	//�G�T���H�ׂ���͈͂ɂ��邩�𔻒f���邽�߂̓����蔻��
	CRectangle GetSearchRect()
	{
		return CRectangle(posX, posY, posX + texture.GetWidth(), posY + texture.GetHeight());
	}
};

