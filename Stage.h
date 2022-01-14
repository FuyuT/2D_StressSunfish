#pragma once
#include "Mof.h"
#include "Player.h"
#include "BackObjectKelp.h"
#include "FishShadow.h"

#define		SCROLL_SPEED	1
#define     BACK_WAVE_SPEED -2					
#define     BACK_WAVE_ADJUSTMENT_SPEED 0.7	//�v���C���[�̈ړ��ɂ��g�������Ȃ鎞�A�g�������Ȃ肷���Ȃ��悤�ɒ���
#define     FRONT_WAVE_SPEED 2					
#define     FRONT_WAVE_ADJUSTMENT_SPEED 0.7

enum Type {
	FishShadow,
};

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

	CFishShadow cFishShadow[3];
	CRandom fishShadowNoRandom;
	CRandom createRandom;
	CRandom posYRandom;
	int posY;
	int posYNum;

	//�w�i�̃I�u�W�F�N�g
	CBackObjectKelp ObjectKelp;
public:
	Stage();
	~Stage();
	bool Load();
	void Initialize();

	void WaveUpdate(const CRectangle& rec, const float& hsw);
	void Update(CPlayer& pl);


	//ScrollSpeed��1.0������
	void Scroll(CTexture tex, float scrollSpeedX, float scrollSpeedY);
	void FishShadowUpdate(int distance);
	void WaveRender();
	void FishShadowRender();
	void BackGroundRender();
	void ForeGroundRender();
	void Render();

	void Release();

	int PosYRandom();


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
	bool FishShadowPercentage(int percent)
	{
		//�m���ɂ����true��Ԃ�
		if (createRandom.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}
};

