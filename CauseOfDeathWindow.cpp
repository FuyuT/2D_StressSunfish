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
	buttonSelect = 1;
	endFlg = false;
	buttonNextScaleFlg = false;

	//�t�H���g
	font.Load(fontAdd, fontName);
	font.Create(118, fontName);
}
void CCauseOfDeathWindow::Update()
{
	popUpScale = scaleController.ScaleShrinkControll(popUpScale, scaleMini, causeOfDeathScaleSpeed);
	if (!buttonNextScaleFlg)
	{
		buttonNextScale = scaleController.ScaleShrinkControll(buttonNextScale, scaleMini, causeOfDeathScaleSpeed);
		if (buttonNextScale = scaleMini)
			buttonNextScaleFlg = true;
	}
	causeOfDeathTextureScale = scaleController.ScaleShrinkControll(causeOfDeathTextureScale, 0.7, causeOfDeathScaleSpeed);
	deathTextScale = scaleController.ScaleShrinkControll(deathTextScale, scaleMini, causeOfDeathScaleSpeed);
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect().CollisionPoint(mousePosX, mousePosY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}

	if (buttonSelect == 1)
	{
		if (buttonNextScaleFlg)
			buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_RESULT;
		}
	}
}
void CCauseOfDeathWindow::Render()
{
	//popUpTexture.Render(popUpPosX, popUpPosY);
	scaleController.ScaleRender(&popUpTexture, popUpPosX, popUpPosY, popUpScale);
	switch (deathResult)
	{
	case CAUSE_Hyperthermia:
		font.RenderString(660, 750, MOF_XRGB(0, 0, 0), "���ʉ��͔M���I");
		break;

	case CAUSE_Frozen:
		font.RenderString(660, 750, MOF_XRGB(0, 0, 0), "�[�C�͊�������");
		break;

	case CAUSE_Starvation:
		font.RenderString(570, 750, MOF_XRGB(0, 0, 0), "���т��H�ׂ�������...");
		break;

	case CAUSE_ChokeOnShell:
		font.RenderString(750, 750, MOF_XRGB(0, 0, 0), "�����A�ɁI");
		break;

	case CAUSE_Obesity:
		font.RenderString(580, 780, MOF_XRGB(0, 0, 0), "�H�׉߂������������B");
		break;

	case CAUSE_Obstacle:
		font.RenderString(640, 750, MOF_XRGB(0, 0, 0), "�S�~�̓S�~���ցB");
		break;

	case CAUSE_Parasite:
		font.RenderString(640, 750, MOF_XRGB(0, 0, 0), "�y���Ă��܂��I");
		break;

	case CAUSE_Jump:
		font.RenderString(690, 750, MOF_XRGB(0, 0, 0), "���\�ɂ������B");
		break;

	case CAUSE_Bubble:
		font.RenderString(720, 750, MOF_XRGB(0, 0, 0), "�ڂ��A�A�A�I");
		break;

	case CAUSE_SeaTurtle:
		font.RenderString(450, 750, MOF_XRGB(0, 0, 0), "�E�~�K���ɓ�����Ǝv����...");
		break;

	case CAUSE_WaterFlow:
		font.RenderString(490, 750, MOF_XRGB(0, 0, 0), "�}�C�y�[�X�ōs��������ˁB");
		break;

	case CAUSE_ShoalFish:
		font.RenderString(680, 750, MOF_XRGB(0, 0, 0), "�O���狛�Q���I");
		break;

	}
	scaleController.ScaleRender(&caseOfDethTexture, causeOfDeathTexturePosX, causeOfDeathTexturePosY, causeOfDeathTextureScale);
	if (newGetDeathFlg)
	{
		newGetTexture.Render(350, 250);
	}
	scaleController.ScaleRender(&buttonNextTexture, buttonNextPosX, buttonNextPosY, buttonNextScale);
	scaleController.ScaleRender(&deathTextTexture, deathTextPosX, deathTextPosY, deathTextScale);
}
void CCauseOfDeathWindow::Release()
{
	newGetTexture.Release();
	deathTextTexture.Release();
	caseOfDethTexture.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}

void CCauseOfDeathWindow::MouseCollision(int posX, int posY)
{
}
