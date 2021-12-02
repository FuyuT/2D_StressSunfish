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
	muteTexPosBGM.x = 300;
	muteTexPosBGM.y = 400;
	muteTexPosSE.x  = 300;
	muteTexPosSE.y  = 650;
}

void CSceneConfig::SoundUpdate()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(BUTTON_MUTE_BGM).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound.GetMuteBGM())
		{
			cSound.SetVolumeBGM(0);
		}
		else
		{
			cSound.SetVolumeBGM(1);
		}

	}
	else if (GetRect(BUTTON_MUTE_SE).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound.GetMuteSE())
		{
			cSound.SetVolumeSE(0);
		}
		else
		{
			cSound.SetVolumeSE(1);
		}
	}

}

void CSceneConfig::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	SoundUpdate();
	//SceneGameMenu
	//if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) && !gamePlayFlg)
	if (GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY))
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
	if (!cSound.GetMuteBGM())
	{
		CGraphicsUtilities::RenderString(100, 500, "muteÇ∂Ç·Ç»Ç¢");
	}
	else
	{
		CGraphicsUtilities::RenderString(100, 500, "muteíÜ");
	}

}

void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
	muteTexBGM.Release();
	muteTexSE.Release();
	cSound.Release();
}