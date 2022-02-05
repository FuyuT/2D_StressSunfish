#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "Ui.h"
#include "Stage.h"
#include "HeaderDefine.h"
#include "SceneConfig.h"
#include "SceneTrophyCollection.h"
#include "SceneStressCollection.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"
#include "SceneBase.h"

#define	PLAYER_SPEED 10


class CSceneGame : public CSceneBase
{
private:
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;
	CSceneTrophyCollection trophy;
	CSceneStressCollection caseOfDeth;
	CPopUpWindowBase* nowPopUpGame = NULL;

	//GameAppで遷移すると設定画面からゲームシーンに戻った際にゲームシーンが初期化されるため、
	//ここで宣言し、ゲームシーンの上から設定画面を表示するようにする。
	CSceneConfig sceneConfig;

	CPlayer pl;
	Stage stg;
	CObstacleManager cObstacle;
	CUi ui;

	int playerX = 100;
	int playerY = 100;

	int distancePlayer = 0;

	Vector2 moveSpeed;
	/*CTexture backGroundTexture;*/
	CTexture playerTexture;

	/*float scrollValueX;
	float scrollValueY;*/

	//障害物
	int posX;
	int posY;
	CTexture seaTurtleTexture;
	bool deadFlag;

	//設定画面フラグ
	bool configFlg = false;
	//ポーズ画面フラグ
	bool poseFlg;
	//新規入手フラグ
	bool newGetTrophy;
	bool newGetDeth;
	//トロフィー用配列
	int	numberOfTrophy[3];
	
	//イベント
	CRandom eventRandom;
	int		eventNum;
	CTimer	eventTimer;
	//開始フラグ
	bool startFlg;

	//SEフラグ
	bool seFlg;
	bool alertFlg;
	bool goFlg;
	bool popUpGuardFlg;
	bool hungryFlg;

	//背景のオブジェクト
	struct BackObject
	{
		CTexture tex;
		int objectTotalNo;
		Vector2* pos;
	};
	BackObject kelp;


public:
	CSceneGame();
	~CSceneGame();
	void PlayBGM() override;
	bool Load()override;
	void Initialize() override;
	void EventUpdate();
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;
	void SEUpdate();

	CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};
		/*
	//追加
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


	void PopUpController();
	void CaseOfDethController();
	void TrophyController();
};

