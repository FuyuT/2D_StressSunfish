#include "SceneTrophyCollection.h"
CSceneTrophyCollection::CSceneTrophyCollection()
{

}
CSceneTrophyCollection::~CSceneTrophyCollection()
{
	Release();
}
void CSceneTrophyCollection::Initialize()
{
	buttonTexture.Load("ButtonMenu.png");
}
void CSceneTrophyCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTrophyCollection::Release();
	}
}
void CSceneTrophyCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
	buttonTexture.Render(buttonPosX, buttonPosY);
}
void CSceneTrophyCollection::Release()
{
	buttonTexture.Release();
}