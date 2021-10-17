#include "SceneGame.h"
#include "SceneConfig.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"

#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;
CPopUpWindowBase* nowPopUpGame = NULL;
//GameAppで遷移すると設定画面からゲームシーンに戻った際にゲームシーンが初期化されるため、
//ここで宣言し、ゲームシーンの上から設定画面を表示するようにする。
CSceneConfig sceneConfig;

CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0),
deadFlag(false),
posX(0.0f),
posY(0.0f)
{
}

CSceneGame::~CSceneGame()
{
}

bool CSceneGame::Load()
{
	//障害物
	if(!cObstacle.Load())return false;
	return true;
}

void CSceneGame::Initialize()
{
	pl.Initialize();
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");

	ui.Initialize();

	//障害物
	ene.Initialize();
	ene.Start(scrollValueX, scrollValueY, 0);
	posX = 500;
	posY = 500;
	cObstacle.Initialize();
	//タイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//ポップアップ
	popUpFlg = false;

	configFlg = false;
}

void CSceneGame::Update()
{
	//画面遷移
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}

	//スクロール
	CRectangle prec = pl.GetRect();
	//スクリーン幅
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//ステージの幅四割の境界線
	float hsw = sw * 0.4f;
	float hsh = sh * 0.4f;
	//ステージ全体の幅 とりあえず画像の幅で
	float stgw = backGroundTexture.GetWidth();
	float stgh = backGroundTexture.GetHeight();
	//左
	if (prec.Left - scrollValueX < hsw)
	{
		//境界線hswより進んだ値を、scrolValueに入れる
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//右
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		if (scrollValueX >= stgw - sw)
		{
			scrollValueX = stgw - sw;
		}
	}
	//上
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//下
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}


	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		nowPopUpGame = new CCauseOfDeathWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		PopUpController();
	}

	//プレイヤー
	pl.Update();
	pl.Collision(ene);

	//障害物
	ene.Update();
	cObstacle.Update(scrollValueX, scrollValueY);

	if (!sceneConfig.GetGamePlayFlg())
		configFlg = false;


	//設定表示
	if (configFlg)
	{
		sceneConfig.Update();
	}
}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	//UIの描画
	ui.Render(pl.GetParasite(),pl.GetHungry(),pl.GetBodyTemp(),pl.GetTemperature());

	//ポップアップ描画
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}
	if (configFlg)
	{
		sceneConfig.Render();
	}

	//障害物
	cObstacle.Render(scrollValueX, scrollValueY);

}

//デバッグ
void CSceneGame::RenderDebug()
{
	//プレイヤー
	pl.RenderDebug(scrollValueX, scrollValueY);
	//障害物
	cObstacle.RenderDebug(scrollValueX, scrollValueY);

	//障害物
	ene.Render(scrollValueX, scrollValueY);
	pl.Render(scrollValueX, scrollValueY);
	//デバッグ用
	pl.RenderDebug(scrollValueX, scrollValueY);
} 

void CSceneGame::Release()
{
	backGroundTexture.Release();
	pl.Release();
	ene.Release();
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
		configFlg = true;
		sceneConfig.SetGamePlayFlg();
		sceneConfig.Initialize();
	}
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
			nowPopUpGame = new CBackToTitleWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_RETRY:
			nowPopUpGame = new CRetryWindow;
			nowPopUpGame->Initialize();
			break;
		case NULL:
			nowPopUpGame = NULL;
			popUpFlg = false;
			break;
		}
	}
}