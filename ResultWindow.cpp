#include "ResultWindow.h"

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{

}

void CResultWindow::Initialize()
{
	distans = 
	popUpTexture.Load("Pop_up���t2.png");
	buttonNextTexture.Load("ButtonNext.png");
	if (numberOfTrophy[0] != TROPHY_NULL)
	{
		switch (numberOfTrophy[0])
		{
		case TROPHY_RIVER:
			trophyTexture.Load("1_�싉.png");
			//�������ǂݍ���
			break;
		case  TROPHY_WATERFALL:
			trophyTexture.Load("2_�ꋉ.png");
			//�������ǂݍ���
			break;
		case TROPHY_LAKE:
			trophyTexture.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_DAM:
			trophyTexture.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEWER:
			trophyTexture.Load("5_��������.png");
			//�������ǂݍ���
			break;
		case TROPHY_INDIANOCEAN:
			trophyTexture.Load("6_�C���h�m��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AMAZONROVER:
			trophyTexture.Load("7_�A�}�]���싉.png");
			//�������ǂݍ���
			break;
		case TROPHY_OCEAN:
			trophyTexture.Load("8_�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEAOFJAPAN:
			trophyTexture.Load("9_���{�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AROUNDTHEGLOBE:
			trophyTexture.Load("10_�n�������.png");
			//�������ǂݍ���
			break;
		case TROPHY_ZEROMOTIVATION:
			trophyTexture.Load("S1_���C�[����.png");
			//�������ǂݍ���
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture.Load("S5_�x�m�R��.png");
			//�������ǂݍ���
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture.Load("S4_���}���\����.png");
			//�������ǂݍ���
			break;
		case TROPHY_BIWALAKE:
			trophyTexture.Load("S2_���i�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_JACKPOD:
			trophyTexture.Load("S3_�W���b�N�|�b�g��.png");
			//�������ǂݍ���
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture.Load("S6_�˔\����.png");
			//�������ǂݍ���
			break;
		}
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		switch (numberOfTrophy[1])
		{
		case TROPHY_RIVER:
			trophyTexture2.Load("1_�싉.png");
			//�������ǂݍ���
			break;
		case  TROPHY_WATERFALL:
			trophyTexture2.Load("2_�ꋉ.png");
			//�������ǂݍ���
			break;
		case TROPHY_LAKE:
			trophyTexture2.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_DAM:
			trophyTexture2.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEWER:
			trophyTexture2.Load("5_��������.png");
			//�������ǂݍ���
			break;
		case TROPHY_INDIANOCEAN:
			trophyTexture2.Load("6_�C���h�m��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AMAZONROVER:
			trophyTexture2.Load("7_�A�}�]���싉.png");
			//�������ǂݍ���
			break;
		case TROPHY_OCEAN:
			trophyTexture2.Load("8_�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEAOFJAPAN:
			trophyTexture2.Load("9_���{�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AROUNDTHEGLOBE:
			trophyTexture2.Load("10_�n�������.png");
			//�������ǂݍ���
			break;
		case TROPHY_ZEROMOTIVATION:
			trophyTexture2.Load("S1_���C�[����.png");
			//�������ǂݍ���
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture2.Load("S5_�x�m�R��.png");
			//�������ǂݍ���
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture2.Load("S4_���}���\����.png");
			//�������ǂݍ���
			break;
		case TROPHY_BIWALAKE:
			trophyTexture2.Load("S2_���i�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_JACKPOD:
			trophyTexture2.Load("S3_�W���b�N�|�b�g��.png");
			//�������ǂݍ���
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture2.Load("S6_�˔\����.png");
			//�������ǂݍ���
			break;
		}
	}
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		switch (numberOfTrophy[2])
		{
		case TROPHY_RIVER:
			trophyTexture3.Load("1_�싉.png");
			//�������ǂݍ���
			break;
		case  TROPHY_WATERFALL:
			trophyTexture3.Load("2_�ꋉ.png");
			//�������ǂݍ���
			break;
		case TROPHY_LAKE:
			trophyTexture3.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_DAM:
			trophyTexture3.Load("3_�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEWER:
			trophyTexture3.Load("5_��������.png");
			//�������ǂݍ���
			break;
		case TROPHY_INDIANOCEAN:
			trophyTexture3.Load("6_�C���h�m��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AMAZONROVER:
			trophyTexture3.Load("7_�A�}�]���싉.png");
			//�������ǂݍ���
			break;
		case TROPHY_OCEAN:
			trophyTexture3.Load("8_�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_SEAOFJAPAN:
			trophyTexture3.Load("9_���{�C��.png");
			//�������ǂݍ���
			break;
		case TROPHY_AROUNDTHEGLOBE:
			trophyTexture3.Load("10_�n�������.png");
			//�������ǂݍ���
			break;
		case TROPHY_ZEROMOTIVATION:
			trophyTexture3.Load("S1_���C�[����.png");
			//�������ǂݍ���
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture3.Load("S5_�x�m�R��.png");
			//�������ǂݍ���
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture3.Load("S4_���}���\����.png");
			//�������ǂݍ���
			break;
		case TROPHY_BIWALAKE:
			trophyTexture3.Load("S2_���i�΋�.png");
			//�������ǂݍ���
			break;
		case TROPHY_JACKPOD:
			trophyTexture3.Load("S3_�W���b�N�|�b�g��.png");
			//�������ǂݍ���
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture3.Load("S6_�˔\����.png");
			//�������ǂݍ���
			break;
		}
	}

	font.Create(64, "MS�@����");
	endFlg = false;
}
void CResultWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
		nextPopUp = POPUPNO_CONTINUE;
	}
}
void CResultWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "����");
	buttonNextTexture.Render(buttonNextPosX, buttonNextPosY);

	if (numberOfTrophy[0] != TROPHY_NULL)
	{
		if (numberOfTrophy[0] == TROPHY_RIVER)
		{
			trophyTexture.Render(0, 0);
			font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�싉");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_WATERFALL)
		{
			font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�ꋉ");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_LAKE)
		{
			font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�΋�");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_DAM)
		{
			font.RenderString(820, 250, MOF_XRGB(0, 0, 0), "�_����");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_SEWER)
		{
			font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "��������");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_INDIANOCEAN)
		{
			font.RenderString(780, 250, MOF_XRGB(0, 0, 0), "�C���h�m��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_AMAZONROVER)
		{
			font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "�A�}�]���싉");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_OCEAN)
		{
			font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�C��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_SEAOFJAPAN)
		{
			font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "���{�C��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_AROUNDTHEGLOBE)
		{
			font.RenderString(770, 250, MOF_XRGB(0, 0, 0), "�n�������");
			//�������`��
		}
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		trophyTexture2.Render(trophyTexturePosX + 5, trophyTexturePosY);
	}
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		trophyTexture3.Render(trophyTexturePosX + 10, trophyTexturePosY);
	}
	trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
}
void CResultWindow::Release()
{
	trophyTexture.Release();
	trophyTexture2.Release();
	trophyTexture3.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}