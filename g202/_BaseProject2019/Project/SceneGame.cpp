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
		nextScene = SCENENO_TITLE;
	}
}

void CSceneGame::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "game‰æ–Ê");
}

void CSceneGame::Release()
{
}
