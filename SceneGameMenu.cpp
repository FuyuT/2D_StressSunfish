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

}
void CSceneGameMenu::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		//ゲームプレイ画面
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		//ゲームプレイ画面
		endFlg = true;
		nextScene = SCENENO_GAME;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_3))
	{
		//設定画面
		endFlg = true;
		nextScene = SCENENO_CONFIG;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		//ストレス集画面
		endFlg = true;
		nextScene = SCENENO_STRESSCOLLECTION;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_5))
	{
		//トロフィー集
		endFlg = true;
		nextScene = SCENENO_TROPHY;		
	}
}
void CSceneGameMenu::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ゲームメニュー画面");
	CGraphicsUtilities::RenderString(100, 350, "1キーでタイトル画面");
	CGraphicsUtilities::RenderString(100, 400, "2キーでゲーム画面");
	CGraphicsUtilities::RenderString(100, 450, "3キーで設定画面");
	CGraphicsUtilities::RenderString(100, 500, "4キーでストレス集画面");
	CGraphicsUtilities::RenderString(100, 550, "5キーでトロフィー画面");
}
void CSceneGameMenu::Release()
{

}