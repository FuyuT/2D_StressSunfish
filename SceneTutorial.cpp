#include "SceneTutorial.h"
#include "SceneConfig.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"

CPopUpWindowBase* nowPopUpTutorial = NULL;
//GameApp�őJ�ڂ���Ɛݒ��ʂ���Q�[���V�[���ɖ߂����ۂɃQ�[���V�[��������������邽�߁A
//�����Ő錾���A�Q�[���V�[���̏ォ��ݒ��ʂ�\������悤�ɂ���B
CSceneConfig sceneConfigT;

CSceneTutorial::CSceneTutorial():
	fBuffer(NULL),
	fBufferOffset(0),
	mShowDelay(0),
	messageEndFlg(false),
	tutorialStep(0),
	poseFlg(false)
{
}

CSceneTutorial::~CSceneTutorial()
{
}

////////////////////////////
// ���\�b�h
////////////////////////////

//�e�L�X�g�̓Ǎ���
bool CSceneTutorial::TextLoad()
{
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen("Text\\Tutorial.txt", "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);  //fp�̈ʒu���t�@�C���̏I�[��
	long fSize = ftell(fp);  //�t�@�C���̓ǂݏ����ʒu���擾�A�ʒu�ŗe�ʂ����߂�
	fseek(fp, 0, SEEK_SET);  //fp�̈ʒu���t�@�C���̐擪��
	//�t�@�C���̗e�ʕ��̃�������malloc�œ��I�Ɋm��
	fBuffer = (char*)malloc(fSize + 1);  //�I�[��\0���܂߂邽�߁A+1
	//�o�b�t�@�Ƀt�@�C����S�ēǂݍ���
	fSize = fread(fBuffer, 1, fSize, fp);
	fBuffer[fSize] = '\0';
	//�t�@�C�������
	fclose(fp);
	return true;
}

//�t�H���g�̓Ǎ���
void CSceneTutorial::FontLoad()
{
	//font�̍쐬
	font.Load(fontAdd, fontName);
	font.Create(38, fontName);
}

//���b�Z�[�W�̍X�V
void CSceneTutorial::MessageUpdate()
{
	//�����񂪏I��(���s�̎��ɉ��s������)������ASPACE�Ŏ��̐�����
	if(fBuffer[fBufferOffset] == '\n' && fBuffer[fBufferOffset + 1] == '\n')
	{
		messageEndFlg = true;
		if (g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			if (tutorialStep == TutorialStep::Task_Complete)
			{
				bubbleFade.FadeOut();
				nextSceneTemp = SCENENO_GAME;

				tutorialStep = TutorialStep::Task_End;
				//nextScene = SCENENO_GAME;
				//endFlg = true;
			}
			else if (tutorialStep != pl.GetTaskCompleteStep())
			{
				for (int n = 0; n < MESSAGE_ARRAY_BYTE; n++)
				{
					fLineBuffer[n] = NULL;
				}
				fBufferOffset++; //�e�L�X�g�𕪂��Ă�����s�͕\�������ɓ���Ȃ��̂ŁA��΂�
				messageEndFlg = false;
				//�`���[�g���A���̒i�K����i�߂� �Ō�̃^�X�N���I����Ă�����A�^�X�N��������Ԃɂ���
				if (tutorialStep == TutorialStep::Task_Action)
				{
					tutorialStep = TutorialStep::Task_Complete;
				}
				else
				{
					tutorialStep += 1;
				}
			}
		}
	}
	//������̏I�[�܂ŕ�����ǉ����Ă���
	else if (fBuffer[fBufferOffset] != '\0')
	{
		int nl = strlen(fLineBuffer);
		//���s�̏ꍇ�A�\������������s����
		if (fBuffer[fBufferOffset] == '\n')
		{
			//�s�Ԃ��~�����̂�2����s���Ă���
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl] = '\0';
			fBufferOffset++;
		}
		else
		{
			//��莞�Ԃ��ƂɈꕶ������fLineBuffer�ɂ���Ă���
			mShowDelay++;
			if (mShowDelay >= MESSAGE_DELAY_FRAME)
			{
				mShowDelay = 0;
				if (IsDBCSLeadByte(fBuffer[fBufferOffset]))			//�S�p��������
				{
					//�S�p�����̏ꍇ�Q�o�C�g���ňꕶ���ɂȂ� (�����R�[�hShift_JIS)
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
				else                                      			//���p�̏ꍇ
				{
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
			}
		}
	}
}

//���b�Z�\�W�̕`��
void CSceneTutorial::MessageRender()
{
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	font.RenderString(FIRST_MESSAGE_POS_X, FIRST_MESSAGE_POS_Y, fLineBuffer);
	if (messageEndFlg && tutorialStep == TutorialStep::Task_Complete)
	{
		font.RenderString(1000, 960, "Space�������ăQ�[�����J�n����");
	}
	else if (messageEndFlg && tutorialStep != pl.GetTaskCompleteStep())
	{
		font.RenderString(1000, 960, "Space�������Ď��ց�");
	}
	else if (messageEndFlg && tutorialStep == pl.GetTaskCompleteStep())
	{
		font.RenderString(1000, 960, "�^�X�N�����Ȃ����I");
	}
}


////////////////////////////
// ����@�\
////////////////////////////

bool CSceneTutorial::Load()
{
	if (!stg.Load())return false;
	if (!ui.Load())return false;
	if (!pl.Load())return false;
	if (!obs.Load())return false;
	if (!messageWindowImg.Load("MessageWindow.png"))return false;
	if (!TextLoad())return false;
	//�t�H���g�̓Ǎ���
	FontLoad();
	bubbleFade.Load();
	return true;
}

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
	obs.Initialize();
	fBufferOffset = 0;
	mShowDelay = 0;
	messageEndFlg = false;
	tutorialStep = TutorialStep::Task_Movement;
	pl.SetSoundManager(*cSound);
	bubbleFade.Initialize();
	sceneConfigT.SetSoundManager(*cSound);
	//�|�b�v�A�b�v
	popUpFlg = false;
	poseFlg = false;
	configFlg = false;
}

void CSceneTutorial::Update()
{
	//todo:�|�[�Y��ʕ\���ɕύX�@����Enter�Ń��j���[�ɖ߂�
	//if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	//{
	//	nextScene = SCENENO_GAMEMENU;
	//	endFlg = true;
	//}


	//�t�F�[�h����
	bubbleFade.Update();
	bubbleFade.FadeIn();

	//�ݒ�\��
	//�Q�[���ɖ߂�{�^������������
	//�Q�[����ʂɖ߂�����configFlg��false
	if (!sceneConfigT.GetGamePlayFlg())
	{
		configFlg = false;
		bubbleFade.FadeIn();
	}
	else
	{
		bubbleFade.Initialize();
	}
	if (configFlg)
	{
		sceneConfigT.Update();
	}

	//�X�N���[��
	if (!poseFlg)
	{
		stg.Update(pl);
	}

	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		if (nextSceneTemp == SCENENO_CONFIG)
		{
			configFlg = true;
			sceneConfigT.SetGamePlayFlg();
			sceneConfigT.Load();
			sceneConfigT.Initialize();
		}
		else
		{
			if (nowPopUpTutorial != nullptr)
			{
				nowPopUpTutorial->Release();
			}

			if (nextSceneTemp == SCENENO_GAME)
			{
				//���g���C�A�������̓R���e�B�j���[�{�^���������ꂽ�珉����
				Initialize();
				return;
			}
			else
			{
				endFlg = true;
			}
		}

		//�V�[���̑J��
		nextScene = nextSceneTemp;
		return;
	}
	//R�Ń|�[�Y���
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpTutorial = new CPoseWindow;
		nowPopUpTutorial->SetSoundManager(*cSound);
		nowPopUpTutorial->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && popUpFlg&& !configFlg)
	{
		nowPopUpTutorial->Release();
		nowPopUpTutorial = NULL;
		popUpFlg = false;
		poseFlg = false;
	}

	//�ݒ�\��
	//�Q�[����ʂɖ߂�����configFlg��false
	if (!sceneConfigT.GetGamePlayFlg())   //�Q�[���ɖ߂�{�^������������
		configFlg = false;

	if (configFlg)
	{
		sceneConfigT.Update();
	}
	if (popUpFlg && !configFlg)
	{
		PopUpController();
	}
	//�|�[�Y��ʂ��J���Ă�����A����܂ōX�V���Ȃ�
	if (poseFlg)return;

	ui.Update(Event_None);
	for (int i = 0; i < 5; i++)
	{
		pl.Collision(obs, i, true, tutorialStep);
	}
	pl.Update(true, tutorialStep,Event_None);
	obs.Update(pl.GetDistance(), pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY(),tutorialStep, Event_None);
	MessageUpdate();


}

void CSceneTutorial::Render()
{
	stg.Render();
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	obs.Render(stg.GetScrollX(), stg.GetScrollY());
	
	//�őO�ʂ̊�w�i
	stg.ForeGroundRender();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(), true, Event_None,pl.GetPosY(), stg.GetScrollY());
	MessageRender();

	//���݂̃^�X�N�ꗗ�\��
	if (tutorialStep >= TutorialStep::Task_Movement)
	{
		font.RenderString(10, 100, MOF_COLOR_BLACK, "��\n��\n��\n��\n");

		if (!pl.GetMoveUpTask())
			font.RenderString(40, 100, MOF_COLOR_BLACK, "�� [W]�ŏ�Ɉړ�");
		else if (pl.GetMoveUpTask())
			font.RenderString(40, 100, MOF_COLOR_BLACK, "�� [W]�ŏ�Ɉړ�");

		if (!pl.GetMoveDownTask())
			font.RenderString(40, 140, MOF_COLOR_BLACK, "�� [S]�ŉ��Ɉړ�");
		else if (pl.GetMoveDownTask())
			font.RenderString(40, 140, MOF_COLOR_BLACK, "�� [S]�ŉ��Ɉړ�");
	}
	if(tutorialStep >= TutorialStep::Task_Action)
	{
		font.RenderString(10, 180, MOF_COLOR_BLACK, "��\n��\n��");

		if (!pl.GetJumpTask())
			font.RenderString(40, 180, MOF_COLOR_BLACK, "�� [ENTER]�ŃW�����v");
		else if (pl.GetJumpTask())
			font.RenderString(40, 180, MOF_COLOR_BLACK, "�� [ENTER]�ŃW�����v");

		if (!pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "�� [ENTER]�ŃG�T��H�ׂ�");
		else if (pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "�� [ENTER]�ŃG�T��H�ׂ�");
	}

	if (tutorialStep < TutorialStep::Task_Complete)
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
	}
	else
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
	}
	
	//�|�b�v�A�b�v�`��
	if (popUpFlg)
	{
		nowPopUpTutorial->Render();
	}
	if (configFlg)
	{
		sceneConfigT.Render();
	}

	//todo:�f�o�b�O�p ���Ƃŏ����i�|�[�Y��ʎg����悤�ɕύX������j
	//font.RenderStringScale(800, 50, 2.0f, MOF_COLOR_BLACK, "�f�o�b�O�p");
	//font.RenderStringScale(800, 100, 2.0f, MOF_COLOR_BLACK,"Enter�ŃQ�[�����j���[�ɖ߂�");

	bubbleFade.Render();

}

void CSceneTutorial::RenderDebug()
{
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
	obs.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneTutorial::Release()
{
	stg.Release();
	ui.Release();
	pl.Release();
	obs.Release();
	messageWindowImg.Release();
	free(fBuffer);

	if (nowPopUpTutorial != NULL)
	{
		nowPopUpTutorial->Release();
		if (nowPopUpTutorial)
		{
			delete nowPopUpTutorial;
			nowPopUpTutorial = NULL;
		}
	}
}

void CSceneTutorial::PopUpController()
{
	nowPopUpTutorial->Update();
	if (nowPopUpTutorial->GetButtonResult() == 1)
	{
		//���g���C�A�������̓R���e�B�j���[�{�^���������ꂽ�珉����
		//Initialize();
		nextSceneTemp = SCENENO_TUTORIAL;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 2)
	{
		//���j���[�{�^���������ꂽ�烁�j���[��ʂɑJ��
		//nextScene = SCENENO_GAMEMENU;
		//endFlg = true;
		nextSceneTemp = SCENENO_GAMEMENU;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 3)
	{
		//�^�C�g���{�^���������ꂽ��^�C�g����ʂɑJ��
		//nextScene = SCENENO_TITLE;
		//endFlg = true;
		nextSceneTemp = SCENENO_TITLE;
		bubbleFade.FadeOut();
	}
	else if (nowPopUpTutorial->GetButtonResult() == 4)
	{
		//�ݒ肪�����ꂽ��ݒ��ʂ�\��
		nextScene = SCENENO_CONFIG;
		//nextSceneTemp = SCENENO_CONFIG;
		//bubbleFade.FadeOut();

		configFlg = true;
		sceneConfigT.SetGamePlayFlg();
		sceneConfigT.Load();
		sceneConfigT.Initialize();
		//�ݒ�̏��������|�b�v�A�b�v�̏������s��Ȃ��̂ŁA������buttonResult��������
		nowPopUpTutorial->SetButtonResult(0);

	}
	else if (nowPopUpTutorial->GetButtonResult() == 5)
	{
		//�Q�[���ɖ߂邪�����ꂽ��
		poseFlg = false;
	}


	//�|�b�v�A�b�v�̕ύX
	if (nowPopUpTutorial->IsEnd())
	{
		//���̃|�b�v�A�b�v�̎擾
		short nextPopUp = nowPopUpTutorial->GetNextPopUp();
		//�Â��|�b�v�A�b�v�̏���
		nowPopUpTutorial->Release();
		delete nowPopUpTutorial;
		//���̃|�b�v�A�b�v�ԍ��ɉ����ă|�b�v�A�b�v��������
		switch (nextPopUp)
		{
		case POPUPNO_POSE:
			nowPopUpTutorial = new CPoseWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case POPUPNO_BACKTOTITLE:
			nowPopUpTutorial = new CBackToTitleWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case POPUPNO_RETRY:
			nowPopUpTutorial = new CRetryWindow;
			nowPopUpTutorial->Initialize();
			nowPopUpTutorial->SetSoundManager(*cSound);
			break;
		case NULL:
			nowPopUpTutorial = NULL;
			popUpFlg = false;
			break;
		}
	}
}
