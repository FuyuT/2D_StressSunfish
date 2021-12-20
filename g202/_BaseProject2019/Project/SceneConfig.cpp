#include "SceneConfig.h"

CSceneConfig::CSceneConfig():
	BGMControlFlg(false),
	SEControlFlg(false)
{
}
CSceneConfig::~CSceneConfig()
{
	Release();
}

//ロード
bool CSceneConfig::Load()
{
	//スクロールバーの割合
	scrollBarLength = VOLUME_CONTROL_BUTTON_MAX - VOLUME_CONTROL_BUTTON_MIN;

	if (!backGroundTex.Load("Title.png"))return false;
	if (!scaneTextImage.Load("PopUpOption.png"))return false;

	//SceneGameMenuの時とSceneGameuの時で読込みを変更
	if (!gamePlayFlg)
		buttonReturnTexture.Load("ButtonMenu.png");
	else if (gamePlayFlg)
		buttonReturnTexture.Load("ButtonReturnGame.png");

	if (!soundMuteTex.Load("UI\\SoundNoMute.png"))return false;
	if (!soundNoMuteTex.Load("UI\\SoundMute.png"))return false;


	if (!volumeBarTex.Load("UI\\ScrollBar.png"))return false;
	if (!volumeControlButton.Load("UI\\PearlButton.png"))return false;
	if (!oysterCloseBottomTex.Load("UI\\PearlOysterCloseBottom.png"))return false;
	if (!oysterCloseTopTex.Load("UI\\PearlOysterCloseTop.png"))return false;
	if (!oysterOpenTex.Load("UI\\PearlOysterOpen.png"))return false;
	
	if (!SETextTex.Load("UI\\SE.png"))return false;
	if (!BGMTextTex.Load("UI\\BGM.png"))return false;
	if (!muteTextTex.Load("UI\\MUTE.png"))return false;
	if (!spaceSelectTex.Load("UI\\SpaceSelect.png"))return false;
	return true;
}

//初期化
void CSceneConfig::Initialize()
{
	cSound->GetVolumeBGM();
	BGMControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN + (cSound->GetVolumeBGM() * scrollBarLength);
	BGMControlButtonPos.y = BGM_CONTROL_BUTTON_POS_Y;
	SEControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN + (cSound->GetVolumeSE() * scrollBarLength);
	SEControlButtonPos.y = SE_CONTROL_BUTTON_POS_Y;

	buttonSelect = BUTTON_RETURN;
}

//更新
void CSceneConfig::SoundMute()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(BUTTON_MUTE_BGM).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound->GetMuteBGM())
		{
			cSound->SetMute(SOUND_BGM);
		}
		else
		{
			cSound->CancelMute(SOUND_BGM);
		}
	}
	else if (GetRect(BUTTON_MUTE_SE).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (!cSound->GetMuteSE())
		{
			cSound->SetMute(SOUND_SE);
		}
		else
		{
			cSound->CancelMute(SOUND_SE);
		}
	}
}

void CSceneConfig::DragButton(Vector2& pos, const int buttonNo, bool& scrollFlg, const int texHalfLength)
{
	//マウスでアイコンをドラッグして音量調節する機能
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	//static bool controlBGMFlg = false;
	if (GetRect(buttonNo).CollisionPoint(mousePosX, mousePosY) && g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		scrollFlg = true;
	}
	if(scrollFlg && g_pInput->IsMouseKeyPull(MOFMOUSE_LBUTTON))
	{
		scrollFlg = false;
	}

	//移動
	if (scrollFlg)
	{
		pos.x = mousePosX - texHalfLength;
	}
	//ボタンの最大移動量
	if (pos.x > VOLUME_CONTROL_BUTTON_MAX)
	{
		pos.x = VOLUME_CONTROL_BUTTON_MAX;
	}
	else if (pos.x < VOLUME_CONTROL_BUTTON_MIN)
	{
		pos.x = VOLUME_CONTROL_BUTTON_MIN;
	}
}

void CSceneConfig::SelectButton()
{
	//マウスで選択
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = BUTTON_RETURN;
	}
	else if (GetRect(BUTTON_SE_CONTROL).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = BUTTON_SE_CONTROL;
	}
	else if (GetRect(BUTTON_MUTE_SE).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = BUTTON_MUTE_SE;
	}
	else if (GetRect(BUTTON_BGM_CONTROL).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = BUTTON_BGM_CONTROL;
	}
	else if (GetRect(BUTTON_MUTE_BGM).CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = BUTTON_MUTE_BGM;
	}

	//キーで選択
	switch (buttonSelect)
	{
	case BUTTON_RETURN:
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = BUTTON_SE_CONTROL;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			buttonSelect = BUTTON_MUTE_SE;
		}
		break;
	case BUTTON_SE_CONTROL:
		//SEの音量変更選択
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (SEControlFlg)
			{
				SEControlFlg = false;
			}
			else
			{
				SEControlFlg = true;
			}
		}
		if (SEControlFlg)return;

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			buttonSelect = BUTTON_MUTE_SE;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = BUTTON_BGM_CONTROL;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = BUTTON_RETURN;
		}

		break;
	case BUTTON_MUTE_SE:
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = BUTTON_MUTE_BGM;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = BUTTON_SE_CONTROL;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = BUTTON_RETURN;
		}
		break;
	case BUTTON_BGM_CONTROL:
		//BGMの音量変更選択
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (BGMControlFlg)
			{
				BGMControlFlg = false;
			}
			else
			{
				BGMControlFlg = true;
			}
		}
		if (BGMControlFlg) return;

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			buttonSelect = BUTTON_MUTE_BGM;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = BUTTON_SE_CONTROL;
		}
		
		break;
	case BUTTON_MUTE_BGM:
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = BUTTON_BGM_CONTROL;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = BUTTON_MUTE_SE;
		}
		break;
	default:
		break;
	}

}

void CSceneConfig::ButtonUpdate()
{
	//ボタンの選択
	SelectButton();
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	switch (buttonSelect)
	{
	case BUTTON_RETURN:			//ボタン　メニューに戻る
		buttonReturnScale = scaleController.ScaleControll(buttonReturnScale, scaleMax, scaleMini, scaleSpeed);
		//SceneGameMenu
		if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(BUTTON_RETURN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE)) && !gamePlayFlg)
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

		//大きさの初期化
		buttonSEControlScale = scaleMini;
		buttonMuteSEScale = scaleMini;
		buttonBGMControlScale = scaleMini;
		buttonMuteBGMScale = scaleMini;

		break;
	case BUTTON_SE_CONTROL:		//ボタン　SE
		buttonSEControlScale = scaleController.ScaleControll(buttonSEControlScale, volumeButtonScaleMax, scaleMini, volumeButtonScaleSpeed);

		//大きさの初期化
		buttonReturnScale = scaleMini;
		buttonMuteSEScale = scaleMini;
		buttonBGMControlScale = scaleMini;
		buttonMuteBGMScale = scaleMini;
		break;
	case BUTTON_MUTE_SE:		//ボタン　SEMUTE
		buttonMuteSEScale = scaleController.ScaleControll(buttonMuteSEScale, scaleMax, scaleMini, scaleSpeed);

		//大きさの初期化
		buttonReturnScale = scaleMini;
		buttonSEControlScale = scaleMini;
		buttonBGMControlScale = scaleMini;
		buttonMuteBGMScale = scaleMini;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (cSound->GetMuteSE())
			{
				cSound->CancelMute(SOUND_SE);
			}
			else
			{
				cSound->SetMute(SOUND_SE);
			}
		}
		break;
	case BUTTON_BGM_CONTROL:	//ボタン　BGM
		buttonBGMControlScale = scaleController.ScaleControll(buttonBGMControlScale, volumeButtonScaleMax, scaleMini, volumeButtonScaleSpeed);

		//大きさの初期化
		buttonReturnScale = scaleMini;
		buttonSEControlScale = scaleMini;
		buttonMuteSEScale = scaleMini;
		buttonMuteBGMScale = scaleMini;


		break;
	case BUTTON_MUTE_BGM:		//ボタン　BGMMUTE
		buttonMuteBGMScale = scaleController.ScaleControll(buttonMuteBGMScale, scaleMax, scaleMini, scaleSpeed);

		//大きさの初期化
		buttonReturnScale = scaleMini;
		buttonSEControlScale = scaleMini;
		buttonMuteSEScale = scaleMini;
		buttonBGMControlScale = scaleMini;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (cSound->GetMuteBGM())
			{
				cSound->CancelMute(SOUND_BGM);
			}
			else
			{
				cSound->SetMute(SOUND_BGM);
			}
		}
		break;
	default:
		break;
	}
}

void CSceneConfig::VolumeAdjustment(const Vector2 pos, const int soundNo)
{
	//スクロールバーとボタンの位置の割合によって、音量を変更する
	float vol = (pos.x - VOLUME_CONTROL_BUTTON_MIN) / scrollBarLength;
	if (vol > 1)
	{
		vol = 1;
	}
	else if (vol < 0)
	{
		vol = 0;
	}
	switch (soundNo)
	{
	case SOUND_BGM:
		cSound->SetVolumeBGM(vol);
		if (cSound->GetMuteBGM())return;
		cSound->ChangeVolume(SOUND_BGM);
		break;
	case SOUND_SE:
		cSound->SetVolumeSE(vol);
		if (cSound->GetMuteSE())return;
		cSound->ChangeVolume(SOUND_SE);
		break;
	default:
		break;
	}
}

void CSceneConfig::SoundUpdate()
{
	//音量調整
	//スクロールバー
	static bool scrollBGMFlg = false;
	DragButton(BGMControlButtonPos, BUTTON_BGM_CONTROL, scrollBGMFlg, volumeControlButton.GetWidth() * 0.5);
	static bool scrollSEFlg = false;
	DragButton(SEControlButtonPos, BUTTON_SE_CONTROL, scrollSEFlg, volumeControlButton.GetWidth() * 0.5);
	//矢印キー
	if (BGMControlFlg)
	{
		if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			BGMControlButtonPos.x += VOLUME_CONTROL_SPEED;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_LEFT))
		{
			BGMControlButtonPos.x -= VOLUME_CONTROL_SPEED;
		}
	}
	else if (SEControlFlg)
	{
		if (g_pInput->IsKeyHold(MOFKEY_RIGHT))
		{
			SEControlButtonPos.x += VOLUME_CONTROL_SPEED;
		}
		else if (g_pInput->IsKeyHold(MOFKEY_LEFT))
		{
			SEControlButtonPos.x -= VOLUME_CONTROL_SPEED;
		}

	}
	//音量変更
	SoundMute();
	VolumeAdjustment(BGMControlButtonPos, SOUND_BGM);
	VolumeAdjustment(SEControlButtonPos,SOUND_SE);
}

void CSceneConfig::Update()
{
	ButtonUpdate();
	SoundUpdate();
}

//描画
void CSceneConfig::Render()
{
	backGroundTex.Render(0, 0);
	scaneTextImage.Render(SCENE_TEXT_IMAGE_X, SCENE_TEXT_IMAGE_Y);
	buttonReturnTexture.Render(buttonReturnPosX, buttonReturnPosY);
	scaleController.ScaleRender(&buttonReturnTexture, buttonReturnPosX,buttonReturnPosY, buttonReturnScale);

	//テキスト
	BGMTextTex.Render(30, BGM_BAR_POS_Y);
	SETextTex.Render(30, SE_BAR_POS_Y);
	muteTextTex.Render(250, 800);
	spaceSelectTex.Render(830, 200);

	//サウンド関係
	//BGM
	volumeBarTex.Render(VOLUME_BAR_POS_X, BGM_BAR_POS_Y);
	oysterOpenTex.Render(OPEN_OYSTER_POS_X, BGM_OPEN_OYSTER_POS_Y);
	oysterCloseBottomTex.Render(CLOSE_OYSTER_POS_X, BGM_CLOSE_OYSTER_BOTTOM_POS_Y);
	scaleController.ScaleRender(&volumeControlButton, BGMControlButtonPos.x, BGMControlButtonPos.y, buttonBGMControlScale);
	oysterCloseTopTex.Render(CLOSE_OYSTER_POS_X, BGM_CLOSE_OYSTER_TOP_POS_Y);
	//SE
	volumeBarTex.Render(VOLUME_BAR_POS_X, SE_BAR_POS_Y);
	oysterOpenTex.Render(OPEN_OYSTER_POS_X, SE_OPEN_OYSTER_POS_Y);
	oysterCloseBottomTex.Render(CLOSE_OYSTER_POS_X, SE_CLOSE_OYSTER_BOTTOM_POS_Y);
	scaleController.ScaleRender(&volumeControlButton,SEControlButtonPos.x, SEControlButtonPos.y,buttonSEControlScale);
	oysterCloseTopTex.Render(CLOSE_OYSTER_POS_X, SE_CLOSE_OYSTER_TOP_POS_Y);

	//ミュート
	if (cSound->GetMuteBGM())
	{
		scaleController.ScaleRender(&soundNoMuteTex, MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y, buttonMuteBGMScale);
	}
	else
	{
		scaleController.ScaleRender(&soundMuteTex,MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y, buttonMuteBGMScale);
	}
	if (cSound->GetMuteSE())
	{
		scaleController.ScaleRender(&soundNoMuteTex, MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y, buttonMuteSEScale);
	}
	else
	{
		scaleController.ScaleRender(&soundMuteTex,MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y,buttonMuteSEScale);
	}

	//デバッグ　位置決め用
	//Vector2 mousePos;
	//g_pInput->GetMousePos(mousePos);
	//CGraphicsUtilities::RenderString(0, 0, "%f", mousePos.x);
	//CGraphicsUtilities::RenderString(0, 50, "%f", mousePos.y);

}

//解放
void CSceneConfig::Release()
{
	backGroundTex.Release();
	scaneTextImage.Release();
	buttonReturnTexture.Release();
	soundMuteTex.Release();
	soundNoMuteTex.Release();
	volumeBarTex.Release();
	volumeControlButton.Release();
	oysterCloseBottomTex.Release();
	oysterCloseTopTex.Release();
	oysterOpenTex.Release();
	SETextTex.Release();
	BGMTextTex.Release();
	muteTextTex.Release();
	spaceSelectTex.Release();

}