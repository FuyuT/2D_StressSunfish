#include "SceneTitle.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize()
{
}

void CSceneTitle::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		endFlg = true;
		nextScene = SCENENO_GAME;
	}
}

void CSceneTitle::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ƒ^ƒCƒgƒ‹");
}

void CSceneTitle::Release()
{
}
