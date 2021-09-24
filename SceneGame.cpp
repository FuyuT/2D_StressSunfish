#include "SceneGame.h"

CSceneGame::CSceneGame()
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::Initialize()
{
}

void CSceneGame::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
	}
}

void CSceneGame::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ゲームプレイ画面");
	CGraphicsUtilities::RenderString(100, 350, "1キーでゲームメニュー");
}

void CSceneGame::Release()
{
}
