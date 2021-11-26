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
	if (GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		buttonScale = scaleController.ScaleControll(buttonScale,scaleMax,scaleMini,scaleSpeed);
		//SceneGameMenu
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !gamePlayFlg)
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneConfig::Release();
		}
		//SceneGame
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && gamePlayFlg)
		{
			CSceneConfig::Release();
			gamePlayFlg = false;
		}
	}
	else
	{
		buttonScale = scaleMini;
	}
}
void CSceneConfig::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "ê›íËâÊñ ");
	scaleController.ScaleRender(&buttonTexture, buttonPosX,buttonPosY, buttonScale);
}
void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
}