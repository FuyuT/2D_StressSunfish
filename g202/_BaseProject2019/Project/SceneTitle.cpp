#include "SceneTitle.h"
#include "GameQuitWindow.h"

CPopUpWindowBase* nowPopUpTitle = NULL;

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize()
{
	backGroundTex.Load("Title.png");
	titleLogoTex.Load("TitleLogo.png");
	gamePrayButtonTexture.Load("ButtonStart.png");
	gameFinishButtonTexture.Load("ButtonFinish.png");
	gamePrayButtonPosX = 800;
	gamePrayButtonPosY = 700;
	gameFinishButtonPosX = 800;
	gameFinishButtonPosY = 800;
	nowPopUpTitle = new CGameQuitWindow;
	nowPopUpTitle->Initialize();


}

void CSceneTitle::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTitle::Release();
	}
	//ƒQ[ƒ€I—¹‚ð‰Ÿ‚µ‚½‚Æ‚«‚Ìˆ—
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		popUpFlg = true;
	}
	
	if (popUpFlg)
	{
		nowPopUpTitle->Initialize();
		nowPopUpTitle->Update();
		if (nowPopUpTitle->IsEnd())
		{
			popUpFlg = false;
		}
	}
}

void CSceneTitle::Render()
{
	backGroundTex.Render(0, 0);
	titleLogoTex.Render(-100, -150);
	gamePrayButtonTexture.Render(gamePrayButtonPosX, gamePrayButtonPosY);
	gameFinishButtonTexture.Render(gameFinishButtonPosX, gameFinishButtonPosY);
	if (popUpFlg)
	{
		nowPopUpTitle->Render();
	}
}

void CSceneTitle::Release()
{
	backGroundTex.Release();
	titleLogoTex.Release();
	gamePrayButtonTexture.Release();
	nowPopUpTitle->Release();
	if (nowPopUpTitle)
	{
		delete nowPopUpTitle;
		nowPopUpTitle = NULL;
	}
}

CRectangle CSceneTitle::GetRect(int i)
{
	if(i == 0)
		return CRectangle(gamePrayButtonPosX, gamePrayButtonPosY, gamePrayButtonPosX + gamePrayButtonTexture.GetWidth(), gamePrayButtonPosY + gamePrayButtonTexture.GetHeight());
	else if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
