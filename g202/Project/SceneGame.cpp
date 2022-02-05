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
poseFlg(false),
startFlg(false),
popUpGuardFlg(false)
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::PlayBGM()
{
	cSound->BGMStop();
	cSound->Play(SOUND_GAME_BGM);
}


bool CSceneGame::Load()
{
	if (!pl.Load())return false;
	if (!ui.Load())return false;
	if (!stg.Load())return false;
	if(!cObstacle.Load())return false;
	bubbleFade.Load();

	return true;
}

void CSceneGame::Initialize()
{
	pl.Initialize();
	ui.Initialize();
	stg.Initialize();
	cObstacle.Initialize();
	cObstacle.SetSoundManager(*cSound);
	bubbleFade.Initialize();
	pl.SetSoundManager(*cSound);
	sceneConfig.SetSoundManager(*cSound);

	//イベント
	eventRandom.SetSeed((MofU32)time(NULL));
	//確認のためにイベントの発生までを早くしている
	eventTimer.SetTotalTime(20);
	eventNum = Event::Event_None;

	//タイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//ポップアップ
	popUpFlg = false;

	configFlg = false;
	poseFlg = false;
	startFlg = false;
	popUpGuardFlg = false;

	trophy.LoadTrophyFlg();
	caseOfDeth.LoadStressFlg();
	for (int i = 0; i < 3; i++)
	{
		numberOfTrophy[i] = TROPHY_NULL;
	}
	PlayBGM();
	seFlg = false;
	alertFlg = false;
	goFlg = false;
	hungryFlg = false;
}

void CSceneGame::EventUpdate()
{
	if (!pl.GetDead())
	{
		eventTimer.StartTimer();
		if (eventTimer.GetNowtime() < 0)
		{
			eventNum = eventRandom.Random(Event::Event_Summer, Event_Count);
			seFlg = true;
			eventTimer.SetTotalTime(40);
		}
		else if (eventTimer.GetNowtime() < 20)
		{
			eventNum = Event::Event_None;
		}
		eventTimer.Update();

		if (seFlg)
		{
			if (eventNum == Event::Event_ShoalSardine)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Garbage)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Turtle)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Summer)
			{
				cSound->Play(SOUND_EVENT_SUMMER);
				seFlg = false;
			}
			if (eventNum == Event::Event_Winter)
			{
				cSound->Play(SOUND_EVENT_WINTER);
				seFlg = false;
			}
		}
	}
	else
	{
		eventNum = Event::Event_None;
	}
}

void CSceneGame::Update()
{
	//デバッグ用　エンターで初期化
	/*if (g_pInput->IsKeyPush(MOFKEY_5))
	{
		Initialize();
		if (nowPopUpGame != nullptr)
		{
			nowPopUpGame->Release();
		}
	}*/

	//フェード処理
	bubbleFade.Update();
	bubbleFade.FadeIn();


	//設定表示
	//ゲームに戻るボタンを押した時
	//ゲーム画面に戻ったらconfigFlgをfalse
	if (!sceneConfig.GetGamePlayFlg())
	{
		configFlg = false;
	}
	else
	{
		bubbleFade.Initialize();
	}
	if (configFlg)
	{
		sceneConfig.Update();
	}

	//スクロール
	if (!poseFlg)
	{
		stg.Update(pl);
	}

	//フェード
	if (bubbleFade.GetFade())
	{
		return;
	}
	else if (bubbleFade.GetFadeOutEnd())
	{
		if (nextSceneTemp == SCENENO_CONFIG)
		{
			configFlg = true;
			sceneConfig.SetGamePlayFlg();
			sceneConfig.Load();
			sceneConfig.Initialize();
		}
		else
		{
			if (nowPopUpGame != nullptr)
			{
				nowPopUpGame->Release();
			}

			if (nextSceneTemp == SCENENO_GAME)
			{
				//リトライ、もしくはコンティニューボタンが押されたら初期化
				Initialize();
				return;
			}
			else
			{
				endFlg = true;
			}
		}

		//シーンの遷移
		nextScene = nextSceneTemp;
		return;
	}

	//画面遷移 ポップアップ画面 
	//死んだら、もしくはF1でゲームオーバー画面
	CaseOfDethController();

	//Rでポーズ画面
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->SetSoundManager(*cSound);
		nowPopUpGame->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && popUpFlg && !pl.GetDead() && !configFlg)
	{
		nowPopUpGame->Release();
		nowPopUpGame = NULL;
		popUpFlg = false;
		poseFlg = false;
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

	ui.Update(eventNum);
	ui.SetPos(pl.GetPosX(), pl.GetPosY());

	if (!startFlg)return;

	//イベント
	EventUpdate();

	//プレイヤー
	for (int i = 0; i < 5; i++)
	{
		pl.Collision(cObstacle, i, false, Task_End);
	}
	//プレイヤー
	pl.Update(false, Task_End, eventNum);

	//障害物
	cObstacle.Update(pl.GetDistance(), pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY(), Task_End, eventNum);

	//SE
	SEUpdate();
}

void CSceneGame::Render()
{
	stg.Render();
	/*int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);*/

	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	if (ui.StartSign(poseFlg))startFlg = true;

	//障害物
	cObstacle.Render(stg.GetScrollX(), stg.GetScrollY());

	//最前面の岩背景
	stg.ForeGroundRender();

	//UIの描画
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(),false,eventNum, pl.GetPosY(), stg.GetScrollY());

	//ポップアップ描画
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}
	if (configFlg)
	{
		sceneConfig.Render();
	}
	bubbleFade.Render();
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
	bubbleFade.Release();
}

//デバッグ
void CSceneGame::RenderDebug()
{
	////プレイヤー
	//pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
	////障害物
	//cObstacle.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneGame::SEUpdate()
{
	//体温アラート
	if ((500 * (pl.GetTemperature() * 0.01f) <= 150 || 500 * (pl.GetTemperature() * 0.01f) >= 330) && !alertFlg)
	{
		cSound->Play(SOUND_ALERTTEMPERATURE);
		alertFlg = true;
	}
	else if (!(500 * (pl.GetTemperature() * 0.01f) >= 330) && 500 * (pl.GetTemperature() * 0.01f) > 150 && alertFlg)
	{
		alertFlg = false;
	}
	else if (!(500 * (pl.GetTemperature() * 0.01f) <= 150) && 500 * (pl.GetTemperature() * 0.01f) < 330 && alertFlg)
	{
		alertFlg = false;
	}
	//スタートSE
	if (startFlg && !goFlg)
	{
		cSound->Play(SOUND_GO);
		goFlg = true;
	}
	//空腹SE
	if (pl.GetHungry() >= 62 && !hungryFlg)
	{
		cSound->Play(SOUND_HUNGRY);
		hungryFlg = true;
	}
	else if (pl.GetHungry() < 62 && hungryFlg)
	{
		hungryFlg = false;
	}
}

void CSceneGame::PopUpController()
{
	nowPopUpGame->Update();
	if (nowPopUpGame->GetButtonResult() == 1)
	{
		//リトライ、もしくはコンティニューボタンが押されたら初期化
		//Initialize();
		popUpGuardFlg = true;
		nextSceneTemp = SCENENO_GAME;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpGame->GetButtonResult() == 2)
	{
		//メニューボタンが押されたらメニュー画面に遷移
		//nextScene = SCENENO_GAMEMENU;
		//endFlg = true;
		popUpGuardFlg = true;
		nextSceneTemp = SCENENO_GAMEMENU;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpGame->GetButtonResult() == 3)
	{
		//タイトルボタンが押されたらタイトル画面に遷移
		//nextScene = SCENENO_TITLE;
		//endFlg = true;
		popUpGuardFlg = true;
		nextSceneTemp = SCENENO_TITLE;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpGame->GetButtonResult() == 5)
	{
		//ゲームに戻るが押されたら
		popUpFlg = false;
		poseFlg = false;
	}
	else if (nowPopUpGame->GetButtonResult() == 4)
	{
		//設定が押されたら設定画面を表示
		//nextScene = SCENENO_CONFIG;
		nextSceneTemp = SCENENO_CONFIG;
		bubbleFade.FadeOut();

		//configFlg = true;
		//sceneConfig.SetGamePlayFlg();
		//sceneConfig.Load();
		//sceneConfig.Initialize();
		//設定の処理だけポップアップの消去を行わないので、ここでbuttonResultを初期化
		nowPopUpGame->SetButtonResult(0);

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
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			TrophyController();
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_POSE:
			nowPopUpGame = new CPoseWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_BACKTOTITLE:
			nowPopUpGame = new CBackToTitleWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_RETRY:
			nowPopUpGame = new CRetryWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
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
	if ((pl.GetDead()) && !popUpFlg && !popUpGuardFlg)
	{
		cSound->Play(SOUND_RESULT);
		nowPopUpGame = new CCauseOfDeathWindow;
		switch (pl.GetCauseOfDeath())
		{
			//熱中症
		case CAUSE_Hyperthermia:
			nowPopUpGame->SetDethResult(CAUSE_Hyperthermia);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Hyperthermia);
			break;
			//体温低下
		case CAUSE_Frozen:
			nowPopUpGame->SetDethResult(CAUSE_Frozen);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Frozen);
			break;
			//餓死
		case CAUSE_Starvation:
			nowPopUpGame->SetDethResult(CAUSE_Starvation);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Starvation);
			break;
			//喉詰まり
		case CAUSE_ChokeOnShell:
			nowPopUpGame->SetDethResult(CAUSE_ChokeOnShell);
			newGetDeth = caseOfDeth.GetStress(CAUSE_ChokeOnShell);
			break;
			//肥満
		case CAUSE_Obesity:
			nowPopUpGame->SetDethResult(CAUSE_Obesity);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Obesity);
			break;
			//衝突
		case CAUSE_Obstacle:
			nowPopUpGame->SetDethResult(CAUSE_Obstacle);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Obstacle);
			break;
			//寄生虫
		case CAUSE_Parasite:
			nowPopUpGame->SetDethResult(CAUSE_Parasite);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Parasite);
			break;
			//ジャンプ
		case CAUSE_Jump:
			nowPopUpGame->SetDethResult(CAUSE_Jump);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Jump);
			break;
			//泡
		case CAUSE_Bubble:
			nowPopUpGame->SetDethResult(CAUSE_Bubble);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Bubble);
			break;
			//ウミガメ
		case CAUSE_SeaTurtle:
			nowPopUpGame->SetDethResult(CAUSE_SeaTurtle);
			newGetDeth = caseOfDeth.GetStress(CAUSE_SeaTurtle);
			break;
			//水流
		case CAUSE_WaterFlow:
			nowPopUpGame->SetDethResult(CAUSE_WaterFlow);
			newGetDeth = caseOfDeth.GetStress(CAUSE_WaterFlow);
			break;
		case CAUSE_ShoalFish:
			nowPopUpGame->SetDethResult(CAUSE_ShoalFish);
			newGetDeth = caseOfDeth.GetStress(CAUSE_ShoalFish);
			break;
		}
		nowPopUpGame->SetSoundManager(*cSound);
		nowPopUpGame->SetNewGetDeath(newGetDeth);
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
}

void CSceneGame::TrophyController()
{
	//川級
	if (pl.GetDistance() > 0)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_RIVER);
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_RIVER;
		//やる気ゼロ級
		if (pl.GetDistance() <= 500)
		{
			newGetTrophy = trophy.GetTrophy(TROPHY_ZEROMOTIVATION);
			numberOfTrophy[1] = numberOfTrophy[0];
			numberOfTrophy[0] = TROPHY_ZEROMOTIVATION;
		}
	}
	//滝級
	if (pl.GetDistance() > 1000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_WATERFALL);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_WATERFALL;
	}
	//湖級
	if (pl.GetDistance() > 2500)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_LAKE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_LAKE;
	}

	//富士山級
	if (3000 <= pl.GetDistance() && pl.GetDistance() < 4000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_MOUNTFJI);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_MOUNTFJI;
	}

	//ダム級
	if (pl.GetDistance() > 5000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_DAM);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_DAM;
	}
	//下水道級
	if (pl.GetDistance() > 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEWER);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_SEWER;
	}
	//インド洋級
	if (pl.GetDistance() > 25000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_INDIANOCEAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_INDIANOCEAN;
	}
	//大阪マラソン級
	if (42000 <= pl.GetDistance() && pl.GetDistance() < 43000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OSAKAMARATHON);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_OSAKAMARATHON;
	}
	//アマゾン川級
	if (pl.GetDistance() > 50000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AMAZONROVER);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_AMAZONROVER;
	}
	//琵琶湖級
	if (63000 <= pl.GetDistance() && pl.GetDistance() < 64000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_BIWALAKE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_BIWALAKE;
	}
	//海級
	if (pl.GetDistance() > 100000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OCEAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_OCEAN;
	}
	//日本海級
	if (pl.GetDistance() > 200000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEAOFJAPAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_SEAOFJAPAN;
	}
	//地球一周級
	if ( pl.GetDistance() > 300000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AROUNDTHEGLOBE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_AROUNDTHEGLOBE;
	}
	//ジャックポット級
	if (777000 <= pl.GetDistance() && pl.GetDistance() < 778000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_JACKPOD);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_JACKPOD;
	}
	//才能魔級
	if (999000 <= pl.GetDistance())
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_TALENTEDDEMON);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_TALENTEDDEMON;
	}

	nowPopUpGame->SetNewGetTrophy(newGetTrophy);
	nowPopUpGame->SetDistance(pl.GetDistance());
	nowPopUpGame->SetNumberOfTrophy(numberOfTrophy);
}