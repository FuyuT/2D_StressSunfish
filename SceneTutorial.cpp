#include "SceneTutorial.h"
CSceneTutorial::CSceneTutorial():
	fBuffer(NULL),
	fBufferOffset(0),
	mShowDelay(0),
	messageEndFlg(false),
	tutorialStep(0)
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
	//�����񂪏I��(���s�̎��ɉ��s������)������AENTER�Ŏ��̐�����
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
		font.RenderString(1200, 980, "Space�������ăQ�[�����J�n����");
	}
	else if (messageEndFlg && tutorialStep != pl.GetTaskCompleteStep())
	{
		font.RenderString(1200, 980, "Space�������Ď��ց�");
	}
	else if (messageEndFlg && tutorialStep == pl.GetTaskCompleteStep())
	{
		font.RenderString(1200, 980, "�^�X�N�����Ȃ����I");
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
}

void CSceneTutorial::Update()
{
	//todo:�|�[�Y��ʕ\���ɕύX�@����Enter�Ń��j���[�ɖ߂�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		nextScene = SCENENO_GAMEMENU;
		endFlg = true;
	}

	//�t�F�[�h����
	bubbleFade.Update();
	bubbleFade.FadeIn();

	stg.Update(pl);

	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		//�V�[���̑J��
		endFlg = true;
		nextScene = nextSceneTemp;
		//Release();
		return;
	}

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
			font.RenderString(40, 180, MOF_COLOR_BLACK, "�� [A]�ŃW�����v");
		else if (pl.GetJumpTask())
			font.RenderString(40, 180, MOF_COLOR_BLACK, "�� [A]�ŃW�����v");

		if (!pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "�� [A]�ŃG�T��H�ׂ�");
		else if (pl.GetEatTask())
			font.RenderString(40, 220, MOF_COLOR_BLACK, "�� [A]�ŃG�T��H�ׂ�");
	}

	if (tutorialStep < TutorialStep::Task_Complete)
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
	}
	else
	{
		font.RenderString(10, 60, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
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
}
