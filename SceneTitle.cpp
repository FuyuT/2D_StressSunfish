#include "SceneTitle.h"
#include "GameQuitWindow.h"

CPopUpWindowBase* nowPopUpTitle = NULL;

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
	Release();
}

void CSceneTitle::PlayBGM()
{
	cSound.AllStop();
	cSound.Play(SOUND_TITLE_BGM);
}

bool CSceneTitle::Load()
{
	if(!backGroundTex.Load("Title.png"))return false;
	if(!titleLogoTex.Load("TitleLogo.png"))return false;
	if (!gamePrayButtonTexture.Load("ButtonStart.png"))return false;
	if(!gameFinishButtonTexture.Load("ButtonFinish.png"))return false;
	return true;
}

void CSceneTitle::Initialize()
{
	Load();
	nowPopUpTitle = new CGameQuitWindow;
	nowPopUpTitle->Initialize();
	PlayBGM();
}

void CSceneTitle::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (popUpFlg)
	{
		nowPopUpTitle->Initialize();
		nowPopUpTitle->Update();
		if (nowPopUpTitle->IsEnd())
		{
			nowPopUpTitle->Release();
			popUpFlg = false;
		}
	}

	SoundUpdate();
}

void CSceneTitle::SoundUpdate()
{
	else
	{
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
	 if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
