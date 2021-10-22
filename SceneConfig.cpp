#include "SceneConfig.h"

CSceneConfig::CSceneConfig()
{

}
CSceneConfig::~CSceneConfig()
{
	Release();
}
void CSceneConfig::Initialize()
{
	if (!gamePlayFlg)
		buttonTexture.Load("ButtonMenu.png");
	else if (gamePlayFlg)
		buttonTexture.Load("ButtonReturnGame.png");
}
void CSceneConfig::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !gamePlayFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneConfig::Release();
	}
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && gamePlayFlg)
	{
		//ゲーム画面から設定に行くパターン
		CSceneConfig::Release();
		gamePlayFlg = false;
	}
}
void CSceneConfig::Render()
{
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_XRGB(0, 0, 255));
	CGraphicsUtilities::RenderString(100, 300, "設定画面");
	buttonTexture.Render(buttonPosX, buttonPosY);
}
void CSceneConfig::Release()
{
	buttonTexture.Release();
}