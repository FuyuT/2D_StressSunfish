#include "SceneTitle.h"
#include "GameQuitWindow.h"


CPopUpWindowBase* nowPopUpTitle = NULL;
CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::PlayBGM()
{
	cSound->BGMStop();
	cSound->Play(SOUND_TITLE_BGM);
}

bool CSceneTitle::Load()
{
	//背景
	if (!backGround_0.Load("BackGround\\Menu_0.png"))return false;
	if (!backGround_1.Load("BackGround\\Menu_1.png"))return false;
	if (!backGround_2.Load("BackGround\\Menu_2.png"))return false;
	if (!backGround_3.Load("BackGround\\Menu_3.png"))return false;
	if (!backGround_4.Load("BackGround\\Menu_4.png"))return false;
	if (!backGround_5.Load("BackGround\\Menu_5.png"))return false;
	if (!backGround_6.Load("BackGround\\Menu_6.png"))return false;
	if (!backGround_7.Load("BackGround\\Menu_7.png"))return false;
	//こんぶ
	//オブジェクトの数を取得して、数分メモリ確保
	CUtility::GetEditObjectData("Text\\menuObject_0.txt", kelp.tex, kelp.objectTotalNo, kelp.pos);
	objectKelp = new CBackObjectKelp[kelp.objectTotalNo];
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Load(kelp.tex, kelp.pos[n],-1,8);
	}
	//あかこんぶ
	CUtility::GetEditObjectData("Text\\menuObject_1.txt", redKelp.tex, redKelp.objectTotalNo, redKelp.pos);
	objectRedKelp = new CBackObjectRedKelp[redKelp.objectTotalNo];
	for (int n = 0; n < redKelp.objectTotalNo; n++)
	{
		objectRedKelp[n].Load(redKelp.tex, redKelp.pos[n], -1, 8);
	}
	//みどりこんぶ
	CUtility::GetEditObjectData("Text\\menuObject_2.txt", greenKelp.tex, greenKelp.objectTotalNo, greenKelp.pos);
	objectGreenKelp = new CBackObjectGreenKelp[greenKelp.objectTotalNo];
	for (int n = 0; n < greenKelp.objectTotalNo; n++)
	{
		objectGreenKelp[n].Load(greenKelp.tex, greenKelp.pos[n], -1, 8);
	}

	if(!titleLogoTex.Load("TitleLogo.png"))return false;
	if (!gamePrayButtonTexture.Load("ButtonStart.png"))return false;
	if(!gameFinishButtonTexture.Load("ButtonFinish.png"))return false;
	bubbleFade.Load();

	return true;
}

void CSceneTitle::Initialize()
{

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
		return;
	}

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
	//背景のオブジェクト
	//こんぶ
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Update(backGround_0.GetWidth(), 0);
	}
	//あかこんぶ
	for (int n = 0; n < redKelp.objectTotalNo; n++)
	{
		objectRedKelp[n].Update(backGround_0.GetWidth(), 0);
	}
	//みどりこんぶ
	for (int n = 0; n < greenKelp.objectTotalNo; n++)
	{
		objectGreenKelp[n].Update(backGround_0.GetWidth(), 0);
	}
}

void CSceneTitle::SoundUpdate()
{
}


void CSceneTitle::Render()
{
	backGround_0.Render(0, 0);
	backGround_1.Render(0, 0);
	backGround_2.Render(0, 0);
	backGround_3.Render(0, 0);
	backGround_4.Render(0, 0);
	//背景のオブジェクト
	//こんぶ
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Render(backGround_0.GetWidth(), 0, 0, 0.6);
	}
	backGround_5.Render(0, 0);
	backGround_6.Render(0, 0);
	backGround_7.Render(0, 0);
	//あかこんぶ
	for (int n = 0; n < redKelp.objectTotalNo; n++)
	{
		objectRedKelp[n].Render(backGround_0.GetWidth(), 0, 0, 0.6);
	}
	//みどりこんぶ
	for (int n = 0; n < greenKelp.objectTotalNo; n++)
	{
		objectGreenKelp[n].Render(backGround_0.GetWidth(), 0, 0, 0.6);
	}

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
	backGround_0.Release();
	backGround_1.Release();
	backGround_2.Release();
	backGround_3.Release();
	backGround_4.Release();
	backGround_5.Release();
	backGround_6.Release();
	backGround_7.Release();
	kelp.tex.Release();
	delete kelp.pos;
	for (int n = 0; n < kelp.objectTotalNo; n++)
	{
		objectKelp[n].Release();
	}
	delete[] objectKelp;
	for (int n = 0; n < redKelp.objectTotalNo; n++)
	{
		objectRedKelp[n].Release();
	}
	delete[] objectRedKelp;
	for (int n = 0; n < greenKelp.objectTotalNo; n++)
	{
		objectGreenKelp[n].Release();
	}
	delete[] objectGreenKelp;

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
