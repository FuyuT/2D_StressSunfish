#include "SceneConfig.h"

CSceneConfig::CSceneConfig()
{
}
CSceneConfig::~CSceneConfig()
{
	Release();
}

//���[�h
bool CSceneConfig::Load()
{
	//�X�N���[���o�[�̊���
	scrollBarLength = VOLUME_CONTROL_BUTTON_MAX - VOLUME_CONTROL_BUTTON_MIN;

	if (!backGroundTex.Load("Title.png"))return false;

	//SceneGameMenu�̎���SceneGameu�̎��œǍ��݂�ύX
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

//������
void CSceneConfig::Initialize()
{
	cSound->GetVolumeBGM();
	BGMControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN + (cSound->GetVolumeBGM() * scrollBarLength);
	BGMControlButtonPos.y = BGM_CONTROL_BUTTON_POS_Y;
	SEControlButtonPos.x = VOLUME_CONTROL_BUTTON_MIN + (cSound->GetVolumeSE() * scrollBarLength);
	SEControlButtonPos.y = SE_CONTROL_BUTTON_POS_Y;

	buttonSelect = 1;
}

//�X�V
void CSceneConfig::SoundMute()//todo:�~���[�g����߂������̉��ǂ����邩(data�ŕۑ����ȂƎv���Ă�j
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
		if (!cSound->GetMuteBGM())
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
	//�}�E�X�ŃA�C�R�����h���b�O���ĉ��ʒ��߂���@�\
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

	//�ړ�
	if (scrollFlg)
	{
		pos.x = mousePosX - texHalfLength;
	}
	//�{�^���̍ő�ړ���
	if (pos.x > VOLUME_CONTROL_BUTTON_MAX)
	{
		pos.x = VOLUME_CONTROL_BUTTON_MAX;
	}
	else if (pos.x < VOLUME_CONTROL_BUTTON_MIN)
	{
		pos.x = VOLUME_CONTROL_BUTTON_MIN;
	}
}

void CSceneConfig::VolumeAdjustment(const Vector2 pos, const int soundNo)
{	
	//�X�N���[���o�[�ƃ{�^���̈ʒu�̊����ɂ���āA���ʂ�ύX����
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
	//���ʒ���(�X�N���[���o�[)
	static bool scrollBGMFlg = false;
	DragButton(BGMControlButtonPos, BUTTON_BGM_CONTROL, scrollBGMFlg, volumeControlButton.GetWidth() * 0.5);
	static bool scrollSEFlg = false;
	DragButton(SEControlButtonPos, BUTTON_SE_CONTROL, scrollSEFlg, volumeControlButton.GetWidth() * 0.5);
	//���ʕύX
	SoundMute();
	VolumeAdjustment(BGMControlButtonPos, SOUND_BGM);
	VolumeAdjustment(SEControlButtonPos,SOUND_SE);
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

//�`��
void CSceneConfig::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "�ݒ���");
	buttonTexture.Render(buttonPosX, buttonPosY);
	scaleController.ScaleRender(&buttonTexture, buttonPosX,buttonPosY, buttonScale);

	//�T�E���h�֌W
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

	//�~���[�g
	muteTexBGM.Render(MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y);
	muteTexSE.Render(MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y);
	CGraphicsUtilities::RenderString(0, 0, "%f", BGMControlButtonPos.x);

}

//���
void CSceneConfig::Release()
{
	backGroundTex.Release();
	buttonTexture.Release();
	muteTexBGM.Release();
	muteTexSE.Release();
	volumeBarTex.Release();
	volumeControlButton.Release();
}