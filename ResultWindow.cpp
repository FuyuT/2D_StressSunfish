#include "ResultWindow.h"
#include <stdio.h>

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{

}

void CResultWindow::Initialize()
{
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
			trophyTexture.Load("4_�_����.png");
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
	distanceFont.Create(172, "MS�@����");
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
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�싉");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_WATERFALL)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�ꋉ");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_LAKE)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�΋�");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_DAM)
		{
			font.RenderString(820, 750, MOF_XRGB(0, 0, 0), "�_����");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_SEWER)
		{
			font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "��������");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_INDIANOCEAN)
		{
			font.RenderString(880, 750, MOF_XRGB(0, 0, 0), "�C���h�m��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_AMAZONROVER)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�A�}�]���싉");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_OCEAN)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�C��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_SEAOFJAPAN)
		{
			font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "���{�C��");
			//�������`��
		}
		if (numberOfTrophy[0] == TROPHY_AROUNDTHEGLOBE)
		{
			font.RenderString(870, 750, MOF_XRGB(0, 0, 0), "�n�������");
			//�������`��
		}
	}
	//�g���t�B�[�`��
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		trophyTexture3.Render(trophyTexturePosX - 150, trophyTexturePosY);
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		trophyTexture2.Render(trophyTexturePosX - 100, trophyTexturePosY);
	}
	trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
	//�V�K�Q�b�g�̏ꍇnew��`��
	if (newGetTrophyFlg)
	{
		font.RenderString(trophyTexturePosX+10, trophyTexturePosY + trophyTexture.GetHeight()+ 10, MOF_XRGB(0, 0, 0), "NEW");
	}

	//m�`��
	if (distance < 1000000)
	{
		sprintf_s(meter,10, "%dm", distance);
	}
	else
	{
		sprintf_s(meter, 10 ,"%dm", 99999);
	}
	CRectangle rec;
	CRectangle drec;
	CGraphicsUtilities::CalculateStringRect(0, 0, meter, rec);
	float cx = popUpTexture.GetWidth() * 0.5f;
	float cy = popUpTexture.GetHeight() * 0.5f;
	float w = rec.GetWidth();
	float h = rec.GetHeight();
	rec.Top = cy - h * 0.5f;
	rec.Bottom = rec.Top + h;
	rec.Left = cx - w * 0.5f;
	rec.Right = rec.Left + w;
	distanceFont.RenderString(cx - rec.GetWidth() * 0.5f, rec.Top -50, MOF_XRGB(0, 0, 0), meter);
}
void CResultWindow::Release()
{
	distanceFont.Release();
	font.Release();
	trophyTexture.Release();
	trophyTexture2.Release();
	trophyTexture3.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}