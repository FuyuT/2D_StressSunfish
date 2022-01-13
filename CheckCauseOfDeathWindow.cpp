#include "CheckCauseOfDeathWindow.h"
CCheckCauseOfDeathWindow::CCheckCauseOfDeathWindow()
{

}
CCheckCauseOfDeathWindow::~CCheckCauseOfDeathWindow()
{
	Release();
}

void CCheckCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonBackTexture.Load("ButtonBack.png");

	//�t�H���g
	font.Load(fontAdd, fontName);
	font.Create(90, fontName);

	if (buttonResult == CAUSE_Hyperthermia)
		causeOfDeathTexture.Load("�}���{�E �̉��㏸.png");

	if (buttonResult == CAUSE_Frozen)
		causeOfDeathTexture.Load("�}���{�E �̉��ቺ.png");

	if (buttonResult == CAUSE_Starvation)
		causeOfDeathTexture.Load("�}���{�E ��2.png");

	if (buttonResult == CAUSE_ChokeOnShell)
		causeOfDeathTexture.Load("�}���{�E�@�A�܂�.png");

	if (buttonResult == CAUSE_Obesity)
		causeOfDeathTexture.Load("�얞�}���{�E2.png");

	if (buttonResult == CAUSE_Obstacle)
		causeOfDeathTexture.Load("��Q���ɂ������Ď��S.png");

	if (buttonResult == CAUSE_Parasite)
		causeOfDeathTexture.Load("�}���{�E�񐶒��X�g���X.png");

	if (buttonResult == CAUSE_Jump)
		causeOfDeathTexture.Load("���ʂɂ���������ꎀ�S.png");

	if (buttonResult == CAUSE_Bubble)
		causeOfDeathTexture.Load("�}���{�E�A.png");

	if (buttonResult == CAUSE_SeaTurtle)
		causeOfDeathTexture.Load("�}���{�E�T�\��.png");

	if (buttonResult == CAUSE_WaterFlow)
		causeOfDeathTexture.Load("������.png");

	if (buttonResult == CAUSE_ShoalFish)
		causeOfDeathTexture.Load("�}���{�E�@���Q�Փˎ� .png");

	buttonSelect = 1;
	endFlg = false;
}
void CCheckCauseOfDeathWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect().CollisionPoint(mousePosX, mousePosY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}

	if (buttonSelect == 1)
	{
		buttonBackScale = scaleController.ScaleControll(buttonBackScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
		}
	}
}
void CCheckCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	causeOfDeathTexture.RenderScale(causeOfDeathTexturePosX, causeOfDeathTexturePosY, 0.8);
	if (buttonResult == CAUSE_Hyperthermia)
	{
		font.RenderString(450, 760, MOF_XRGB(0, 0, 0), "�̉��㏸�������ĔM���ǂɂȂ莀�S");
	}

	if (buttonResult == CAUSE_Frozen)
	{
		font.RenderString(365, 760, MOF_XRGB(0, 0, 0), "�[�C�ɐ��肷���đ̉��������肷���Ď��S");
	}

	if (buttonResult == CAUSE_Starvation)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "���т�H�ׂȂ������ĉ쎀���Ă��܂���");
	}

	if (buttonResult == CAUSE_ChokeOnShell)
	{
		font.RenderString(440, 760, MOF_XRGB(0, 0, 0), "����k���A�Ɏh�������X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_Obesity)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "�H�׉߂��Ĕ얞�ɂȂ����X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_Obstacle)
	{
		font.RenderString(550, 760, MOF_XRGB(0, 0, 0), "��Q���ɂԂ������Ռ��Ŏ��S");
	}

	if (buttonResult == CAUSE_Parasite)
	{
		font.RenderString(400, 760, MOF_XRGB(0, 0, 0), "�񐶒����̂ɕt���������X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_Jump)
	{
		font.RenderString(390, 735, MOF_XRGB(0, 0, 0), "�񐶒���̂��痎�Ƃ��ׂɃW�����v����");
		font.RenderString(360, 800, MOF_XRGB(0, 0, 0), "���ʂɒ@���������ʏՌ����������Ď��S");
	}

	if (buttonResult == CAUSE_Bubble)
	{
		font.RenderString(530, 760, MOF_XRGB(0, 0, 0), "�A���ڂɓ������X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_SeaTurtle)
	{
		font.RenderString(450, 735, MOF_XRGB(0, 0, 0), "�ڂ̑O�̃E�~�K���ɂԂ��肻����");
		font.RenderString(640, 800, MOF_XRGB(0, 0, 0), "�\���̃X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_WaterFlow)
	{
		font.RenderString(475, 760, MOF_XRGB(0, 0, 0), "�}�ɉ���������ꂽ�X�g���X�Ŏ��S");
	}

	if (buttonResult == CAUSE_ShoalFish)
	{
		font.RenderString(525, 760, MOF_XRGB(0, 0, 0), "���Q�ɏՓ˂����X�g���X�Ŏ��S");
	}

	scaleController.ScaleRender(&buttonBackTexture, buttonBackPosX, buttonBackPosY, buttonBackScale);
}
void CCheckCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
	causeOfDeathTexture.Release();
}

void CCheckCauseOfDeathWindow::MouseCollision(int posX, int posY)
{
}
