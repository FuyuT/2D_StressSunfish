#include "SceneGame.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;

CPopUpWindowBase* nowPopUpGame = NULL;

CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0)
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::Initialize()
{
	//stressGauge.Load("gauge.png");
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");

	stressMeter.Load("sutoresume--ta-.png");

	tempNormal.Load("nicochyan5.png");
	tempHot.Load("nicochyan6.png");
	tempCold.Load("nicochyan4.png");

	tempMeter.Load("temperatureMeter.png");
	tempMeterFrame.Load("temperatureMeterFrame.png");

	hungerGauge.Load("stomach2.png");
	hungerGaugeFrame.Load("stomach.png");

	parasite1.Load("kiseitilyuu.png");
	parasite2.Load("kiseitilyuu2.png");
	parasite3.Load("kiseitilyuu3.png");
	parasite4.Load("kiseitilyuu4.png");
	parasite5.Load("kiseitilyuu5.png");

	//タイマー
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	nowPopUpGame = new CCauseOfDeathWindow;
	nowPopUpGame->Initialize();
}

void CSceneGame::Update()
{
	//画面遷移
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}

	//タイマー
	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();
	//スクロール
	CRectangle prec = GetRect();
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
	
	//移動
	//初期化（しないと加速するので
	moveSpeed.x = 0; moveSpeed.y = 0;
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		moveSpeed.x += PLAYER_SPEED;
		distancePlayer += 10.0f;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_A))
	{
		moveSpeed.x -= PLAYER_SPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveSpeed.y -= PLAYER_SPEED;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveSpeed.y += PLAYER_SPEED;
	}
	//移動制限
	//左右
	if (prec.Left < 0)
	{
		playerX = 0;
	}
	else if (prec.Right > stgw)
	{
		playerX = stgw - playerTexture.GetWidth();
	}
	//上下

	
	//実際に移動
	playerX += moveSpeed.x;
	playerY += moveSpeed.y;


	//else if (prec.Right > backGroundTexture.GetWidth())
	//{
	//	playerX = stgw - playerTexture.GetWidth();
	//}



	//体温変化
	//体温下降
	if (playerY >= backGroundTexture.GetHeight() - 330)
	{		
		//タイマーセット
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp > -30)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
			}
			tempTimer.SetTotalTime(1);
		}
	}
	//体温上昇
	else if (playerY <= backGroundTexture.GetHeight() - 1200)
	{	
		//タイマーセット
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp < 50)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
			}
			tempTimer.SetTotalTime(1);
		}
	}
	//体温が一定の値に戻る
	else
	{
		if (bodyTemp > 10)
		{	
			//タイマーセット
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
				tempTimer.SetTotalTime(2);
			}
		}
		else if (bodyTemp < 10)
		{	
			//タイマーセット
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
				tempTimer.SetTotalTime(2);
			}
		}
	}

	//寄生虫
	if (parasiteFlg < 5)
	{
		//タイマーセット
		parasiteTimer.StartTimer();
		if (parasiteTimer.GetNowtime() <= 0)
		{
			parasiteFlg += 1;
			parasiteTimer.SetTotalTime(15);
		}

	}

	//空腹ゲージ
	//タイマーセット
	hungerTimer.StartTimer();
	if (hungerTimer.GetNowtime() <= 0)
	{
		if (hungerRegion < 160)
		{
			hungerRegion += 3;
		}		
		hungerTimer.SetTotalTime(3);
	}

	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		PopUpController();
	}
}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	playerTexture.Render(playerX - scrollValueX, playerY - scrollValueY);
	//CGraphicsUtilities::RenderString(100, 300, "game画面");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	stressMeter.Render(1600, 0);
	
	//体温UI描画
	if (bodyTemp >=40)
	{
		tempHot.Render(1600, 0);
	}
	else if (bodyTemp <= -20)
	{
		tempCold.Render(1600, 0);
	}
	else
	{
		tempNormal.Render(1600, 0);
	}

	//温度計UI描画
	tempMeterFrame.Render(1550,200);
	CRectangle rec1(0, tempRegion, 500, 500);
	tempMeter.Render(1550, 200 + tempRegion,rec1);

	//寄生虫UIの描画
	switch (parasiteFlg)
	{
	case 1:
		parasite1.Render(1600, 0);
		break;
	case 2:
		parasite2.Render(1600, 0);
		break;
	case 3:
		parasite3.Render(1600, 0);
		break;
	case 4:
		parasite4.Render(1600, 0);
		break;
	case 5:
		parasite5.Render(1600, 0);
		break;
	}

	//空腹ゲージUI描画
	CRectangle rec2(0, 0, 330, 200);
	hungerGaugeFrame.Render(1400, 0,rec2);
	CRectangle rec3(0,hungerRegion, 330, 200);
	hungerGauge.Render(1400,hungerRegion,rec3);

	//ポップアップ描画
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}

	//デバッグ用
	CGraphicsUtilities::RenderString(10, 50,MOF_COLOR_BLACK, "温度  %d", bodyTemp);
	tempTimer.Render(10, 70);
	hungerTimer.Render(10, 90);
	parasiteTimer.Render(10, 110);
}

void CSceneGame::Release()
{
	backGroundTexture.Release();
	playerTexture.Release();

	stressMeter.Release();

	tempNormal.Release();
	tempHot.Release();
	tempCold.Release();

	tempMeter.Release();
	tempMeterFrame.Release();

	hungerGauge.Release();
	hungerGaugeFrame.Release();

	parasite1.Release();
	parasite2.Release();
	parasite3.Release();
	parasite4.Release();
	parasite5.Release();

	nowPopUpGame->Release();
	if (nowPopUpGame)
	{
		delete nowPopUpGame;
		nowPopUpGame = NULL;
	}
}

void CSceneGame::PopUpController()
{
	nowPopUpGame->Update();
	if (nowPopUpGame->IsEnd())
	{
		//次のポップアップの取得
		short nextPopUp = nowPopUpGame->GetNextPopUp();
		//古いポップアップの消去
		delete nowPopUpGame;
		//次のポップアップ番号に応じてポップアップを初期化
		switch (nextPopUp)
		{
		case POPUPNO_CAUSEOFDEATH:
			nowPopUpGame = new CCauseOfDeathWindow;
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			break;
		case NULL:
			nowPopUpGame = new CCauseOfDeathWindow;
			popUpFlg = false;
		}
		nowPopUpGame->Initialize();
	}
}