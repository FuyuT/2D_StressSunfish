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
	cSound->AllStop();
	cSound->Play(SOUND_TITLE_BGM);
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
	buttonSelect = 1;
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
		nowPopUpTitle->Update();
		if (nowPopUpTitle->IsEnd())
		{
			nowPopUpTitle->Release();
			popUpFlg = false;
		}
	}
	else if (!popUpFlg)
	{
		if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
		{
			buttonSelect = 1;
		}
		else if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
		{
			buttonSelect = 2;
		}

		if (buttonSelect == 1)
		{
			gameFinishButtonScale = scaleMini;

			if (g_pInput->IsKeyPush(MOFKEY_DOWN))
			{
				buttonSelect = 2;
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP))
			{
				buttonSelect = 2;
			}
			gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				endFlg = true;
				nextScene = SCENENO_GAMEMENU;
				CSceneTitle::Release();
			}
		}
		//ƒQ[ƒ€I—¹‚ð‰Ÿ‚µ‚½‚Æ‚«‚Ìˆ—
		else if (buttonSelect == 2)
		{
			gamePlayButtonScale = scaleMini;
			if (g_pInput->IsKeyPush(MOFKEY_DOWN) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
			}
			gameFinishButtonScale = scaleController.ScaleControll(gameFinishButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				nowPopUpTitle->Initialize();
				popUpFlg = true;
			}
		}
	}

	SoundUpdate();
}

void CSceneTitle::SoundUpdate()
{
}

void CSceneTitle::Render()
{
	backGroundTex.Render(0, 0);
	titleLogoTex.Render(-100, -150);
	scaleController.ScaleRender(&gamePrayButtonTexture,gamePrayButtonPosX,gamePlayButtonPosY,gamePlayButtonScale);
	scaleController.ScaleRender(&gameFinishButtonTexture,gameFinishButtonPosX,gameFinishButtonPosY,gameFinishButtonScale);
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
		return CRectangle(gamePrayButtonPosX, gamePlayButtonPosY, gamePrayButtonPosX + gamePrayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePrayButtonTexture.GetHeight());
	 if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
