#include "SceneGame.h"

CSceneGame::CSceneGame()
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::Initialize()
{
	//CUtilities::SetCurrentDirectory("Resource");

	//stressGauge.Load("gauge.png");
}

void CSceneGame::Update()
{
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		if (playerX < 500)
		{
			playerX += 1.0f;
		}
		
		distancePlayer += 10.0f;
	}

	if (timeCnt == 75)
	{
		stressNumber -= 1;
		stressBarChenge -= 3;

		timeCnt = 0;
	}
	else
	{
		timeCnt += 1;
	}

	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}
}

void CSceneGame::Render()
{
	//CGraphicsUtilities::RenderString(100, 300, "game‰æ–Ê");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);
	CGraphicsUtilities::RenderFillCircle(playerX, playerY, 20, MOF_XRGB(0, 255, 0));
	//CGraphicsUtilities::RenderFillRect(stressBarX, stressBarY, stressBarX + stressBarChenge, stressBarY + 40, MOF_XRGB(0, 255, 0));
	//stressGauge.Render(stressBarX, stressBarY);
}

void CSceneGame::Release()
{
	//stressGauge.Release();
}
