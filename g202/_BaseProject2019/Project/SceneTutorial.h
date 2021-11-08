#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"

#define	 MESSAGE_WINDOW_POS_X 210
#define	 MESSAGE_WINDOW_POS_Y 650
#define  FIRST_MESSAGE_POS_X  400
#define  FIRST_MESSAGE_POS_Y  750
#define  MESSAGE_ARRAY_BYTE   500	//メッセージの文字数を変更したかったら、ここを変更する
#define  MESSAGE_DELAY_FRAME  5		//何フレームごとに一文字を表示するか

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

	//フォント
	LPMofChar fontAdd = "Test\\PopRumCute.otf";
	CFont FontPopRumCute;
	
	//チュートリアルメッセージ
	CTexture		 messageWindowImg;
	char*			 fBuffer;
	int				 fBufferOffset;	  //現在表示できている位置

	//一度に表示するバッファ 全角は(MESSAGE_ARRAY_BYTE/2)文字まで表示可能(文字コードShift_JISの場合)
	char			 fLineBuffer[MESSAGE_ARRAY_BYTE] = "\0";
	int				 mShowDelay;
	bool			 messageEndFlg;
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


};

