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
	cSound->BGMStop();
	cSound->Play(SOUND_TITLE_BGM);
}

bool CSceneTitle::Load()
{
	if(!backGroundTex.Load("Title.png"))return false;
	if(!titleLogoTex.Load("TitleLogo.png"))return false;
	if (!gamePrayButtonTexture.Load("ButtonStart.png"))return false;
	if(!gameFinishButtonTexture.Load("ButtonFinish.png"))return false;
	bubbleFade.Load();

	return true;
}

void CSceneTitle::Initialize()
{
	Load();
	buttonSelect = 1;
	nowPopUpTitle = new CGameQuitWindow;
	nowPopUpTitle->Initialize();
	nowPopUpTitle->SetSoundManager(*cSound);
	PlayBGM();
	bubbleFade.Initialize();
}

void CSceneTitle::Update()
{
	//フェード処理
	bubbleFade.Update();
	bubbleFade.FadeIn();
	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		//シーンの遷移
		endFlg = true;
		nextScene = nextSceneTemp;
		CSceneTitle::Release();
		return;
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (popUpFlg)
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
		if (buttonSelect == 1)
		{
			gameFinishButtonScale = scaleMini;
			MouseCollision(mousePosX, mousePosY);
			if (g_pInput->IsKeyPush(MOFKEY_DOWN))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 2;
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 2;
			}
			gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				//endFlg = true;
				bubbleFade.FadeOut();
				nextSceneTemp = SCENENO_GAMEMENU;
				//nextScene = SCENENO_GAMEMENU;
				cSound->Play(SOUND_BUTTON_PUSH);
				//CSceneTitle::Release();
			}
		}
		//ゲーム終了を押したときの処理
		else if (buttonSelect == 2)
		{
			gamePlayButtonScale = scaleMini;
			MouseCollision(mousePosX, mousePosY);
			if (g_pInput->IsKeyPush(MOFKEY_DOWN) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
				cSound->Play(SOUND_BUTTON_SELECT);
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
				cSound->Play(SOUND_BUTTON_SELECT);
			}
			gameFinishButtonScale = scaleController.ScaleControll(gameFinishButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				nowPopUpTitle->Initialize();
				cSound->Play(SOUND_BUTTON_PUSH);
				popUpFlg = true;
			}
		}
	}

	SoundUpdate();
}

void CSceneTitle::SoundUpdate()
{
	if (seSelectFlg)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		seSelectFlg = false;
	}
	else if (!popUpFlg)
	{
		if (buttonSelect == 1)
		{
			gameFinishButtonScale = scaleMini;
			MouseCollision(mousePosX, mousePosY);
			if (g_pInput->IsKeyPush(MOFKEY_DOWN))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 2;
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 2;
			}
			gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				endFlg = true;
				nextScene = SCENENO_GAMEMENU;
				cSound->Play(SOUND_BUTTON_OK);
				//cSound->Play(SOUND_BUTTON_PUSH);
				CSceneTitle::Release();
			}
		}
		//ゲーム終了を押したときの処理
		else if (buttonSelect == 2)
		{
			gamePlayButtonScale = scaleMini;
			MouseCollision(mousePosX, mousePosY);
			if (g_pInput->IsKeyPush(MOFKEY_DOWN) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
				cSound->Play(SOUND_BUTTON_SELECT);
			}
			if (g_pInput->IsKeyPush(MOFKEY_UP) || GetRect(0).CollisionPoint(mousePosX, mousePosY))
			{
				buttonSelect = 1;
				cSound->Play(SOUND_BUTTON_SELECT);
			}
			gameFinishButtonScale = scaleController.ScaleControll(gameFinishButtonScale, scaleMax, scaleMini, scaleSpeed);

			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
			{
				nowPopUpTitle->Initialize();
				cSound->Play(SOUND_BUTTON_PUSH);
				popUpFlg = true;
			}
		}
	}
	//todo:soundUpdateでsoundupdate呼んでる？
	SoundUpdate();
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
	bubbleFade.Render();
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
	bubbleFade.Release();
}

void CSceneTitle::MouseCollision( int posX, int posY)
{
	if (GetRect(0).CollisionPoint(posX, posY) && buttonSelect != 1)
	{
		buttonSelect = 1;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 2;
	}
}

CRectangle CSceneTitle::GetRect(int i)
{
	if(i == 0)
		return CRectangle(gamePrayButtonPosX, gamePlayButtonPosY, gamePrayButtonPosX + gamePrayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePrayButtonTexture.GetHeight());
	 if(i == 1)
		return CRectangle(gameFinishButtonPosX, gameFinishButtonPosY, gameFinishButtonPosX + gameFinishButtonTexture.GetWidth(), gameFinishButtonPosY + gameFinishButtonTexture.GetHeight());
}
