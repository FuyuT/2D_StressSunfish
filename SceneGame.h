#pragma once
#include "SceneBase.h"
#include "Player.h"

class CSceneGame : public CSceneBase
{
private:
	/*int playerX = 100;
	int playerY = 100;*/

	//�ǉ�
	CPlayer pl;

	int distancePlayer = 0;

	int stressBarX = 700;
	int stressBarY = 10;
	int stressBarChenge = 300;

	int stressNumber = 100;

	int timeCnt = 0;

	int bodyTemperature = 50;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	//Vector2 moveSpeed;
	CTexture backGroundTexture;
	//CTexture playerTexture;
	float scrollValueX;
	float scrollValueY;

	CTexture temperatureNormal;
	CTexture temperatureHot;
	CTexture temperatureCold;

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

	/*
	//�ǉ�
	float GetScrollX()
	{
		return scrollValueX;
	};
	float GetScrollY()
	{
		return scrollValueY;
	}
	*/
	/*CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};*/

};

