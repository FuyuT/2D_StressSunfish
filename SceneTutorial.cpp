#include "SceneTutorial.h"
CFont FontPopRumCute;
CFont f1;
CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
}

bool CSceneTutorial::Load()
{
	if (!stg.Load())return false;
	if (!ui.Load())return false;
	if (!pl.Load())return false;
	if (!obs.Load())return false;
	if (!messageWindowImg.Load("MessageWindow.png"))return false;
	if (!TextLoad())return false;
	//font�̍쐬
	FontPopRumCute.Create(64, "MS�@�S�V�b�N");
	f1.Create(64, "MS�@����");
	//FontPopRumCute.Create(64, "	�|�v��ށ��L���[�g");
	
	return true;
}

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

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
	fBufferOffset = 0;
	mShowDelay = 0;
	
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
	pl.Update();
	ui.Update();
	MessageUpdate();
}

void CSceneTutorial::MessageUpdate()
{
	//������̏I�[�܂ł̊Ԏ��s
	if (fBuffer[fBufferOffset] != '\0')
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
			if (mShowDelay >= 5)
			{
				mShowDelay = 0;
				//�S�p��������
				if (IsDBCSLeadByte(fBuffer[fBufferOffset]))
				{
					//�S�p�����̏ꍇ�Q�o�C�g���ňꕶ���ɂȂ�
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
				//���p�̏ꍇ
				else
				{
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
			}
		}
	}
	//�����񂪏I��������AENTER�Ŏ��̐�����
	else
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
		}
	}
}

void CSceneTutorial::Render()
{
	stg.Render();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetBodyTemp(), pl.GetTemperature());
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	//char* test = "�`���[�g���A���Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n\nTutorial�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n\n�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q";
	//CGraphicsUtilities::RenderString(FIRST_LETTER_POS_X,FIRST_LETTER_POS_Y,"%s",test);
	CGraphicsUtilities::RenderString(400, 750, fLineBuffer);
}

void CSceneTutorial::RenderDebug()
{
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneTutorial::Release()
{
	stg.Release();
	ui.Release();
	pl.Release();
	messageWindowImg.Release();
	free(fBuffer);
}
