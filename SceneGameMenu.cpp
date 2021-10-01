#include "SceneGameMenu.h"

CSceneGameMenu:: CSceneGameMenu()
{

}

CSceneGameMenu::~CSceneGameMenu()
{
	Release();
}
void CSceneGameMenu::Initialize()
{
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	torophyButtonTexture.Load("ButtonTrophy.png");
	tutorialButtonTexture.Load("ButtonTutorial.png");
	titleButtonTexture.Load("ButtonTitle.png");

	//後でテキストデータを読み込む
	gamePlayButtonPosX = 100;
	gamePlayButtonPosY = 400;
	configButtonPosX = 100;
	configButtonPosY = 500;
	stressButtonPosX = 100;
	stressButtonPosY = 600;
	torophyButtonPosX = 100;
	torophyButtonPosY = 700;
	tutorialButtonPosX = 100;
	tutorialButtonPosY = 800;
	titleButtonPosX = 1200;
	titleButtonPosY = 800;
	
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
			nextScene = SCENENO_GAME;
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
void CSceneGameMenu::Render()
{
	gamePlayButtonTexture.Render(gamePlayButtonPosX, gamePlayButtonPosY);
	configButtonTexture.Render(configButtonPosX, configButtonPosY);
	stressButtonTexture.Render(stressButtonPosX, stressButtonPosY);
	torophyButtonTexture.Render(torophyButtonPosX, torophyButtonPosY);
	tutorialButtonTexture.Render(tutorialButtonPosX, tutorialButtonPosY);
	titleButtonTexture.Render(titleButtonPosX, titleButtonPosY);

	CGraphicsUtilities::RenderString(100, 300, "ゲームメニュー画面");
}
void CSceneGameMenu::Release()
{
	gamePlayButtonTexture.Release();
	configButtonTexture.Release();
	stressButtonTexture.Release();
	torophyButtonTexture.Release();
	tutorialButtonTexture.Release();
	titleButtonTexture.Release();
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
		return CRectangle(gamePlayButtonPosX, gamePlayButtonPosY, gamePlayButtonPosX + gamePlayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePlayButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(configButtonPosX, configButtonPosY, configButtonPosX + configButtonTexture.GetWidth(), configButtonPosY + configButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(stressButtonPosX, stressButtonPosY, stressButtonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(torophyButtonPosX, torophyButtonPosY, torophyButtonPosX + torophyButtonTexture.GetWidth(), torophyButtonPosY + torophyButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(tutorialButtonPosX, tutorialButtonPosY, tutorialButtonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}