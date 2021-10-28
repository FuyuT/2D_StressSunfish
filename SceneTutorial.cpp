#include "SceneTutorial.h"
CFont FontPopRumCute;

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
	//FontPopRumCute.Create(64, "MS ����");
	FontPopRumCute.Create(64, "	�|�v��ށ��L���[�g");

	return true;
}

bool CSceneTutorial::TextLoad()
{
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen("Text\\Tutorial.txt", "rt");
	if (fp == NULL)return false;
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);  //fp�̈ʒu���t�@�C���̏I�[��
	long fSize = ftell(fp);  //�t�@�C���̓ǂݏ����ʒu���擾�A�ʒu�ŗe�ʂ����߂�
	fseek(fp, 0, SEEK_SET);  //fp�̈ʒu���t�@�C���̐擪��
	//�t�@�C���̗e�ʕ��̃�������malloc�œ��I�Ɋm��
	fBuffer = NULL;
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
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
	pl.Update();
	ui.Update();
}

void CSceneTutorial::Render()
{
	stg.Render();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetBodyTemp(), pl.GetTemperature());
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	//char* test = "�`���[�g���A���Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n\nTutorial�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q\n\n�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q";
	//CGraphicsUtilities::RenderString(FIRST_LETTER_POS_X,FIRST_LETTER_POS_Y,"%s",test);
	FontPopRumCute.RenderString(100, 100,"�Ă���");
	Mof::LPString a = FontPopRumCute.GetName();
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
