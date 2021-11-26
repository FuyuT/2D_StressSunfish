#include "SceneConfig.h"

CSceneConfig::CSceneConfig()
{

}
CSceneConfig::~CSceneConfig()
{
	Release();
}

bool CSceneConfig::Load()
{
	if (!backGroundTex.Load("Title.png"))return false;

	//SceneGameMenuÇÃéûÇ∆SceneGameuÇÃéûÇ≈ì«çûÇ›ÇïœçX
	if (!gamePlayFlg)
		buttonTexture.Load("ButtonMenu.png");
	else if (gamePlayFlg)
		buttonTexture.Load("ButtonReturnGame.png");

	if (!muteTexBGM.Load("sutoresume--ta-.png"))return false;
	if (!muteTexSE.Load("sutoresume--ta-.png"))return false;

	return true;
}

void CSceneConfig::Initialize()
{

}
void CSceneConfig::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	//SceneGameMenu
	//if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) && !gamePlayFlg)
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
	//SceneGame
	//else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) && gamePlayFlg)
	else
	{
		buttonScale = scaleMini;
	}
}

void CSceneConfig::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "ê›íËâÊñ ");
	buttonTexture.Render(buttonPosX, buttonPosY);

	muteTexBGM.Render(300, 400);
	muteTexSE.Render(300, 650);
	scaleController.ScaleRender(&buttonTexture, buttonPosX,buttonPosY, buttonScale);
}

void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
	muteTexBGM.Release();
	muteTexSE.Release();
}