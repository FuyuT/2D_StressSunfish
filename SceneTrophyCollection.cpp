#include "SceneTrophyCollection.h"
#include "TrophyWindow.h"

CPopUpWindowBase* nowPopUpTrophy = NULL;

CSceneTrophyCollection::CSceneTrophyCollection()
{

}
CSceneTrophyCollection::~CSceneTrophyCollection()
{
	Release();
}
void CSceneTrophyCollection::Initialize()
{
	menuButtonTexture.Load("ButtonMenu.png");
	popUpFlg = false;
	nowPopUpTrophy = new CTrophyWindow;
	nowPopUpTrophy->Initialize();
}
void CSceneTrophyCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTrophyCollection::Release();
	}

	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		nowPopUpTrophy->Initialize();
		nowPopUpTrophy->Update();
		if (nowPopUpTrophy->IsEnd())
		{
			popUpFlg = false;
		}
	}
}
void CSceneTrophyCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	if (popUpFlg)
	{
		nowPopUpTrophy->Render();
	}
}
void CSceneTrophyCollection::Release()
{
	menuButtonTexture.Release();
	nowPopUpTrophy->Release();
}