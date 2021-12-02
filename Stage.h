#pragma once
#include "Mof.h"
#include "Player.h"

#define		SCROLL_SPEED	1
#define     BACK_WAVE_SPEED -2					
#define     BACK_WAVE_ADJUSTMENT_SPEED 0.7	//�v���C���[�̈ړ��ɂ��g�������Ȃ鎞�A�g�������Ȃ肷���Ȃ��悤�ɒ���
#define     FRONT_WAVE_SPEED 2					
#define     FRONT_WAVE_ADJUSTMENT_SPEED 0.7

class Stage
{
private:
	CTexture	skyTex;
	CTexture	backWaveTex;
	Vector2		backWavePos;
	Vector2		backWaveSpeed;
	bool		backWaveTurnFlg;
	float		backWaveScrollValueX;
	CTexture	frontWaveTex;
	Vector2		frontWavePos;
	float		frontWaveScrollValueX;

	CTexture	distantBackGroundTex;
	CTexture	insideBackGroundTex;
	CTexture	closeBackGroundTex;

	int			enemyCount;
	CTexture	enemyTexture;
	int			enemyNo;

	float scrollValueX;
	float scrollValueY;

public:
	Stage();
	~Stage();
	bool Load();
	void Initialize();

	void WaveUpdate(const CRectangle& rec, const float& hsw);
	void Update(CPlayer& pl);


	//ScrollSpeed��1.0������
	void Scroll(CTexture tex, float scrollSpeedX, float scrollSpeedY);
	void WaveRender();
	void BackGroundRender();
	void ForeGroundRender();
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
		return skyTex.GetWidth();
	}
	float GetBackTextureHeight()
	{
		return skyTex.GetHeight();
	}
};

