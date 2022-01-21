#include "ResultWindow.h"
#include <stdio.h>

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{
	Release();
}

void CResultWindow::Initialize()
{
	popUpTexture.Load("Pop_up���t2.png");
	buttonNextTexture.Load("ButtonNext.png");
	resultTexture.Load("PopUpResult.png");
	newGetTexture.Load("NEW.png");
	if (numberOfTrophy[0] != TROPHY_NULL)
	{
		switch (numberOfTrophy[0])
		{
		case TROPHY_RIVER:
			trophyTexture.Load("1_�싉.png");
			classPlateTexture.Load("PlateRiver.png");
			break;
		case  TROPHY_WATERFALL:
			trophyTexture.Load("2_�ꋉ.png");
			classPlateTexture.Load("PlateWaterfall.png");
			break;
		case TROPHY_LAKE:
			trophyTexture.Load("3_�΋�.png");
			classPlateTexture.Load("PlateLike.png");
			break;
		case TROPHY_DAM:
			trophyTexture.Load("4_�_����.png");
			classPlateTexture.Load("PlateDam.png");
			break;
		case TROPHY_SEWER:
			trophyTexture.Load("5_��������.png");
			classPlateTexture.Load("PlateSewer.png");
			break;
		case TROPHY_INDIANOCEAN:
			trophyTexture.Load("6_�C���h�m��.png");
			classPlateTexture.Load("PlateIndianOcean.png");
			break;
		case TROPHY_AMAZONROVER:
			trophyTexture.Load("7_�A�}�]���싉.png");
			classPlateTexture.Load("PlateAmazonRiver.png");
			break;
		case TROPHY_OCEAN:
			trophyTexture.Load("8_�C��.png");
			classPlateTexture.Load("PlateOcean.png");
			break;
		case TROPHY_SEAOFJAPAN:
			trophyTexture.Load("9_���{�C��.png");
			classPlateTexture.Load("PlateSeaOfJapan.png");
			break;
		case TROPHY_AROUNDTHEGLOBE:
			trophyTexture.Load("10_�n�������.png");
			classPlateTexture.Load("PlateAroundTheGlobe.png");
			break;
		case TROPHY_ZEROMOTIVATION:
			trophyTexture.Load("S1_���C�[����.png");
			classPlateTexture.Load("PlateZeroMotibation.png");
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture.Load("S5_�x�m�R��.png");
			classPlateTexture.Load("PlateMountFuji.png");
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture.Load("S4_���}���\����.png");
			classPlateTexture.Load("PlateOsakaMarathon.png");
			break;
		case TROPHY_BIWALAKE:
			trophyTexture.Load("S2_���i�΋�.png");
			classPlateTexture.Load("PlateBiwaLake.png");
			break;
		case TROPHY_JACKPOD:
			trophyTexture.Load("S3_�W���b�N�|�b�g��.png");
			classPlateTexture.Load("PlateJackPod.png");
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture.Load("S6_�˔\����.png");
			classPlateTexture.Load("PlateTalentDemon.png");
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
			trophyTexture2.Load("4_�_����.png");
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
			trophyTexture3.Load("4_�_����.png");
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

	buttonSelect = 1;
	distanceFont.Create(172, "MS�@����");
	endFlg = false;

	font.Load(fileAdd, fontName);
	font.Create(172, fontName);
}
void CResultWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	MouseCollision(mousePosX, mousePosY);
	
	if (buttonSelect == 1)
	{
		buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_CONTINUE;
		}
	}

}
void CResultWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	resultTexture.Render(resultTextPosX, resultTextPosY);
	scaleController.ScaleRender(&buttonNextTexture,buttonNextPosX,buttonNextPosY,buttonNextScale);

	//if (numberOfTrophy[0] != TROPHY_NULL)
	//{
	//	if (numberOfTrophy[0] == TROPHY_RIVER)
	//	{
	//		font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�싉");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_WATERFALL)
	//	{
	//		font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�ꋉ");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_LAKE)
	//	{
	//		font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�΋�");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_DAM)
	//	{
	//		font.RenderString(820, 750, MOF_XRGB(0, 0, 0), "�_����");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_SEWER)
	//	{
	//		font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "��������");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_INDIANOCEAN)
	//	{
	//		font.RenderString(880, 750, MOF_XRGB(0, 0, 0), "�C���h�m��");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_AMAZONROVER)
	//	{
	//		font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�A�}�]���싉");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_OCEAN)
	//	{
	//		font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "�C��");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_SEAOFJAPAN)
	//	{
	//		font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "���{�C��");
	//		//�������`��
	//	}
	//	if (numberOfTrophy[0] == TROPHY_AROUNDTHEGLOBE)
	//	{
	//		font.RenderString(870, 750, MOF_XRGB(0, 0, 0), "�n�������");
	//		//�������`��
	//	}
	//}
	//�g���t�B�[�`��
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		if (numberOfTrophy[2] == TROPHY_MOUNTFJI)
		{
			trophyTexture3.Render(trophyTexturePosX - 100, trophyTexturePosY + 195);
		}
		else if (numberOfTrophy[2] == TROPHY_OCEAN)
		{
			trophyTexture3.Render(trophyTexturePosX - 100, trophyTexturePosY);
		}
		else if (numberOfTrophy[2] == TROPHY_SEAOFJAPAN)
		{
			trophyTexture3.Render(trophyTexturePosX - 90, trophyTexturePosY);
		}
		else
		{
			trophyTexture3.Render(trophyTexturePosX - 100, trophyTexturePosY);
		}
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		if (numberOfTrophy[1] == TROPHY_MOUNTFJI)
		{
			trophyTexture2.Render(trophyTexturePosX - 50, trophyTexturePosY + 195);
		}
		else if (numberOfTrophy[1] == TROPHY_OCEAN)
		{
			trophyTexture2.Render(trophyTexturePosX  +30 , trophyTexturePosY);
		}
		else if (numberOfTrophy[1] == TROPHY_SEAOFJAPAN)
		{
			trophyTexture2.Render(trophyTexturePosX - 40, trophyTexturePosY);
		}
		else
		{
			trophyTexture2.Render(trophyTexturePosX - 50, trophyTexturePosY);
		}	
	}

	if (numberOfTrophy[0] == TROPHY_MOUNTFJI)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY + 195);
	}
	else if (numberOfTrophy[0] == TROPHY_OCEAN)
	{
		trophyTexture.Render(trophyTexturePosX + 90, trophyTexturePosY);
	}
	else if (numberOfTrophy[0] == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Render(trophyTexturePosX + 90, trophyTexturePosY);
	}
	else
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
	}

	if (numberOfTrophy[0] == TROPHY_JACKPOD)
	{
		scaleController.ScaleRender(&classPlateTexture, classPlatePosX - 10, classPlatePosY - 80,0.9f);
	}
	else
	{
		classPlateTexture.Render(classPlatePosX, classPlatePosY);
	}
	//�V�K�Q�b�g�̏ꍇnew��`��
	if (newGetTrophyFlg)
	{
		if (numberOfTrophy[2] != TROPHY_NULL)
		{
			if (numberOfTrophy[0] == TROPHY_MOUNTFJI)
				newGetTexture.Render(trophyTexturePosX - 90, trophyTexturePosY + trophyTexture.GetHeight() + 205);
			else
				newGetTexture.Render(trophyTexturePosX - 90, trophyTexturePosY + trophyTexture.GetHeight() + 10);
		}
		else if (numberOfTrophy[1] != TROPHY_NULL)
		{
			if (numberOfTrophy[0] == TROPHY_MOUNTFJI)
				newGetTexture.Render(trophyTexturePosX - 50, trophyTexturePosY + trophyTexture.GetHeight() + 205);
			else
				newGetTexture.Render(trophyTexturePosX - 50, trophyTexturePosY + trophyTexture.GetHeight() + 10);
		}
		else
		{
			if (numberOfTrophy[0] == TROPHY_MOUNTFJI)
				newGetTexture.Render(trophyTexturePosX - 25, trophyTexturePosY + trophyTexture.GetHeight() + 205);
			else
				newGetTexture.Render(trophyTexturePosX - 25, trophyTexturePosY + trophyTexture.GetHeight() + 10);
		}
	}

	//m�`��
	if (distance < 1000000)
	{
		if (distance >= 1000)
		{
			double distanceNum = distance / 100;
			int km = distanceNum;
			double trueDis = (double)distanceNum / 10;
			sprintf_s(meter, 10, "%4.1fkm", trueDis);
		}
		else
		{
			sprintf_s(meter, 10, "%dm", distance);
		}
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
	font.RenderString(cx - rec.GetWidth() * 0.5f, rec.Top -50, MOF_XRGB(0, 0, 0), meter);
}
void CResultWindow::Release()
{
	newGetTexture.Release();
	distanceFont.Release();
	resultTexture.Release();
	classPlateTexture.Release();
	font.Release();
	trophyTexture.Release();
	trophyTexture2.Release();
	trophyTexture3.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}

void CResultWindow::MouseCollision(int posX, int posY)
{
	if (GetRect().CollisionPoint(posX,posY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}
}
