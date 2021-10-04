#pragma once
#include "SceneBase.h"
class CSceneGame : public CSceneBase
{
private:
	int playerX = 100;
	int playerY = 100;

	int distancePlayer = 0;

	int stressBarX = 700;
	int stressBarY = 10;
	int stressBarChenge = 300;

	int bodyTemp = 10;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	float tempRegion = 245;
	int hungerRegion = 40;

	Vector2 moveSpeed;
	CTexture backGroundTexture;
	CTexture playerTexture;
	float scrollValueX;
	float scrollValueY;

	CTexture stressMeter;

	CTexture tempNormal;
	CTexture tempHot;
	CTexture tempCold;

	CTexture tempMeter;
	CTexture tempMeterFrame;

	CTexture hungerGauge;
	CTexture hungerGaugeFrame;

	CTexture parasite1;
	CTexture parasite2;
	CTexture parasite3;
	CTexture parasite4;
	CTexture parasite5;
public:
	CSceneGame();
	~CSceneGame();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};

};

