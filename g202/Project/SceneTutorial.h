#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"
#include "HeaderDefine.h"
#include "ResourceFont.h"
#include "SceneConfig.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"

#define	 MESSAGE_WINDOW_POS_X 210
#define	 MESSAGE_WINDOW_POS_Y 650
#define  FIRST_MESSAGE_POS_X  400
#define  FIRST_MESSAGE_POS_Y  750
#define  MESSAGE_ARRAY_BYTE   500	//メッセージの文字数を変更したかったら、ここを変更する
#define  MESSAGE_DELAY_FRAME  5		//何フレームごとに一文字を表示するか


class CSceneTutorial : public CSceneBase
{
private:
	//GameAppで遷移すると設定画面からゲームシーンに戻った際にゲームシーンが初期化されるため、
	//ここで宣言し、ゲームシーンの上から設定画面を表示するようにする。
	CSceneConfig sceneConfig;

	CPopUpWindowBase* nowPopUpTutorial = NULL;

	Stage			 stg;
	CUi				 ui;
	CPlayer			 pl;
	CObstacleManager obs;

	//タイマー
	CTimer			 tempTimer;
	CTimer			 hungerTimer;
	CTimer			 parasiteTimer;

	//フォント
	LPMofChar fontAdd = "Text\\PopRumCute.otf";
	CResourceFont	font;
	LPMofChar fontName = "ポプらむ☆キュート";

	//チュートリアルメッセージ
	CTexture		 messageWindowImg;
	char* fBuffer;
	int				 fBufferOffset;	  //現在表示できている位置

	//一度に表示するバッファ 全角は(MESSAGE_ARRAY_BYTE/2)文字まで表示可能(文字コードShift_JISの場合)
	char			 fLineBuffer[MESSAGE_ARRAY_BYTE] = "\0";
	int				 mShowDelay;
	bool			 messageEndFlg;
	int				 tutorialStep;

	//ポーズ画面フラグ
	bool poseFlg;
	//設定画面フラグ
	bool configFlg = false;

public:
	CSceneTutorial();
	~CSceneTutorial();
	bool TextLoad();
	void FontLoad();
	void MessageUpdate();
	void MessageRender();
	bool Load()override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;

	void PopUpController();

};
