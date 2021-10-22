#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"

class CSceneTutorial : public CSceneBase
{
private:
	CPlayer			 pl;
	CUi				 ui;
	CObstacleManager cObstacle;

	//タイマー
	CTimer			 tempTimer;
	CTimer			 hungerTimer;
	CTimer			 parasiteTimer;

	//設定画面フラグ
	bool configFlg = false;

	//背景
	float scrollValueX;
	float scrollValueY;
	CTexture backGroundTexture;

public:
	CSceneTutorial();
	~CSceneTutorial();
	bool Load()override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;

	void ScreenScroll();

};

