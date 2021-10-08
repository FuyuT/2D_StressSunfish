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
	buttonTexture.Load("ButtonMenu.png");
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
	buttonTexture.Render(buttonPosX, buttonPosY);
}
void CSceneConfig::Release()
{
	buttonTexture.Release();
}