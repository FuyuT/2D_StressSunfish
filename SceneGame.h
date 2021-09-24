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

	//CTexture stressGauge;
public:
	CSceneGame();
	~CSceneGame();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	
};

