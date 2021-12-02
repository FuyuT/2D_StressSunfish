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

	//SceneGameMenuの時とSceneGameuの時で読込みを変更
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
	buttonSelect = 0;
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
		keyModeFlg = false;
		buttonSelect = 1;
	}
	else
	{
		if (!keyModeFlg)
			buttonSelect = 0;
	}

	if (buttonSelect == 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_DOWN) || g_pInput->IsKeyPush(MOFKEY_UP))
		{
			keyModeFlg = true;
			buttonSelect = 1;
		}
		buttonScale = scaleMini;
	}
	else if (buttonSelect == 1)
	{
		buttonScale = scaleController.ScaleControll(buttonScale,scaleMax,scaleMini,scaleSpeed);
		//SceneGameMenu
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE) && !gamePlayFlg)
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneConfig::Release();
		}
		//SceneGame
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE) && gamePlayFlg)
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
	CGraphicsUtilities::RenderString(100, 300, "設定画面");
	buttonTexture.Render(buttonPosX, buttonPosY);

	muteTexBGM.Render(300, 400);
	muteTexSE.Render(300, 650);
	scaleController.ScaleRender(&buttonTexture, buttonPosX,buttonPosY, buttonScale);
	if (!cSound.GetMuteBGM())
	{
		CGraphicsUtilities::RenderString(100, 500, "muteじゃない");
	}
	else
	{
		CGraphicsUtilities::RenderString(100, 500, "mute中");
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