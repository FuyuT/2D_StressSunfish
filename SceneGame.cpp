#include "SceneGame.h"
#include "SceneConfig.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "SceneTrophyCollection.h"
#include "SceneStressCollection.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"
#include "SceneBase.h"

#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;
CSceneTrophyCollection trophy;
CSceneStressCollection caseOfDeth;
CPopUpWindowBase* nowPopUpGame = NULL;
//GameAppで遷移すると設定画面からゲームシーンに戻った際にゲームシーンが初期化されるため、
//ここで宣言し、ゲームシーンの上から設定画面を表示するようにする。
CSceneConfig sceneConfig;

CSceneGame::CSceneGame():
//scrollValueX(0),
//scrollValueY(0),
deadFlag(false),
posX(0.0f),
posY(0.0f),
poseFlg(false)
{
}

CSceneGame::~CSceneGame()
{
}

bool CSceneGame::Load()
{
	if (!pl.Load())return false;
	if (!ui.Load())return false;
	if (!stg.Load())return false;
	if(!cObstacle.Load())return false;
	return true;
}

void CSceneGame::Initialize()
{
	pl.Initialize();
	ui.Initialize();
	stg.Initialize();
	cObstacle.Initialize();



	//タイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//ポップアップ
	popUpFlg = false;

	configFlg = false;
	poseFlg = false;

	trophy.LoadTrophyFlg();
	caseOfDeth.LoadStressFlg();
}

void CSceneGame::Update()
{
	//デバッグ用　エンターで初期化
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		Initialize();
	}
	//画面遷移 ポップアップ画面 
	//死んだら、もしくはF1でゲームオーバー画面
	if (g_pInput->IsKeyPush(MOFKEY_F1) || pl.GetDead() && !popUpFlg)
	{
		//熱中症
		if(pl.GetCauseOfDeath() + 1 == CASE_INCREASEDBODYTEMPERATURE);
		{
			nowPopUpGame = new CCauseOfDeathWindow;
			nowPopUpGame->Initialize();
			popUpFlg = true;
			nowPopUpGame->SetButtonResult(CASE_INCREASEDBODYTEMPERATURE);
			caseOfDeth.GetStress(CASE_INCREASEDBODYTEMPERATURE);
		}
		nowPopUpGame = new CCauseOfDeathWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	//Rでポーズ画面
	else if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}

	//設定表示
	//ゲーム画面に戻ったらconfigFlgをfalse
	if (!sceneConfig.GetGamePlayFlg())   //ゲームに戻るボタンを押した時
		configFlg = false;
		
	if (configFlg)
	{
		sceneConfig.Update();
	}
	if (popUpFlg && !configFlg)
	{
		PopUpController();
	}
	//ポーズ画面を開いていたら、閉じるまで更新しない
	if (poseFlg)return;

	//スクロール
	stg.Update(pl);

	//プレイヤー
	pl.Update();

	for (int i = 0; i < 3; i++)
	{
		pl.Collision(cObstacle,i);
	}
	//障害物
	cObstacle.Update(pl.GetDistance(),pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY());
}

void CSceneGame::Render()
{

	stg.Render();
	/*int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);*/
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	//UIの描画
	ui.Render(pl.GetParasite(),pl.GetHungry(),pl.GetBodyTemp(),pl.GetTemperature());

	pl.Render(stg.GetScrollX(), stg.GetScrollY());

	//障害物
	cObstacle.Render(stg.GetScrollX(), stg.GetScrollY());
	//ポップアップ描画
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}
	if (configFlg)
	{
		sceneConfig.Render();
	}
}

//デバッグ
void CSceneGame::RenderDebug()
{
	//プレイヤー
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
	//障害物
	cObstacle.RenderDebug(stg.GetScrollX(), stg.GetScrollY());

	//デバッグ用
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
} 

void CSceneGame::Release()
{
	stg.Release();
	pl.Release();
	ui.Release();


	if (nowPopUpGame != NULL)
	{
		nowPopUpGame->Release();
		if (nowPopUpGame)
		{
			delete nowPopUpGame;
			nowPopUpGame = NULL;
		}
	}

	//障害物
	cObstacle.Release();
}

void CSceneGame::PopUpController()
{
	nowPopUpGame->Update();
	if (nowPopUpGame->GetButtonResult() == 1)
	{
		//リトライ、もしくはコンティニューボタンが押されたら初期化
		Initialize();
	}
	else if (nowPopUpGame->GetButtonResult() == 2)
	{
		//メニューボタンが押されたらメニュー画面に遷移
		nextScene = SCENENO_GAMEMENU;
		endFlg = true;
	}
	else if (nowPopUpGame->GetButtonResult() == 3)
	{
		//タイトルボタンが押されたらタイトル画面に遷移
		nextScene = SCENENO_TITLE;
		endFlg = true;
	}
	else if (nowPopUpGame->GetButtonResult() == 4)
	{
		//設定が押されたら設定画面を表示
		nextScene = SCENENO_CONFIG;
		configFlg = true;
		sceneConfig.SetGamePlayFlg();
		sceneConfig.Initialize();
		//設定の処理だけポップアップの消去を行わないので、ここでbuttonResultを初期化
		nowPopUpGame->SetButtonResult(0);
	}
	else if (nowPopUpGame->GetButtonResult() == 5)
	{
		//ゲームに戻るが押されたら
		poseFlg = false;
	}


	//ポップアップの変更
	if (nowPopUpGame->IsEnd())
	{
		//次のポップアップの取得
		short nextPopUp = nowPopUpGame->GetNextPopUp();
		//古いポップアップの消去
		nowPopUpGame->Release();
		delete nowPopUpGame;
		//次のポップアップ番号に応じてポップアップを初期化
		switch (nextPopUp)
		{
		case POPUPNO_CAUSEOFDEATH:
			nowPopUpGame = new CCauseOfDeathWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_POSE:
			nowPopUpGame = new CPoseWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_BACKTOTITLE:
			//nowPopUpGame = new CBackToTitleWindow;
			//nowPopUpGame->Initialize();
			break;
		case POPUPNO_RETRY:
			//nowPopUpGame = new CRetryWindow;
			//nowPopUpGame->Initialize();
			break;
		case NULL:
			nowPopUpGame = NULL;
			popUpFlg = false;
			break;
		}
	}
}