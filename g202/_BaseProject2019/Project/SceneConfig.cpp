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


	if (!volumeBarTex.Load("UI\\ScrollBar.png"))return false;
	if (!volumeControlButton.Load("UI\\PearlButton.png"))return false;
	if (!oysterCloseBottomTex.Load("UI\\PearlOysterCloseBottom.png"))return false;
	if (!oysterCloseTopTex.Load("UI\\PearlOysterCloseTop.png"))return false;
	if (!oysterOpenTex.Load("UI\\PearlOysterOpen.png"))return false;
	return true;
}

void CSceneConfig::Initialize()
{
	BGMControlButtonPos.x = VOLUME_CONTROL_BUTTON_POS_X;
	BGMControlButtonPos.y = BGM_CONTROL_BUTTON_POS_Y;
	SEControlButtonPos.x = VOLUME_CONTROL_BUTTON_POS_X;
	SEControlButtonPos.y = SE_CONTROL_BUTTON_POS_X;
	buttonSelect = 1;
}

//todo:mute機能作る あとミュートから戻した時の音どうするかだけ
void CSceneConfig::SoundMute()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(BUTTON_MUTE_BGM).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound->GetMuteBGM())
		{
			cSound->SetVolumeBGM(0);
		}
		else
		{
			cSound->SetVolumeBGM(1);
		}

	}
	else if (GetRect(BUTTON_MUTE_SE).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound->GetMuteSE())
		{
			cSound->SetVolumeSE(0);
		}
		else
		{
			cSound->SetVolumeSE(1);
		}
	}
}

void CSceneConfig::DragVolumeButton(Vector2& pos,int buttonNo,bool& scrollFlg)
{
	//マウスでアイコンをドラッグして音量調節する機能
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	//static bool controlBGMFlg = false;
	if (GetRect(buttonNo).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		scrollFlg = true;
	}
	else if(g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
	{
		scrollFlg = false;
	}

	if (scrollFlg)
	{
		pos.x = mousePosX;
	}

	//if (GetRect(BUTTON_BGM_CONTROL).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
	//{
	//}
	//else if (g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
	//{
	//	controlBGMFlg = false;
	//}

}

void CSceneConfig::VolumeAdjustment()
{
	//BGMの最大値（ボタンの最大移動量）
	if (BGMControlButtonPos.x > VOLUME_CONTROL_BUTTON_MAX)
	{
		BGMControlButtonPos.x = VOLUME_CONTROL_BUTTON_MAX;
	}
	else if (BGMControlButtonPos.x < VOLUME_CONTROL_BUTTON_MIN)
	{
		BGMControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN;
	}
	//SEの最大値（ボタンの最大移動量）
	if (SEControlButtonPos.x > VOLUME_CONTROL_BUTTON_MAX)
	{
		SEControlButtonPos.x = VOLUME_CONTROL_BUTTON_MAX;
	}
	else if (SEControlButtonPos.x < VOLUME_CONTROL_BUTTON_MIN)
	{
		SEControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN;
	}

}

void CSceneConfig::SoundUpdate()
{
	//ミュート
	SoundMute();
	//音量調整(スクロールバー)
	static bool scrollBGMFlg = false;
	DragVolumeButton(BGMControlButtonPos, BUTTON_BGM_CONTROL, scrollBGMFlg);
	static bool scrollSEFlg = false;
	DragVolumeButton(SEControlButtonPos, BUTTON_SE_CONTROL, scrollSEFlg);
	VolumeAdjustment();
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
		buttonSelect = 1;
	}
	if (buttonSelect == 1)
	{
		buttonScale = scaleController.ScaleControll(buttonScale,scaleMax,scaleMini,scaleSpeed);
		//SceneGameMenu
		if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))&& !gamePlayFlg)
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneConfig::Release();
		}
		//SceneGame
		else if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE)) && gamePlayFlg)
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
	scaleController.ScaleRender(&buttonTexture, buttonPosX,buttonPosY, buttonScale);

	//サウンド関係
	//BGM
	volumeBarTex.Render(VOLUME_BAR_POS_X, BGM_BAR_POS_Y);
	oysterOpenTex.Render(OPEN_OYSTER_POS_X, BGM_OPEN_OYSTER_POS_Y);
	oysterCloseBottomTex.Render(CLOSE_OYSTER_POS_X, BGM_CLOSE_OYSTER_BOTTOM_POS_Y);
	volumeControlButton.Render(BGMControlButtonPos.x, BGMControlButtonPos.y);
	oysterCloseTopTex.Render(CLOSE_OYSTER_POS_X, BGM_CLOSE_OYSTER_TOP_POS_Y);
	//SE
	volumeBarTex.Render(VOLUME_BAR_POS_X, SE_BAR_POS_Y);
	oysterOpenTex.Render(OPEN_OYSTER_POS_X, SE_OPEN_OYSTER_POS_Y);
	oysterCloseBottomTex.Render(CLOSE_OYSTER_POS_X, SE_CLOSE_OYSTER_BOTTOM_POS_Y);
	volumeControlButton.Render(SEControlButtonPos.x, SEControlButtonPos.y);
	oysterCloseTopTex.Render(CLOSE_OYSTER_POS_X, SE_CLOSE_OYSTER_TOP_POS_Y);

	//ミュート
	muteTexBGM.Render(MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y);
	muteTexSE.Render(MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y);
	CGraphicsUtilities::RenderString(0, 0, "%f", BGMControlButtonPos.x);

}

void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
	muteTexBGM.Release();
	muteTexSE.Release();
	volumeBarTex.Release();
	volumeControlButton.Release();
}