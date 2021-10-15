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
	menuButtonTexture.Load("ButtonMenu.png");
}
void CSceneConfig::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneConfig::Release();
	}
}
void CSceneConfig::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ê›íËâÊñ ");
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
}
void CSceneConfig::Release()
{
	menuButtonTexture.Release();
}