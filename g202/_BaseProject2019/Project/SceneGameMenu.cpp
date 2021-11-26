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
	cSound.AllStop();
	cSound.Play(SOUND_MENU_BGM);
}


void CSceneGameMenu::Initialize()
{
	backGroundTex.Load("Title.png");
	textTexture.Load("MenuText.png");
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	torophyButtonTexture.Load("ButtonTrophy.png");
	tutorialButtonTexture.Load("ButtonTutorial.png");
	titleButtonTexture.Load("ButtonTitle.png");	
	scaleFlg = true;

	PlayBGM();
}

void CSceneGameMenu::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect(0).CollisionPoint(mousePosX,mousePosY))
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
			//ゲームプレイ画面
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
	}
	else
	{
		gamePlayButtonScale = 1.0f;
	}
	if (GetRect(1).CollisionPoint(mousePosX,mousePosY))
	{
		if (configButtonScale <= 1.05f && scaleFlg)
			configButtonScale += scaleSpeed;
		else
			scaleFlg = false;

		if (configButtonScale >= 1.0 && !scaleFlg)
			configButtonScale -= scaleSpeed;
		else
			scaleFlg = true;


		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//設定画面
			endFlg = true;
			nextScene = SCENENO_CONFIG;
			Release();
		}
	}
	else
	{
		configButtonScale = 1.0f;
	}
	if (GetRect(2).CollisionPoint(mousePosX,mousePosY))
	{
		if (stressButtonScale <= 1.05f && scaleFlg)
			stressButtonScale += scaleSpeed;
		else
			scaleFlg = false;

		if (stressButtonScale >= 1.0 && !scaleFlg)
			stressButtonScale -= scaleSpeed;
		else
			scaleFlg = true;
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//ストレス集画面
			endFlg = true;
			nextScene = SCENENO_STRESSCOLLECTION;
			Release();
		}
	}
	else
	{
		stressButtonScale = 1.0f;
	}
	if (GetRect(3).CollisionPoint(mousePosX,mousePosY))
	{
		if (trophyButtonScale <= 1.05f && scaleFlg)
			trophyButtonScale += scaleSpeed;
		else
			scaleFlg = false;

		if (trophyButtonScale >= 1.0 && !scaleFlg)
			trophyButtonScale -= scaleSpeed;
		else
			scaleFlg = true;

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//トロフィー集
			endFlg = true;
			nextScene = SCENENO_TROPHY;
			Release();
		}
	}
	else
	{
		trophyButtonScale = 1.0f;
	}
	if (GetRect(4).CollisionPoint(mousePosX, mousePosY))
	{
		if (tutorialButtonScale <= 1.05f && scaleFlg)
			tutorialButtonScale += scaleSpeed;
		else
			scaleFlg = false;

		if (tutorialButtonScale >= 1.0 && !scaleFlg)
			tutorialButtonScale -= scaleSpeed;
		else
			scaleFlg = true;

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//チュートリアルモード
			flgTutorial = true;
			endFlg = true;
			nextScene = SCENENO_TUTORIAL;
			Release();
		}
	}
	else
	{
		tutorialButtonScale = 1.0f;
	}
	if (GetRect(5).CollisionPoint(mousePosX, mousePosY))
	{
		if (titleButtonScale <= 1.05f && scaleFlg)
			titleButtonScale += scaleSpeed;
		else
			scaleFlg = false;

		if (titleButtonScale >= 1.0 && !scaleFlg)
			titleButtonScale -= scaleSpeed;
		else
			scaleFlg = true;
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//タイトル画面
			endFlg = true;
			nextScene = SCENENO_TITLE;
			Release();
		}
	}
	else
	{
		titleButtonScale = 1.0f;
	}
}
void CSceneGameMenu::SoundUpdate()
{

}

void CSceneGameMenu::Render()
{
	backGroundTex.Render(0,0);
	gamePlayButtonTexture.RenderScale(buttonPosX + gamePlayButtonTexture.GetWidth()/2, gamePlayButtonPosY + gamePlayButtonTexture.GetHeight()/2,gamePlayButtonScale, TEXALIGN_CENTERCENTER);
	configButtonTexture.RenderScale(buttonPosX + configButtonTexture.GetWidth() / 2, configButtonPosY + configButtonTexture.GetHeight() / 2, configButtonScale, TEXALIGN_CENTERCENTER);
	stressButtonTexture.RenderScale(buttonPosX + stressButtonTexture.GetWidth() / 2, stressButtonPosY + stressButtonTexture.GetHeight() / 2, stressButtonScale, TEXALIGN_CENTERCENTER);
	torophyButtonTexture.RenderScale(buttonPosX + torophyButtonTexture.GetWidth() / 2, torophyButtonPosY + torophyButtonTexture.GetHeight() / 2, trophyButtonScale, TEXALIGN_CENTERCENTER);
	tutorialButtonTexture.RenderScale(buttonPosX + tutorialButtonTexture.GetWidth() / 2, tutorialButtonPosY + tutorialButtonTexture.GetHeight() / 2, tutorialButtonScale, TEXALIGN_CENTERCENTER);
	titleButtonTexture.RenderScale(titleButtonPosX + titleButtonTexture.GetWidth() / 2, titleButtonPosY + titleButtonTexture.GetHeight() / 2, titleButtonScale, TEXALIGN_CENTERCENTER);
	textTexture.Render(textPosX, textPosY);
}
void CSceneGameMenu::Release()
{
	backGroundTex.Release();
	gamePlayButtonTexture.Release();
	configButtonTexture.Release();
	stressButtonTexture.Release();
	torophyButtonTexture.Release();
	tutorialButtonTexture.Release();
	titleButtonTexture.Release();
	textTexture.Release();
}


/*************************************************************************//*!
		@brief			各ボタンの矩形の取得
		@param			0...泳ぐボタンの矩形を取得
						1...設定ボタンの矩形を取得
						2...ストレス集ボタンの矩形を取得
						3...トロフィーボタンの矩形を取得
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
		return CRectangle(buttonPosX, stressButtonPosY, buttonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, torophyButtonPosY,buttonPosX + torophyButtonTexture.GetWidth(), torophyButtonPosY + torophyButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(buttonPosX, tutorialButtonPosY,buttonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}