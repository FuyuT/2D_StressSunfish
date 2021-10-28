#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"

#define	 MESSAGE_WINDOW_POS_X 210
#define	 MESSAGE_WINDOW_POS_Y 650
#define  FIRST_LETTER_POS_X   400
#define  FIRST_LETTER_POS_Y   750

class CSceneTutorial : public CSceneBase
{
private:
	Stage			 stg;
	CUi				 ui;
	CPlayer			 pl;
	CObstacleManager obs;

	//タイマー
	CTimer			 tempTimer;
	CTimer			 hungerTimer;
	CTimer			 parasiteTimer;

	//チュートリアルメッセージ
	CTexture		 messageWindowImg;
	char*			 fBuffer;
public:
	CSceneTutorial();
	~CSceneTutorial();
	bool Load()override;
	bool TextLoad();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;


};

