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

	int stressNumber = 100;

	int timeCnt = 0;

	Vector2 moveSpeed;
	CTexture backGroundTexture;
	CTexture playerTexture;
	float scrollValueX;
	float scrollValueY;
	//CTexture stressGauge;
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

