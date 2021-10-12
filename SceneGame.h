#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Enemy.h"

class CSceneGame : public CSceneBase
{
private:
	CPlayer pl;
	Enemy ene;

	int playerX = 100;
	int playerY = 100;

	int distancePlayer = 0;

	int stressBarX = 700;
	int stressBarY = 10;
	int stressBarChenge = 300;

	int stressNumber = 100;

	int timeCnt = 0;

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

	//è·äQï®
	int posX;
	int posY;
	CTexture seaTurtleTexture;
	bool deadFlag;

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
		/*
	//í«â¡
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

	/*CRectangle GetRect()
	{
		return CRectangle(
			ePosX,
			ePosY,
			ePosX + 100,
			ePosY + 100
		);
	}
	int GetType()
	{
		return 0;
	}*/


};

