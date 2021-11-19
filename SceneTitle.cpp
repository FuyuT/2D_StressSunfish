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
	scaleFlg = true;
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
	else
	{
		if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
		{
			if (gamePlayButtonScale <= 1.05f && scaleFlg)
				gamePlayButtonScale += scaleSpeed;
			else
				scaleFlg = false;

			if (gamePlayButtonScale >= 1.0 && !scaleFlg)
				gamePlayButtonScale -= scaleSpeed;
			else
				scaleFlg = true;
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				endFlg = true;
				nextScene = SCENENO_GAMEMENU;
				CSceneTitle::Release();
			}
		}
		else
		{
			gamePlayButtonScale = 1.0f;
		}
		//ÉQÅ[ÉÄèIóπÇâüÇµÇΩÇ∆Ç´ÇÃèàóù
		if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
		{
			if (gameFinishButtonScale <= 1.05f && gameFinishButtonFlg)
				gameFinishButtonScale += scaleSpeed;
			else
				gameFinishButtonFlg = false;

			if (gameFinishButtonScale >= 1.0 && !gameFinishButtonFlg)
				gameFinishButtonScale -= scaleSpeed;
			else
				gameFinishButtonFlg = true;

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
			{
				popUpFlg = true;
			}
		}
		else
		{
			gameFinishButtonScale = 1.0f;
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
	gamePrayButtonTexture.RenderScale(glmePrayButtonPosX + (gamePrayButtonTexture.GetWidth()/2), gamePlayButtonPosY +(gamePrayButtonTexture.GetHeight() /2), gamePlayButtonScale,TEXALIGN_CENTERCENTER);
	gameFinishButtonTexture.RenderScale(gameFinishButtonPosX+(gameFinishButtonTexture.GetWidth()/2), gameFinishButtonPosY+ gameFinishButtonTexture.GetHeight()/2,gameFinishButtonScale,TEXALIGN_CENTERCENTER);
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
		return CRectangle(glmePrayButtonPosX, gamePlayButtonPosY, glmePrayButtonPosX + gamePrayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePrayButtonTexture.GetHeight());
	 if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
