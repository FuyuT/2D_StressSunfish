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
	backGroundTex.Load("Title.png");

	//SceneGameMenuÇÃéûÇ∆SceneGameuÇÃéûÇ≈ì«çûÇ›ÇïœçX
	if (!gamePlayFlg)
		buttonTexture.Load("ButtonMenu.png");
	else if (gamePlayFlg)
		buttonTexture.Load("ButtonReturnGame.png");

}
void CSceneConfig::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	//SceneGameMenu
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !gamePlayFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneConfig::Release();
	}
	//SceneGame
	else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && gamePlayFlg)
	{
		CSceneConfig::Release();
		gamePlayFlg = false;
	}
}
void CSceneConfig::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "ê›íËâÊñ ");
	buttonTexture.Render(buttonPosX, buttonPosY);
}
void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
}