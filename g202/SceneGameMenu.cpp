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
	PlayBGM();
}

void CSceneGameMenu::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (GetRect(0).CollisionPoint(mousePosX,mousePosY))
		{
			//ゲームプレイ画面
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
		else if (GetRect(1).CollisionPoint(mousePosX,mousePosY))
		{
			//設定画面
			endFlg = true;
			nextScene = SCENENO_CONFIG;
			Release();
		}
		else if (GetRect(2).CollisionPoint(mousePosX,mousePosY))
		{
			//ストレス集画面
			endFlg = true;
			nextScene = SCENENO_STRESSCOLLECTION;
			Release();
		}
		else if (GetRect(3).CollisionPoint(mousePosX,mousePosY))
		{
			//トロフィー集
			endFlg = true;
			nextScene = SCENENO_TROPHY;
			Release();
		}
		else if (GetRect(4).CollisionPoint(mousePosX, mousePosY))
		{
			//チュートリアルモード
			flgTutorial = true;
			endFlg = true;
			nextScene = SCENENO_TUTORIAL;
			Release();
		}
		else if (GetRect(5).CollisionPoint(mousePosX, mousePosY))
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
	gamePlayButtonTexture.Render(buttonPosX, gamePlayButtonPosY);
	configButtonTexture.Render(buttonPosX, configButtonPosY);
	stressButtonTexture.Render(buttonPosX, stressButtonPosY);
	torophyButtonTexture.Render(buttonPosX, torophyButtonPosY);
	tutorialButtonTexture.Render(buttonPosX, tutorialButtonPosY);
	titleButtonTexture.Render(titleButtonPosX, titleButtonPosY);
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