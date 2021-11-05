#include "CheckCauseOfDeathWindow.h"
#include "SceneStressCollection.h"
CCheckCauseOfDeathWindow::CCheckCauseOfDeathWindow()
{

}
CCheckCauseOfDeathWindow::~CCheckCauseOfDeathWindow()
{

}

void CCheckCauseOfDeathWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonBackTexture.Load("ButtonBack.png");

	if (buttonResult == CASE_INCREASEDBODYTEMPERATURE)
		causeOfDeathTexture.Load("�}���{�E �̉��㏸.png");

	if (buttonResult == CASE_LOWERBODYTEMPERATURE)
		causeOfDeathTexture.Load("�}���{�E �̉��ቺ.png");

	if (buttonResult == CASE_STARVATION)
		causeOfDeathTexture.Load("�}���{�E ��2.png");	
	
	if (buttonResult == CASE_CLOGGEDTHROAT)
		causeOfDeathTexture.Load("�}���{�E�@�A�܂�.png");

	if (buttonResult == CASE_OBESITY)
		causeOfDeathTexture.Load("�얞�}���{�E2.png");

	if (buttonResult == CASE_IMPACT)
		causeOfDeathTexture.Load("��Q���ɂ������Ď��S.png");

	if (buttonResult == CASE_PARASITE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_JUMP)
		causeOfDeathTexture.Load("���ʂɂ���������ꎀ�S.png");

	if (buttonResult == CASE_BUBBLE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_TURTLE)
		causeOfDeathTexture.Load("siin_aikon.png");

	if (buttonResult == CASE_WATERFLOW)
		causeOfDeathTexture.Load("������.png");

	font.Create(64, "MS�@����");

	endFlg = false;
}
void CCheckCauseOfDeathWindow::Update()
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
void CCheckCauseOfDeathWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	causeOfDeathTexture.Render(causeOfDeathTextureTexturePosX, causeOfDeathTextureTexturePosY);
	if (buttonResult == CASE_INCREASEDBODYTEMPERATURE)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "�̉��㏸�������ĔM���ǂɂȂ莀�S");
	
	if (buttonResult == CASE_LOWERBODYTEMPERATURE)
		font.RenderString(440, 250, MOF_XRGB(0, 0, 0), "�[�C�ɐ��肷���đ̉��������肷���Ď��S");

	if (buttonResult == CASE_STARVATION)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "���т�H�ׂȂ������ĉ쎀���Ă��܂���");

	if (buttonResult == CASE_CLOGGEDTHROAT)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "����k���A�Ɏh�������X�g���X�Ŏ��S");
	
	if (buttonResult == CASE_OBESITY)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "�H�׉߂��Ĕ얞�ɂȂ����X�g���X�Ŏ��S");
	
	if (buttonResult == CASE_IMPACT)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "��Q���ɂԂ������Ռ��Ŏ��S");
	
	if (buttonResult == CASE_PARASITE)
		font.RenderString(450, 250, MOF_XRGB(0, 0, 0), "�񐶒����̂ɕt���������X�g���X�Ŏ��S");
	
	if (buttonResult == CASE_JUMP)
	{
		font.RenderString(450, 225, MOF_XRGB(0, 0, 0), "�񐶒���̂��痎�Ƃ��ׂɃW�����v����");
		font.RenderString(400, 280, MOF_XRGB(0, 0, 0), "���ʂɒ@���������ʏՌ����������Ď��S");
	}

	if (buttonResult == CASE_BUBBLE)
		font.RenderString(550, 250, MOF_XRGB(0, 0, 0), "�A���ڂɓ������X�g���X�Ŏ��S");
	
	if (buttonResult == CASE_TURTLE)
	{
		font.RenderString(450, 225, MOF_XRGB(0, 0, 0), "�ڂ̑O�̃E�~�K���ɂԂ��肻����");
		font.RenderString(575, 275, MOF_XRGB(0, 0, 0), "�\���̃X�g���X�Ŏ��S");
	}

	if (buttonResult == CASE_WATERFLOW)
		font.RenderString(475, 250, MOF_XRGB(0, 0, 0), "�}�ɉ���������ꂽ�X�g���X�Ŏ��S");
	
	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CCheckCauseOfDeathWindow::Release()
{
	popUpTexture.Release();
	buttonBackTexture.Release();
	causeOfDeathTexture.Release();
}