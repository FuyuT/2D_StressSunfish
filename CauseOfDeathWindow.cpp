#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{

}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonNextTexture.Load("ButtonNext.png");
	//�����e�N�X�`���ǂݍ���
	switch (dethResult)
	{
	case CASE_INCREASEDBODYTEMPERATURE:
		//�����F�̉��㏸�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E �̉��㏸.png");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		//�����F�̉��ቺ�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E �̉��ቺ.png");
		break;
	case CASE_STARVATION:
		//�����F�쎀�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E ��2.png");
		break;
	case CASE_CLOGGEDTHROAT:
		//�����F�A�܂�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E�@�A�܂�.png");
		break;
	case CASE_OBESITY:
		//�����F�얞�摜��ǂݍ���
		caseOfDethTexture.Load("�얞�}���{�E2.png");
		break;
	case CASE_IMPACT:
		//�����F�Փˉ摜��ǂݍ���
		caseOfDethTexture.Load("��Q���ɂ������Ď��S.png");
		break;
	case CASE_PARASITE:
		//�����F�񐶒��摜��ǂݍ���
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_JUMP:
		//�����F�W�����v�摜��ǂݍ���
		caseOfDethTexture.Load("���ʂɂ���������ꎀ�S.png");
		break;
	case CASE_BUBBLE:
		//�����F�A�摜��ǂݍ���
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_TURTLE:
		//�����F�E�~�K���摜��ǂݍ���
		caseOfDethTexture.Load("siin_aikon.png");
		break;
	case CASE_WATERFLOW:
		//�����F�����A�C�R����ǂݍ���
		caseOfDethTexture.Load("������.png");
		break;
	}
	font.Create(64, "MS�@����");
	endFlg = false;
}
void CCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_RESULT;
	}
}
void CCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	switch (dethResult)
	{
	case CASE_INCREASEDBODYTEMPERATURE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�M����");
		break;
	case CASE_LOWERBODYTEMPERATURE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�̉��ቺ");
		break;
	case CASE_STARVATION:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�쎀");
		break;
	case CASE_CLOGGEDTHROAT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�A�l�܂�");
		break;
	case CASE_OBESITY:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�얞");
		break;
	case CASE_IMPACT:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:��Q���ƏՓ�");
		break;
	case CASE_PARASITE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�񐶒�");
		break;
	case CASE_JUMP:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�W�����v");
		break;
	case CASE_BUBBLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�A");
		break;
	case CASE_TURTLE:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�E�~�K��");
		break;
	case CASE_WATERFLOW:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:����");
		break;
	}
	if (newGetDethFlg)
	{
		font.RenderString(350, 250, MOF_XRGB(0, 0, 0), "NEW");
	}
	caseOfDethTexture.Render(715,350);
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);
}
void CCauseOfDeathWindow::Release()
{
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}