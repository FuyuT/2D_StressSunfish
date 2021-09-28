#include "SceneGame.h"
#define	PLAYER_SPEED 10
CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0)
{
}

CSceneGame::~CSceneGame()
{
	Release();
}

void CSceneGame::Initialize()
{
	//stressGauge.Load("gauge.png");
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");
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
	if (prec.Top < 0)
	{
		playerY = 0;
	}
	else if (prec.Bottom > stgh)
	{
		playerY = stgh - playerTexture.GetHeight();
	}
	
	//実際に移動
	playerX += moveSpeed.x;
	playerY += moveSpeed.y;


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

}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	playerTexture.Render(playerX - scrollValueX, playerY - scrollValueY);
	//CGraphicsUtilities::RenderString(100, 300, "game画面");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);
	//CGraphicsUtilities::RenderFillCircle(playerX, playerY, 20, MOF_XRGB(0, 255, 0));
	//CGraphicsUtilities::RenderFillRect(stressBarX, stressBarY, stressBarX + stressBarChenge, stressBarY + 40, MOF_XRGB(0, 255, 0));
	//stressGauge.Render(stressBarX, stressBarY);
}

void CSceneGame::Release()
{
	backGroundTexture.Release();
	playerTexture.Release();
	//stressGauge.Release();
}
