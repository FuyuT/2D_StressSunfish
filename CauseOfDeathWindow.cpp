#include "CauseOfDeathWindow.h"

CCauseOfDeathWindow::CCauseOfDeathWindow()
{

}
CCauseOfDeathWindow::~CCauseOfDeathWindow()
{
	Release();
}

void CCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonNextTexture.Load("ButtonNext.png");
	deathTextTexture.Load("PopUpCaseOfDeath.png");
	newGetTexture.Load("NEW.png");
	//�����e�N�X�`���ǂݍ���
	switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		//�����F�̉��㏸�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E �̉��㏸.png");
		break;
	case CAUSE_Frozen:
		//�����F�̉��ቺ�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E �̉��ቺ.png");
		break;
	case CAUSE_Starvation:
		//�����F�쎀�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E ��2.png");
		break;
	case CAUSE_ChokeOnShell:
		//�����F�A�܂�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E�@�A�܂�.png");
		break;
	case CAUSE_Obesity:
		//�����F�얞�摜��ǂݍ���
		caseOfDethTexture.Load("�얞�}���{�E2.png");
		break;
	case CAUSE_Obstacle:
		//�����F�Փˉ摜��ǂݍ���
		caseOfDethTexture.Load("��Q���ɂ������Ď��S.png");
		break;
	case CAUSE_Parasite:
		//�����F�񐶒��摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E�񐶒��X�g���X.png");
		break;
	case CAUSE_Jump:
		//�����F�W�����v�摜��ǂݍ���
		caseOfDethTexture.Load("���ʂɂ���������ꎀ�S.png");
		break;
	case CAUSE_Bubble:
		//�����F�A�摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E�A.png");
		break;
	case CAUSE_SeaTurtle:
		//�����F�E�~�K���摜��ǂݍ���
		caseOfDethTexture.Load("�}���{�E�T�\��.png");
		break;
	case CAUSE_WaterFlow:
		//�����F�����A�C�R����ǂݍ���
		caseOfDethTexture.Load("������.png");
		break;
	case CAUSE_ShoalFish:
		//�����F�����A�C�R����ǂݍ���
		caseOfDethTexture.Load("�}���{�E�@���Q�Փˎ� .png");
		break;
	}
	font.Create(64, "MS�@����");
	buttonSelect = 1;
	endFlg = false;
}
void CCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		buttonSelect = 1;
	}
	
	if (buttonSelect == 1)
	{
		buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RESULT;
		}
	}
}
void CCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	/*switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�M����");
		break;
	case CAUSE_Frozen:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�̉��ቺ");
		break;
	case CAUSE_Starvation:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�쎀");
		break;
	case CAUSE_ChokeOnShell:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�A�l�܂�");
		break;
	case CAUSE_Obesity:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�얞");
		break;
	case CAUSE_Obstacle:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:��Q���ƏՓ�");
		break;
	case CAUSE_Parasite:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�񐶒�");
		break;
	case CAUSE_Jump:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�W�����v");
		break;
	case CAUSE_Bubble:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�A");
		break;
	case CAUSE_SeaTurtle:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:�E�~�K��");
		break;
	case CAUSE_WaterFlow:
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "����:����");
		break;
	}*/
	if (newGetDeathFlg)
	{
		newGetTexture.Render(350, 250);
	}
	caseOfDethTexture.Render(causeOfDeathTexturePosX,causeOfDeathTexturePosY);
	scaleController.ScaleRender(&buttonNextTexture,buttonNextPosX,buttonNextPosY,buttonNextScale);
	deathTextTexture.Render(deathTextPosX, deathTextPosY);
}
void CCauseOfDeathWindow::Release()
{
	newGetTexture.Release();
	deathTextTexture.Release();
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}