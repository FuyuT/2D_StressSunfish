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
	if (cSound->GetNowSound() != SOUND_MENU_BGM)
	{
		cSound->BGMStop();
		cSound->Play(SOUND_MENU_BGM);
	}
}


void CSceneGameMenu::Initialize()
{
	FILE* fp = fopen("SaveDeta\\SaveTutorial.dat", "rb");
	if (fp)
	{
		fread(&tutorialFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}

	buttonSelect = 1;
	backGroundTex.Load("Title.png");
	textTexture.Load("MenuText.png");
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	trophyButtonTexture.Load("ButtonTrophy.png");
	if(tutorialFlg)
		tutorialButtonTexture.Load("ButtonTutorial.png");
	else
		tutorialButtonTexture.Load("ButtonTutorialBigin.png");

	titleButtonTexture.Load("ButtonTitle.png");	

	PlayBGM();
	bubbleFade.Load();
	bubbleFade.Initialize();
}

void CSceneGameMenu::Update()
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
		Release();
		return;
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	MouseCollision(mousePosX, mousePosY);

	//ゲームプレイボタン
	if (buttonSelect == 1)
	{
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}
		gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//ゲームプレイ画面
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_GAME;

			//endFlg = true;
			//nextScene = SCENENO_GAME;
			cSound->Play(SOUND_BUTTON_PUSH);
			cSound->Play(SOUND_BUTTON_OK);
			//Release();
		}
	}
	//設定ボタン
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
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//設定画面
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_CONFIG;

			//endFlg = true;
			//nextScene = SCENENO_CONFIG;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//トロフィー集ボタン
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
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 3;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//トロフィー集
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TROPHY;

			//endFlg = true;
			//nextScene = SCENENO_TROPHY;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//ストレス一覧ボタン
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
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 3;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 4;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//ストレス集画面
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_STRESSCOLLECTION;

			//endFlg = true;
			//nextScene = SCENENO_STRESSCOLLECTION;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//チュートリアルボタン
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
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 4;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(4).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//チュートリアルモード
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TUTORIAL;

			tutorialFlg = true;
			//endFlg = true;
			cSound->Play(SOUND_BUTTON_PUSH);
			//nextScene = SCENENO_TUTORIAL;
			FILE* fp = fopen("SaveDeta\\SaveTutorial.dat", "wb");
			if (fp)
			{
				fwrite(&tutorialFlg, sizeof(bool), 1, fp);
				fclose(fp);
			}
			//Release();
		}
	}
	//タイトルボタン
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
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_LEFT) || g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = beforButtonSelect;
			cSound->Play(SOUND_BUTTON_SELECT);
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(5).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//タイトル画面
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TITLE;
			//endFlg = true;
			//nextScene = SCENENO_TITLE;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
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
	bubbleFade.Render();
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
	bubbleFade.Release();
}

void CSceneGameMenu::MouseCollision(int posX, int posY)
{
	if (GetRect(0).CollisionPoint(posX, posY) && buttonSelect != 1)
	{
		buttonSelect = 1;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		buttonSelect = 2;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(2).CollisionPoint(posX, posY) && buttonSelect != 3)
	{
		buttonSelect = 3;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(3).CollisionPoint(posX, posY) && buttonSelect != 4)
	{
		buttonSelect = 4;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(4).CollisionPoint(posX, posY) && buttonSelect != 5)
	{
		buttonSelect = 5;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(5).CollisionPoint(posX, posY) && buttonSelect != 6)
	{
		buttonSelect = 6;
		cSound->Play(SOUND_BUTTON_SELECT);
		beforButtonSelect = 1;
	}
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