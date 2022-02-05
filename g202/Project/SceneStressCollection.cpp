#include "SceneStressCollection.h"
#include "CheckCauseOfDeathWindow.h"

CPopUpWindowBase* nowPopUpStress = NULL;

CSceneStressCollection::CSceneStressCollection():
	hyperthermiaFlg(false),
	lowerBodyTemperatureFlg(false),
	starvationFlg(false),
	cloggedThroatFlg(false),
	obesityFlg(false),
	impactFlg(false),
	parasiteFlg(false),
	jumpFlg(false),
	bubbleFlg(false),
	turtleFlg(false),
	waterFlowFlg(false),
	shoalFishFlg(false)
{

}
CSceneStressCollection::~CSceneStressCollection()
{
	Release();
}

void CSceneStressCollection::PlayBGM()
{
	cSound->BGMStop();
	cSound->Play(SOUND_COLLECTION_BGM);
}

void CSceneStressCollection::Initialize()
{
	//�w�i�ǂݍ���
	backGroundTex.Load("BackGround_CaseOfDeath.png");

	//�X�g���X�t���O�ǂݍ���
	LoadStressFlg();

	//�t�H���g
	font.Load(fontAdd, fontName);
	font.Create(64, fontName);


	page = 1;
	//�����e�N�X�`���ǂݍ���
	if (hyperthermiaFlg)
		hyperthermiaTexture.Load("�}���{�E �̉��㏸icon.png");
	else
		hyperthermiaTexture.Load("�}���{�E �̉��㏸icon_�e.png");
	if (lowerBodyTemperatureFlg)
		lowerBodyTemperatureTexture.Load("�}���{�E �̉��ቺicon.png");
	else
		lowerBodyTemperatureTexture.Load("�}���{�E �̉��ቺicon_�e.png");
	if (starvationFlg)
		starvationTexture.Load("�}���{�E ��icon.png");
	else
		starvationTexture.Load("�}���{�E ��icon_�e.png");
	if (cloggedThroatFlg)
		cloggedThroatexture.Load("�}���{�E�@�A�܂�icon.png");
	else
		cloggedThroatexture.Load("�}���{�E�@�A�܂�icon_�e.png");

	if (obesityFlg)
		obesityTexture.Load("�얞�}���{�E2icon.png");
	else
		obesityTexture.Load("�얞�}���{�E2icon_�e.png");
	if (impactFlg)
		impactTexture.Load("��Q���ɂ������Ď��Sicon.png");
	else
		impactTexture.Load("��Q���ɂ������Ď��Sicon_�e.png");
	if (parasiteFlg)
		parasiteIconTexture.Load("�}���{�E�񐶒��X�g���Xicon.png");
	else
		parasiteIconTexture.Load("�}���{�E�񐶒��X�g���Xicon_�e.png");
	if (jumpFlg)
		jumpTexture.Load("���ʂɂ���������ꎀ�S �C�Ȃ�icon.png");
	else
		jumpTexture.Load("���ʂɂ���������ꎀ�S �C�Ȃ�icon_�e.png");
	
	if (bubbleFlg)
		bubbleTexture.Load("�}���{�E�Aicon.png");
	else 
		bubbleTexture.Load("�}���{�E�Aicon_�e.png");

	if (turtleFlg)
		turtleTexture.Load("�}���{�E�T�\��icon.png");
	else
		turtleTexture.Load("�}���{�E�T�\��icon_�e.png");

	if (waterFlowFlg)
		waterFlowTexture.Load("������icon.png");
	else
		waterFlowTexture.Load("������icon_�e.png");
	if (shoalFishFlg)
		shoalFishTexture.Load("�}���{�E�@���Q�Փˎ�icon.png");
	else
		shoalFishTexture.Load("�}���{�E�@���Q�Փˎ�icon_�e.png");

	//�{�^���e�N�X�`���ǂݍ���
	menuButtonTexture.Load("ButtonMenu.png");
	rightButtonTexture.Load("ButtonRight.png");
	leftButtonTexture.Load("ButtonLeft.png");

	//�|�b�v�A�b�v������
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
	nowPopUpStress->SetSoundManager(*cSound);
	PlayBGM();

	//�I��������
	if (hyperthermiaFlg)
		buttonSelect = 1;
	else if (lowerBodyTemperatureFlg)
		buttonSelect = 2;
	else if (starvationFlg)
		buttonSelect = 3;
	else if (cloggedThroatFlg)
		buttonSelect = 4;
	else
		buttonSelect = 0;

	bubbleFade.Load();
	bubbleFade.Initialize();
}
void CSceneStressCollection::Update()
{
	//�t�F�[�h����
	bubbleFade.Update();
	bubbleFade.FadeIn();
	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		//�V�[���̑J��
		endFlg = true;
		nextScene = nextSceneTemp;
		CSceneStressCollection::Release();
		return;
	}

	//�|�b�v�A�b�v����
	if (popUpFlg)
	{		
		if (nowPopUpStress->IsEnd())
		{
			nowPopUpStress->Release();
			popUpFlg = false;
		}
		nowPopUpStress->Update();
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (!popUpFlg)
	{
		MouseCollision(mousePosX, mousePosY);
		if (page == 1)
		{
			if (buttonSelect == 0)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;					
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				hyperthermiaScale = scaleController.ScaleControll(hyperthermiaScale, scaleMax, scaleMini, scaleSpeed);
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else
					{
						page = 2;
						if (obesityFlg)
							buttonSelect = 1;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (jumpFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�̉��㏸�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleController.ScaleControll(lowerBodyTemperatureScale, scaleMax, scaleMini, scaleSpeed);
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (starvationFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (starvationFlg)
						buttonSelect = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�̉��ቺ�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Frozen);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleController.ScaleControll(starvationScale, scaleMax, scaleMini, scaleSpeed);
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else
					{
						page = 2;
						if (obesityFlg)
							buttonSelect = 1;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (jumpFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�쎀�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Starvation);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleController.ScaleControll(cloggedThroatScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (starvationFlg)
						buttonSelect = 3;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (parasiteFlg)
					buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�A�l�܂�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
					nowPopUpStress->Initialize();
				}
			}

			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
				if (obesityFlg)
					buttonSelect = 1;
				else if (parasiteFlg)
					buttonSelect = 3;
				else if (impactFlg)
					buttonSelect = 2;
				else if (jumpFlg)
					buttonSelect = 4;
				else
					buttonSelect = 0;
				cSound->Play(SOUND_BUTTON_PUSH);
			}
		}
		else if (page == 2)
		{
			if (buttonSelect == 0)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				obesityScale = scaleController.ScaleControll(obesityScale, scaleMax, scaleMini, scaleSpeed);;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (impactFlg)
						buttonSelect = 2;
					else if (jumpFlg)
						buttonSelect = 4;
					else
					{
						page = 3;
						if (bubbleFlg)
							buttonSelect = 1;
						else if (waterFlowFlg)
							buttonSelect = 3;
						else if (turtleFlg)
							buttonSelect = 2;
						else if (shoalFishFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (starvationFlg)
						buttonSelect = 2;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (starvationFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�얞�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Obesity);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				obesityScale = scaleMini;
				impactScale = scaleController.ScaleControll(impactScale, scaleMax, scaleMini, scaleSpeed);
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jumpFlg)
						buttonSelect = 4;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (starvationFlg)
							buttonSelect = 2;
						else if (cloggedThroatFlg)
							buttonSelect = 4;
						else if (hyperthermiaFlg)
							buttonSelect = 1;
						else if (starvationFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (bubbleFlg)
						buttonSelect = 1;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else if (turtleFlg)
						buttonSelect = 2;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:��Q���ƏՓ˂̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleController.ScaleControll(parasiteScale, scaleMax, scaleMini, scaleSpeed);
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jumpFlg)
						buttonSelect = 4;
					else if (impactFlg)
						buttonSelect = 2;
					else
					{
						page = 3;
						if (waterFlowFlg)
							buttonSelect = 3;
						else if (shoalFishFlg)
							buttonSelect = 4;
						else if (bubbleFlg)
							buttonSelect = 1;
						else if (turtleFlg)
							buttonSelect = 2;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (starvationFlg)
						buttonSelect = 2;
					else if (starvationFlg)
						buttonSelect = 3;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�񐶒��̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Parasite);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleController.ScaleControll(jumpScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (impactFlg)
						buttonSelect = 2;
					else if (obesityFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (parasiteFlg)
						buttonSelect = 3;
					else if (obesityFlg)
						buttonSelect = 1;
					else
					{
						page = 1;
						if (cloggedThroatFlg)
							buttonSelect = 4;
						else if (starvationFlg)
							buttonSelect = 2;
						else if (starvationFlg)
							buttonSelect = 3;
						else if (hyperthermiaFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�W�����v�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Jump);
					nowPopUpStress->Initialize();
				}
			}



			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)&& ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				if (hyperthermiaFlg)
					buttonSelect = 1;
				else if (starvationFlg)
					buttonSelect = 3;
				else if (starvationFlg)
					buttonSelect = 2;
				else if (cloggedThroatFlg)
					buttonSelect = 4;
				else
					buttonSelect = 0;
				page = 1;
			}
			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				if (bubbleFlg)
					buttonSelect = 1;
				else if (waterFlowFlg)
					buttonSelect = 3;
				else if (turtleFlg)
					buttonSelect = 2;
				else if (shoalFishFlg)
					buttonSelect = 4;
				else
					buttonSelect = 0;
				page = 3;
			}
		}
		else if (page == 3)
		{
			if (buttonSelect == 0)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				bubbleScale = scaleController.ScaleControll(bubbleScale, scaleMax, scaleMini, scaleSpeed);;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (turtleFlg)
						buttonSelect = 2;
					else if (shoalFishFlg)
						buttonSelect = 4;
					
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (impactFlg)
						buttonSelect = 2;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�A�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Bubble);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleController.ScaleControll(turtleScalse, scaleMax, scaleMini, scaleSpeed);
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (shoalFishFlg)
						buttonSelect = 4;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (impactFlg)
							buttonSelect = 2;
						else if (jumpFlg)
							buttonSelect = 4;
						else if (obesityFlg)
							buttonSelect = 1;
						else if (parasiteFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_SeaTurtle).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�E�~�K���̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleController.ScaleControll(waterFlowScale, scaleMax, scaleMini, scaleSpeed);
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (shoalFishFlg)
						buttonSelect = 4;
					else if (turtleFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (jumpFlg)
						buttonSelect = 4;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (obesityFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�����̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleController.ScaleControll(shoalFishScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (turtleFlg)
						buttonSelect = 2;
					else if (bubbleFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (bubbleFlg)
						buttonSelect = 1;
					else
					{
						page = 2;
						if (jumpFlg)
							buttonSelect = 4;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (obesityFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ShoalFish).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�W�����v�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_ShoalFish);
					nowPopUpStress->Initialize();
				}
			}

			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				if (obesityFlg)
					buttonSelect = 1;
				else if (parasiteFlg)
					buttonSelect = 3;
				else if (impactFlg)
					buttonSelect = 2;
				else if (jumpFlg)
					buttonSelect = 4;
				else
					buttonSelect = 0;
				page = 2;
			}
		}
	}
}
void CSceneStressCollection::Render()
{
	backGroundTex.Render(0, 0);
	font.RenderString(textPosX,textPosY, MOF_XRGB(0, 0, 0), "�X�g���X�ꗗ");
	if (page == 1)
	{
		//1�y�[�W�ڂɕ\��
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 31, leftAndRightButtonPosY - 2, MOF_XRGB(0, 0, 0), "1/3");

		scaleController.ScaleRender(&hyperthermiaTexture, iconFirstRowPosX, iconOneLinePosY, hyperthermiaScale);
		scaleController.ScaleRender(&lowerBodyTemperatureTexture, iconSecondRowPosX, iconOneLinePosY, lowerBodyTemperatureScale);
		scaleController.ScaleRender(&starvationTexture, iconFirstRowPosX, iconTwoLinePosY, starvationScale);
		scaleController.ScaleRender(&cloggedThroatexture, iconSecondRowPosX, iconTwoLinePosY, cloggedThroatScale);
	}
	if (page == 2)
	{
		//2�y�[�W�ڂɕ\��
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 10, leftAndRightButtonPosY - 2, MOF_XRGB(0, 0, 0), "2/3");

		scaleController.ScaleRender(&obesityTexture, iconFirstRowPosX, iconOneLinePosY, obesityScale);
		scaleController.ScaleRender(&impactTexture, iconSecondRowPosX, iconOneLinePosY, impactScale);
		scaleController.ScaleRender(&parasiteIconTexture, iconFirstRowPosX, iconTwoLinePosY, parasiteScale);
		scaleController.ScaleRender(&jumpTexture, iconSecondRowPosX, iconTwoLinePosY +10, jumpScale);
	}
	if (page == 3)
	{
		//3�y�[�W�ڂɕ\��
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 9, leftAndRightButtonPosY - 2, MOF_XRGB(0, 0, 0), "3/3");

		scaleController.ScaleRender(&bubbleTexture, iconFirstRowPosX, iconOneLinePosY, bubbleScale);
		scaleController.ScaleRender(&turtleTexture, iconSecondRowPosX, iconOneLinePosY, turtleScalse);
		scaleController.ScaleRender(&waterFlowTexture, iconFirstRowPosX, iconTwoLinePosY+10, waterFlowScale);
		scaleController.ScaleRender(&shoalFishTexture,iconSecondRowPosX,iconTwoLinePosY+20,shoalFishScale);
	}

	scaleController.ScaleRender(&menuButtonTexture , menuButtonPosX,menuButtonPosY,menuButtonScale);
	
	if(page != 1)
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	if (page !=3)
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);

	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}

	bubbleFade.Render();
}
void CSceneStressCollection::Release()
{
	backGroundTex.Release();
	hyperthermiaTexture.Release();
	lowerBodyTemperatureTexture.Release();
	starvationTexture.Release();
	cloggedThroatexture.Release();
	obesityTexture.Release();
	impactTexture.Release();
	parasiteIconTexture.Release();
	jumpTexture.Release();
	bubbleTexture.Release();
	turtleTexture.Release();
	waterFlowTexture.Release();
	shoalFishTexture.Release();

	menuButtonTexture.Release();
	if (nowPopUpStress != NULL)
	{
		nowPopUpStress->Release();
		if (nowPopUpStress)
		{
			delete nowPopUpStress;
			nowPopUpStress = NULL;
		}
	}
	bubbleFade.Release();
}

CRectangle CSceneStressCollection::GetRect(int i)
{
	//����:�̉��㏸�N���b�N��
	if (i == CAUSE_Hyperthermia && hyperthermiaFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + hyperthermiaTexture.GetWidth(), iconOneLinePosY + hyperthermiaTexture.GetHeight());
	//����:�̉��ቺ�N���b�N��
	if (i == CAUSE_Frozen && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureTexture.GetHeight());
	//����:�쎀�N���b�N��
	if (i == CAUSE_Starvation && starvationFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + starvationTexture.GetWidth(), iconTwoLinePosY + starvationTexture.GetHeight());
	//����:�A�Ɏh����N���b�N��
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + cloggedThroatexture.GetWidth(), iconTwoLinePosY + cloggedThroatexture.GetHeight());

	//����:�얞�N���b�N��
	if (i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + obesityTexture.GetWidth(), iconOneLinePosY + obesityTexture.GetHeight());
	//����:��Q���ƏՓ˃N���b�N��
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + impactTexture.GetWidth(), iconOneLinePosY + impactTexture.GetHeight());
	//����:�񐶒��N���b�N��
	if (i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconTwoLinePosY + parasiteIconTexture.GetHeight());
	//����:�W�����v�N���b�N��
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + jumpTexture.GetWidth(), iconTwoLinePosY + jumpTexture.GetHeight());

	//����:�A�N���b�N��
	if (i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + bubbleTexture.GetWidth(), iconOneLinePosY + bubbleTexture.GetHeight());
	//����:�E�~�K���ڐG�N���b�N��
	if (i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + turtleTexture.GetWidth(), iconOneLinePosY + turtleTexture.GetHeight());
	//����:����
	if (i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + waterFlowTexture.GetWidth(), iconTwoLinePosY + waterFlowTexture.GetHeight());
	//����:���Q
	if(i == CAUSE_ShoalFish && shoalFishFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + shoalFishTexture.GetWidth(), iconTwoLinePosY + shoalFishTexture.GetHeight());
	
	else
	{
		return CRectangle(0, 0, 0, 0);
	}
}

void CSceneStressCollection::MouseCollision(int posX, int posY)
{
	if (ButtonGetRect(0).CollisionPoint(posX, posY) && buttonSelect != 0)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 0;
	}
	if (page == 1)
	{
		if (GetRect(CAUSE_Hyperthermia).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_Frozen).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_Starvation).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_ChokeOnShell).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
	else if (page == 2)
	{
		if (GetRect(CAUSE_Obesity).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_Obstacle).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_Parasite).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_Jump).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
	else if (page == 3)
	{
		if (GetRect(CAUSE_Bubble).CollisionPoint(posX, posY) &&buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_SeaTurtle).CollisionPoint(posX, posY)&&buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_WaterFlow).CollisionPoint(posX, posY)&& buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_ShoalFish).CollisionPoint(posX, posY)&& buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
}

CRectangle CSceneStressCollection::ButtonGetRect(int i)
{
	if (i == 0)
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(leftButtonPosX, leftAndRightButtonPosY, leftButtonPosX + leftButtonTexture.GetWidth(), leftAndRightButtonPosY + leftButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(rightButtonPosX, leftAndRightButtonPosY, rightButtonPosX + rightButtonTexture.GetWidth(), leftAndRightButtonPosY + rightButtonTexture.GetHeight());
}

bool CSceneStressCollection::GetStress(int i)
{

	//�M���ǃQ�b�g
	if (i == CAUSE_Hyperthermia && !hyperthermiaFlg)
	{
		hyperthermiaFlg = true;
		SaveStressFlg();
		return true;
	}
	//�̉��ቺ�Q�b�g
	if (i == CAUSE_Frozen && !lowerBodyTemperatureFlg)
	{
		lowerBodyTemperatureFlg = true;
		SaveStressFlg();
		return true;
	}
	//�쎀
	if (i == CAUSE_Starvation && !starvationFlg)
	{
		starvationFlg = true;
		SaveStressFlg();
		return true;
	}
	//�A�l�܂�
	if (i == CAUSE_ChokeOnShell && !cloggedThroatFlg)
	{
		cloggedThroatFlg = true;
		SaveStressFlg();
		return true;
	}
	//�얞
	if (i == CAUSE_Obesity && !obesityFlg)
	{
		obesityFlg = true;
		SaveStressFlg();
		return true;
	}
	//�Փ�
	if (i == CAUSE_Obstacle && !impactFlg)
	{
		impactFlg = true;
		SaveStressFlg();
		return true;
	}
	//�񐶒�
	if (i == CAUSE_Parasite && !parasiteFlg)
	{
		parasiteFlg = true;
		SaveStressFlg();
		return true;
	}
	//�W�����v
	if (i == CAUSE_Jump && !jumpFlg)
	{
		jumpFlg = true;
		SaveStressFlg();
		return true;
	}
	//�A
	if (i == CAUSE_Bubble && !bubbleFlg)
	{
		bubbleFlg = true;
		SaveStressFlg();
		return true;
	}
	//�E�~�K��
	if (i == CAUSE_SeaTurtle && !turtleFlg)
	{
		turtleFlg = true;
		SaveStressFlg();
		return true;
	}
	//����
	if (i == CAUSE_WaterFlow && !waterFlowFlg)
	{
		waterFlowFlg = true;
		SaveStressFlg();
		return true;
	}
	if (i == CAUSE_ShoalFish && !shoalFishFlg)
	{
		shoalFishFlg = true;
		SaveStressFlg();
		return true;
	}
	return false;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("SaveData\\SaveStress.dat", "wb");
	if (fp)
	{
		fwrite(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fwrite(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fwrite(&starvationFlg, sizeof(bool), 1, fp);
		fwrite(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fwrite(&obesityFlg, sizeof(bool), 1, fp);
		fwrite(&impactFlg, sizeof(bool), 1, fp);
		fwrite(&parasiteFlg, sizeof(bool), 1, fp);
		fwrite(&jumpFlg, sizeof(bool), 1, fp);
		fwrite(&bubbleFlg, sizeof(bool), 1, fp);
		fwrite(&turtleFlg, sizeof(bool), 1, fp);
		fwrite(&waterFlowFlg, sizeof(bool), 1, fp);
		fwrite(&shoalFishFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}

void CSceneStressCollection::LoadStressFlg()
{
	FILE* fp = fopen("SaveData\\SaveStress.dat", "rb");
	if (fp)
	{
		fread(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fread(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fread(&starvationFlg, sizeof(bool), 1, fp);
		fread(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fread(&obesityFlg, sizeof(bool), 1, fp);
		fread(&impactFlg, sizeof(bool), 1, fp);
		fread(&parasiteFlg, sizeof(bool), 1, fp);
		fread(&jumpFlg, sizeof(bool), 1, fp);
		fread(&bubbleFlg, sizeof(bool), 1, fp);
		fread(&turtleFlg, sizeof(bool), 1, fp);
		fread(&waterFlowFlg, sizeof(bool), 1, fp);
		fread(&shoalFishFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}
