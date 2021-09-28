#include "SceneTitle.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize()
{
	buttonTexture.Load("ButtonStart.png");
}

void CSceneTitle::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if ( g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX,mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTitle::Release();
	}
}

void CSceneTitle::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ƒ^ƒCƒgƒ‹‰æ–Ê");
	buttonTexture.Render(buttonPosX, buttonPosY);
}

void CSceneTitle::Release()
{
	buttonTexture.Release();
}
