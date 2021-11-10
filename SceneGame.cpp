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
	Release();
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
	for (int i = 0; i < 3; i++)
	{
		numberOfTrophy[i] = TROPHY_NULL;
	}
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
	CaseOfDethController();

	//Rでポーズ画面
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
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
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat());

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
	sceneConfig.Release();

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
			TrophyController();
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

void CSceneGame::CaseOfDethController()
{
	if ((g_pInput->IsKeyPush(MOFKEY_F1) || pl.GetDead()) && !popUpFlg)
	{
		nowPopUpGame = new CCauseOfDeathWindow;
		switch (pl.GetCauseOfDeath() - 1)
		{
			//熱中症
		case CASE_INCREASEDBODYTEMPERATURE:
			nowPopUpGame->SetDethResult(CASE_INCREASEDBODYTEMPERATURE);
			newGetDeth = caseOfDeth.GetStress(CASE_INCREASEDBODYTEMPERATURE);
			break;
			//体温低下
		case CASE_LOWERBODYTEMPERATURE:
			nowPopUpGame->SetDethResult(CASE_LOWERBODYTEMPERATURE);
			newGetDeth = caseOfDeth.GetStress(CASE_LOWERBODYTEMPERATURE);
			break;
			//餓死
		case CASE_STARVATION:
			nowPopUpGame->SetDethResult(CASE_STARVATION);
			newGetDeth = caseOfDeth.GetStress(CASE_STARVATION);
			break;
			//喉詰まり
		case CASE_CLOGGEDTHROAT:
			nowPopUpGame->SetDethResult(CASE_CLOGGEDTHROAT);
			newGetDeth = caseOfDeth.GetStress(CASE_CLOGGEDTHROAT);
			break;
			//肥満
		case CASE_OBESITY:
			nowPopUpGame->SetDethResult(CASE_OBESITY);
			newGetDeth = caseOfDeth.GetStress(CASE_OBESITY);
			break;
			//衝突
		case CASE_IMPACT:
			nowPopUpGame->SetDethResult(CASE_IMPACT);
			newGetDeth = caseOfDeth.GetStress(CASE_IMPACT);
			break;
			//寄生虫
		case CASE_PARASITE:
			nowPopUpGame->SetDethResult(CASE_PARASITE);
			newGetDeth = caseOfDeth.GetStress(CASE_PARASITE);
			break;
			//ジャンプ
		case CASE_JUMP:
			nowPopUpGame->SetDethResult(CASE_JUMP);
			newGetDeth = caseOfDeth.GetStress(CASE_JUMP);
			break;
			//泡
		case CASE_BUBBLE:
			nowPopUpGame->SetDethResult(CASE_BUBBLE);
			newGetDeth = caseOfDeth.GetStress(CASE_BUBBLE);
			break;
			//ウミガメ
		case CASE_TURTLE:
			nowPopUpGame->SetDethResult(CASE_TURTLE);
			newGetDeth = caseOfDeth.GetStress(CASE_TURTLE);
			break;
			//水流
		case CASE_WATERFLOW:
			nowPopUpGame->SetDethResult(CASE_WATERFLOW);
			newGetDeth = caseOfDeth.GetStress(CASE_WATERFLOW);
			break;
		}
		nowPopUpGame->SetNewGetDeth(newGetDeth);
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
}

void CSceneGame::TrophyController()
{
	//川級
	if (pl.GetDistance() <= 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_RIVER);
		numberOfTrophy[0] = TROPHY_RIVER;
	}
	//滝級
	else if (pl.GetDistance() <= 50000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_WATERFALL);
		numberOfTrophy[0] = TROPHY_WATERFALL;
	}
	//湖級
	else if (pl.GetDistance() <= 100000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_LAKE);
		numberOfTrophy[0] = TROPHY_LAKE;
	}
	//ダム級
	else if (pl.GetDistance() <= 500000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_DAM);
		numberOfTrophy[0] = TROPHY_DAM;
	}
	//下水道級
	else if (pl.GetDistance() <= 1000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEWER);
		numberOfTrophy[0] = TROPHY_SEWER;
	}
	//インド洋級
	else if (pl.GetDistance() <= 3000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_INDIANOCEAN);
		numberOfTrophy[0] = TROPHY_INDIANOCEAN;
	}
	//アマゾン川級
	else if (pl.GetDistance() <= 5000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AMAZONROVER);
		numberOfTrophy[0] = TROPHY_AMAZONROVER;
	}
	//海級
	else if (pl.GetDistance() <= 10000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OCEAN);
		numberOfTrophy[0] = TROPHY_OCEAN;
	}
	//日本海級
	else if (pl.GetDistance() <= 30000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEAOFJAPAN);
		numberOfTrophy[0] = TROPHY_SEAOFJAPAN;
	}
	//地球一周級
	else if (pl.GetDistance() <= 40000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AROUNDTHEGLOBE);
		numberOfTrophy[0] = TROPHY_AROUNDTHEGLOBE;
	}

	//特別級
	//やる気ゼロ級
	if (pl.GetDistance() < 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_ZEROMOTIVATION);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_ZEROMOTIVATION;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_ZEROMOTIVATION;
		}
	}
	//富士山級
	if (3000 <= pl.GetDistance() <= 5000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_MOUNTFJI);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_MOUNTFJI;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_MOUNTFJI;
		}
	}
	//大阪マラソン級
	if (20000 <= pl.GetDistance() <= 42000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OSAKAMARATHON);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_OSAKAMARATHON;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_OSAKAMARATHON;
		}
	}
	//琵琶湖級
	if (40000 <= pl.GetDistance() <= 63000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_BIWALAKE);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_BIWALAKE;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_BIWALAKE;
		}
	}
	//ジャックポット級
	if (777000 <= pl.GetDistance() <= 888000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_JACKPOD);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_JACKPOD;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_JACKPOD;
		}
	}
	//才能魔級
	if (99999000 <= pl.GetDistance())
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_TALENTEDDEMON);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_TALENTEDDEMON;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_TALENTEDDEMON;
		}
	}

	nowPopUpGame->SetNumberOfTrophy(numberOfTrophy);
}