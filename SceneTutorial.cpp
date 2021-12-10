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
	font.Create(26, fontName);
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
				tutorialStep = TutorialStep::Task_End;
				nextScene = SCENENO_GAME;
				endFlg = true;
			}
			else if (tutorialStep != pl.GetTaskCompleteStep())
			{
				for (int n = 0; n < MESSAGE_ARRAY_BYTE; n++)
				{
					fLineBuffer[n] = NULL;
				}
				fBufferOffset++; //�e�L�X�g�𕪂��Ă�����s�͕\�������ɓ���Ȃ��̂ŁA��΂�
				messageEndFlg = false;
				//�`���[�g���A���̒i�K����i�߂�
				tutorialStep += 1;
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
		CGraphicsUtilities::RenderString(1200, 980, "Space�������ăQ�[�����J�n����");
	}
	else if (messageEndFlg && tutorialStep != pl.GetTaskCompleteStep())
	{
		CGraphicsUtilities::RenderString(1200, 980, "Space�������Ď��ց�");
	}
	else if (messageEndFlg && tutorialStep == pl.GetTaskCompleteStep())
	{
		CGraphicsUtilities::RenderString(1200, 980, "�^�X�N�����Ȃ����I");
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
	tutorialStep = 0;
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
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
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(), true, Event_None);
	MessageRender();

	//���݂̃^�X�N�ꗗ�\��
	if (tutorialStep >= TutorialStep::Task_Movement)
	{
		CGraphicsUtilities::RenderString(10, 280, MOF_COLOR_BLACK, "��\n��\n��\n��\n");

		if (!pl.GetMoveUpTask())
			CGraphicsUtilities::RenderString(40, 280, MOF_COLOR_BLACK, "�� [W]�ŏ�Ɉړ�");
		else if (pl.GetMoveUpTask())
			CGraphicsUtilities::RenderString(40, 280, MOF_COLOR_BLACK, "�� [W]�ŏ�Ɉړ�");

		if (!pl.GetMoveDownTask())
			CGraphicsUtilities::RenderString(40, 320, MOF_COLOR_BLACK, "�� [S]�ŉ��Ɉړ�");
		else if (pl.GetMoveDownTask())
			CGraphicsUtilities::RenderString(40, 320, MOF_COLOR_BLACK, "�� [S]�ŉ��Ɉړ�");
	}
	if(tutorialStep >= TutorialStep::Task_Action)
	{
		CGraphicsUtilities::RenderString(10, 360, MOF_COLOR_BLACK, "��\n��\n��");

		if (!pl.GetJumpTask())
			CGraphicsUtilities::RenderString(40, 360, MOF_COLOR_BLACK, "�� [A]�ŃW�����v");
		else if (pl.GetJumpTask())
			CGraphicsUtilities::RenderString(40, 360, MOF_COLOR_BLACK, "�� [A]�ŃW�����v");

		if (!pl.GetEatTask())
			CGraphicsUtilities::RenderString(40, 400, MOF_COLOR_BLACK, "�� [A]�ŃG�T��H�ׂ�");
		else if (pl.GetEatTask())
			CGraphicsUtilities::RenderString(40, 400, MOF_COLOR_BLACK, "�� [A]�ŃG�T��H�ׂ�");
	}

	if (tutorialStep != TutorialStep::Task_Complete)
	{
		CGraphicsUtilities::RenderString(10, 240, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
	}
	else
	{
		CGraphicsUtilities::RenderString(10, 240, MOF_COLOR_BLACK, "�� �`���[�g���A������������");
	}
	

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
