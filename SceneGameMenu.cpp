#include "SceneGameMenu.h"

CSceneGameMenu:: CSceneGameMenu()
{

}

CSceneGameMenu::~CSceneGameMenu()
{
	Release();
}

void CSceneGameMenu::PlayBGM()
{
	cSound->AllStop();
	cSound->Play(SOUND_MENU_BGM);
}


void CSceneGameMenu::Initialize()
{
	buttonSelect = 0;
	backGroundTex.Load("Title.png");
	textTexture.Load("MenuText.png");
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	trophyButtonTexture.Load("ButtonTrophy.png");
	tutorialButtonTexture.Load("ButtonTutorial.png");
	titleButtonTexture.Load("ButtonTitle.png");	

	PlayBGM();
}

void CSceneGameMenu::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect(0).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 1;
	}
	else if (GetRect(1).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 2;
	}
	else if (GetRect(2).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 3;
	}
	else if (GetRect(3).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 4;
	}
	else if (GetRect(4).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 5;
	}
	else if (GetRect(5).CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 6;
	}
	else
	{
		if (!keyModeFlg)
			buttonSelect = 0;
	}

	if (buttonSelect == 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_DOWN) || g_pInput->IsKeyPush(MOFKEY_UP))
		{
			keyModeFlg = true;
			buttonSelect = 1;
		}
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;
	}
	else if (buttonSelect == 1)
	{
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 1;
			buttonSelect = 6;
		}
		gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//ゲームプレイ画面
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
	}
	else if (buttonSelect == 2)
	{
		gamePlayButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		configButtonScale = scaleController.ScaleControll(configButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 3;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 2;
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//設定画面
			endFlg = true;
			nextScene = SCENENO_CONFIG;
			Release();
		}
	}
	else if (buttonSelect == 3)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		trophyButtonScale = scaleController.ScaleControll(trophyButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 4;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 2;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 3;
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//トロフィー集
			endFlg = true;
			nextScene = SCENENO_TROPHY;
			Release();
		}
	}
	else if (buttonSelect == 4)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		stressButtonScale = scaleController.ScaleControll(stressButtonScale, scaleMax, scaleMini, scaleSpeed);
			
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 5;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 3;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 4;
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//ストレス集画面
			endFlg = true;
			nextScene = SCENENO_STRESSCOLLECTION;
			Release();
		}
	}
	else if (buttonSelect == 5)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		tutorialButtonScale = scaleController.ScaleControll(tutorialButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 4;
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 5;
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//チュートリアルモード
			flgTutorial = true;
			endFlg = true;
			nextScene = SCENENO_TUTORIAL;
			Release();
		}
	}
	else if (buttonSelect == 6)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleController.ScaleControll(titleButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 1;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
		}
		if (g_pInput->IsKeyPush(MOFKEY_LEFT) || g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = beforButtonSelect;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//タイトル画面
			endFlg = true;
			nextScene = SCENENO_TITLE;
			Release();
		}
	}
}
void CSceneGameMenu::SoundUpdate()
{

}

void CSceneGameMenu::Render()
{
	backGroundTex.Render(0,0);
	scaleController.ScaleRender(&gamePlayButtonTexture,buttonPosX,gamePlayButtonPosY,gamePlayButtonScale);
	scaleController.ScaleRender(&configButtonTexture,buttonPosX,configButtonPosY,configButtonScale);
	scaleController.ScaleRender(&stressButtonTexture,buttonPosX,stressButtonPosY,stressButtonScale);
	scaleController.ScaleRender(&trophyButtonTexture,buttonPosX,trophyButtonPosY,trophyButtonScale);
	scaleController.ScaleRender(&tutorialButtonTexture,buttonPosX,tutorialButtonPosY,tutorialButtonScale);
	scaleController.ScaleRender(&titleButtonTexture,titleButtonPosX,titleButtonPosY,titleButtonScale);
	textTexture.Render(textPosX, textPosY);
}
void CSceneGameMenu::Release()
{
	backGroundTex.Release();
	gamePlayButtonTexture.Release();
	configButtonTexture.Release();
	stressButtonTexture.Release();
	trophyButtonTexture.Release();
	tutorialButtonTexture.Release();
	titleButtonTexture.Release();
	textTexture.Release();
}


/*************************************************************************//*!
		@brief			各ボタンの矩形の取得
		@param			0...泳ぐボタンの矩形を取得
						1...設定ボタンの矩形を取得
						2...トロフィーボタンの矩形を取得
						3...ストレス集ボタンの矩形を取得
						4...チュートリアルボタンの矩形を取得
						5...タイトルボタンの矩形を取得

		@return			引数に対応したボタンの矩形
*//**************************************************************************/
CRectangle CSceneGameMenu::GetRect(int i)
{
	if (i == 0)
		return CRectangle(buttonPosX, gamePlayButtonPosY, buttonPosX + gamePlayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePlayButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonPosX, configButtonPosY, buttonPosX + configButtonTexture.GetWidth(), configButtonPosY + configButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonPosX, trophyButtonPosY,buttonPosX + trophyButtonTexture.GetWidth(), trophyButtonPosY + trophyButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, stressButtonPosY, buttonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(buttonPosX, tutorialButtonPosY,buttonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}