#include "SceneGame.h"

#define	PLAYER_SPEED 10
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
	//playerTexture.Load("Player.png");

	temperatureNormal.Load("nicochyan5.png");
	temperatureHot.Load("nicochyan6.png");
	temperatureCold.Load("nicochyan4.png");

	hungerGauge.Load("stomach2.png");
	hungerGaugeFrame.Load("stomach.png");

	parasite1.Load("kiseitilyuu.png");
	parasite2.Load("kiseitilyuu2.png");
	parasite3.Load("kiseitilyuu3.png");
	parasite4.Load("kiseitilyuu4.png");
	parasite5.Load("kiseitilyuu5.png");

	pl.Initialize();
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
	
	//移動
	//初期化（しないと加速するので
	//moveSpeed.x = 0; moveSpeed.y = 0;
	/*if (g_pInput->IsKeyHold(MOFKEY_D))
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
	}*/
	//移動制限
	//左右
	//if (prec.Left < 0)
	//{
	//	playerX = 0;
	//}
	//else if (prec.Right > stgw)
	//{
	//	playerX = stgw - playerTexture.GetWidth();
	//}
	////上下


	//追加
	pl.Update();


	//
	////実際に移動
	//playerX += moveSpeed.x;
	//playerY += moveSpeed.y;


	//else if (prec.Right > backGroundTexture.GetWidth())
	//{
	//	playerX = stgw - playerTexture.GetWidth();
	//}


	//if (timeCnt == 75)
	//{
	//	stressNumber -= 1;
	//	stressBarChenge -= 3;

	//	timeCnt = 0;
	//}
	//else
	//{
	//	timeCnt += 1;
	//}

	//体温変化
	//体温下降
	if (pl.GetPosX() >= backGroundTexture.GetHeight() - 500)
	{		
		if (timeCnt >= 40)
		{
			bodyTemperature -= 1;

			timeCnt = 0;
		}
		else
		{
			timeCnt += 1;
		}
	}
	//体温上昇
	else if (pl.GetPosY() <= backGroundTexture.GetHeight() - 1200)
	{		
		if (timeCnt >= 40)
		{
			bodyTemperature += 1;

			timeCnt = 0;
		}
		else
		{
			timeCnt += 1;
		}
	}
	//体温が一定の値に戻る
	else
	{
		if (bodyTemperature > 50)
		{			
			if (timeCnt == 80)
			{
				bodyTemperature -= 1;

				timeCnt = 0;
			}
			else
			{
				timeCnt += 1;
			}
		}
		else if (bodyTemperature < 50)
		{			
			if (timeCnt == 80)
			{
				bodyTemperature += 1;

				timeCnt = 0;
			}
			else
			{
				timeCnt += 1;
			}
		}
	}

	//寄生虫(仮)
	parasiteCnt += 1;

	if (parasiteCnt == 50)
	{
		parasiteFlg = 1;
	}
	else if (parasiteCnt == 100)
	{
		parasiteFlg = 2;
	}
	else if (parasiteCnt == 150)
	{
		parasiteFlg = 3;
	}
	else if (parasiteCnt == 200)
	{
		parasiteFlg = 4;
	}
	else if (parasiteCnt == 250)
	{
		parasiteFlg = 5;
	}
	else if (parasiteCnt == 300)
	{
		parasiteFlg = 0;
		parasiteCnt = 0;
	}
}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	
	pl.Render(scrollValueX, scrollValueY);

	//playerTexture.Render(playerX - scrollValueX, playerY - scrollValueY);
	//CGraphicsUtilities::RenderString(100, 300, "game画面");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);
	
	//体温UI描画
	if (bodyTemperature >=70)
	{
		temperatureHot.Render(1600, 0);
	}
	else if (bodyTemperature <= 30)
	{
		temperatureCold.Render(1600, 0);
	}
	else
	{
		temperatureNormal.Render(1600, 0);
	}

	//寄生虫UIの描画(仮)
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
	//hungerGauge.Render(1400, 0);
	hungerGaugeFrame.Render(1400, 0);

	//デバッグ用
	CGraphicsUtilities::RenderString(10, 50,MOF_COLOR_BLACK, "%d", bodyTemperature);
}

void CSceneGame::Release()
{
	backGroundTexture.Release();
	//playerTexture.Release();
	pl.Release();
	temperatureNormal.Release();
	temperatureHot.Release();
	temperatureCold.Release();

	hungerGauge.Release();
	hungerGaugeFrame.Release();

	parasite1.Release();
	parasite2.Release();
	parasite3.Release();
	parasite4.Release();
	parasite5.Release();
}
