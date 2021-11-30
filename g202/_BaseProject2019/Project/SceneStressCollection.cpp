#include "SceneStressCollection.h"
#include "CheckCauseOfDeathWindow.h"

CPopUpWindowBase* nowPopUpStress = NULL;

CSceneStressCollection::CSceneStressCollection()
{

}
CSceneStressCollection::~CSceneStressCollection()
{
	Release();
}

void CSceneStressCollection::PlayBGM()
{
	cSound.AllStop();
	cSound.Play(SOUND_COLLECTION_BGM);
}

void CSceneStressCollection::Initialize()
{
	//�w�i�ǂݍ���
	backGroundTex.Load("Title.png");

	//�X�g���X�t���O�ǂݍ���
	LoadStressFlg();

	page = 1;
	//�����e�N�X�`���ǂݍ���
	//�t���O���I���Ȃ�Ή�����e�N�X�`���A�t���O���I�t�Ȃ疢�擾�e�N�X�`����ǂݍ��ށB
	if(hyperthermiaFlg)
		hyperthermiaTexture.Load("�}���{�E �̉��㏸icon.png");
	else
		hyperthermiaTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureTexture.Load("�}���{�E �̉��ቺicon.png");
	else
		lowerBodyTemperatureTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationTexture.Load("�}���{�E ��icon.png");
	else
		starvationTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatexture.Load("�}���{�E�@�A�܂�icon.png");
	else
		cloggedThroatexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityTexture.Load("�얞�}���{�E2icon.png");
	else
		obesityTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactTexture.Load("��Q���ɂ������Ď��Sicon.png");
	else
		impactTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("�}���{�E�񐶒��X�g���Xicon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");

	if(jumpFlg)
		jumpTexture.Load("���ʂɂ���������ꎀ�S �C�Ȃ�icon.png");
	else
		jumpTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleTexture.Load("siin_aikon.png");
	else
		bubbleTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleTexture.Load("�}���{�E�T�\��icon.png");
	else
		turtleTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowTexture.Load("������icon.png");
	else
		waterFlowTexture.Load("siin_aikon_Enpty.png");

	//�{�^���e�N�X�`���ǂݍ���
	menuButtonTexture.Load("ButtonMenu.png");
	rightButtonTexture.Load("ButtonRight.png");
	leftButtonTexture.Load("ButtonLeft.png");

	//�|�b�v�A�b�v������
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
	PlayBGM();
}
void CSceneStressCollection::Update()
{
	//�|�b�v�A�b�v����
	if (popUpFlg)
	{		
		if (nowPopUpStress->IsEnd())
		{
			nowPopUpStress->Release();
			popUpFlg = false;
		}
		nowPopUpStress->Initialize();
		nowPopUpStress->Update();
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		menuButtonScale =  scaleController.ScaleControll(menuButtonScale,scaleMax,scaleMini,scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneStressCollection::Release();
		}
	}
	else
	{
		menuButtonScale = scaleMini;
	}

	if(!popUpFlg)
	{
		if (page == 1)
		{
			if (GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY))
			{
				hyperthermiaScale = scaleController.ScaleControll(hyperthermiaScale,scaleMax,scaleMini,scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�̉��㏸�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
				}
			}
			else
			{
				hyperthermiaScale = scaleMini;
			}
			if (GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY))
			{
				lowerBodyTemperatureScale = scaleController.ScaleControll(lowerBodyTemperatureScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�̉��ቺ�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Frozen);
				}
			}
			else
			{
				lowerBodyTemperatureScale = scaleMini;
			}
			if (GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY))
			{
				starvationScale = scaleController.ScaleControll(starvationScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�쎀�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Starvation);
				}
			}
			else
			{
				starvationScale = scaleMini;
			}
			if (GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY))
			{
				cloggedThroatScale = scaleController.ScaleControll(cloggedThroatScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�A�l�܂�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
				}
			}
			else
			{
				cloggedThroatScale = scaleMini;
			}
			if (GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY))
			{
				obesityScale = scaleController.ScaleControll(obesityScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�얞�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Obesity);
				}
			}
			else
			{
				obesityScale = scaleMini;
			}
			if (GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY))
			{
				impactScale = scaleController.ScaleControll(impactScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:��Q���ƏՓ˂̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
				}
			}
			else
			{
				impactScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY))
			{
				parasiteScale = scaleController.ScaleControll(parasiteScale,scaleMax,scaleMini,scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�񐶒��̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Parasite);
				}
			}
			else
			{
				parasiteScale = scaleMini;
			}
			if (GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY))
			{
				jumpScale = scaleController.ScaleControll(jumpScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�W�����v�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Jump);
				}
			}
			else
			{
				jumpScale = scaleMini;
			}
			if (GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY))
			{
				bubbleScale = scaleController.ScaleControll(bubbleScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�A�̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_Bubble);
				}
			}
			else
			{
				bubbleScale = scaleMini;
			}
			if (GetRect(CAUSE_SeaTurtle).CollisionPoint(mousePosX, mousePosY))
			{
				turtleScalse = scaleController.ScaleControll(turtleScalse, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�E�~�K���̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
				}
			}
			else
			{
				turtleScalse = scaleMini;
			}
			if (GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY))
			{
				waterFlowScale = scaleController.ScaleControll(waterFlowScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//�|�b�v�A�b�v�Ɏ���:�����̎����摜��\��������
					nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
				}
			}
			else
			{
				waterFlowScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT) ||  (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)&& ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 1;
			}
		}
	}


	//F1�Ń|�b�v�A�b�v�\��
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
}
void CSceneStressCollection::Render()
{
	backGroundTex.Render(0, 0);
	if (page == 1)
	{
		//1�y�[�W�ڂɕ\��
		//hyperthermiaTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&hyperthermiaTexture, iconFirstRowPosX, iconOneLinePosY,hyperthermiaScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "�̉��㏸");
		//lowerBodyTemperatureIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&lowerBodyTemperatureTexture, iconSecondRowPosX, iconOneLinePosY, lowerBodyTemperatureScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "�̉��ቺ");
		//starvationIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&starvationTexture, iconThirdRowPosX, iconOneLinePosY, starvationScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "�a");
		//cloggedThroatIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&cloggedThroatexture, iconFirstRowPosX, iconTwoLinePosY, cloggedThroatScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY - 30, "���̍��E�b�k�ނ̊k");
		//obesityIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&obesityTexture, iconSecondRowPosX, iconTwoLinePosY, obesityScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY - 30, "�H�׉߂�");
		//impactIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&impactTexture, iconThirdRowPosX, iconTwoLinePosY, impactScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY - 30, "��Q��");
	}
	if (page == 2)
	{
		//2�y�[�W�ڂɕ\��
		//parasiteIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&parasiteIconTexture, iconFirstRowPosX, iconOneLinePosY, parasiteScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "�񐶒�");
		//jumpTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&jumpTexture, iconSecondRowPosX, iconOneLinePosY, jumpScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "�W�����v");
		//bubbleTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&bubbleTexture, iconThirdRowPosX, iconOneLinePosY, bubbleScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "�A");
		//turtleTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&turtleTexture, icon2PageFirstRowPosX, iconTwoLinePosY, turtleScalse);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY - 30, "�E�~�K��");
		//waterFlowTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&waterFlowTexture, icon2pageSecondRowPosX, iconTwoLinePosY, waterFlowScale);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY - 30, "����");
	}

	scaleController.ScaleRender(&menuButtonTexture , menuButtonPosX,menuButtonPosY,menuButtonScale);
	
	CGraphicsUtilities::RenderString(900, 800, "%d/2",page);
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);

	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}
}
void CSceneStressCollection::Release()
{
	backGroundTex.Release();
	hyperthermiaTexture.Release();
	lowerBodyTemperatureTexture.Release();
	starvationTexture.Release();
	cloggedThroatexture.Release();
	obesityTexture.Release();
	impactTexture.Release();
	parasiteIconTexture.Release();
	jumpTexture.Release();
	bubbleTexture.Release();
	turtleTexture.Release();
	waterFlowTexture.Release();

	menuButtonTexture.Release();
	if (nowPopUpStress != NULL)
	{
		nowPopUpStress->Release();
		if (nowPopUpStress)
		{
			delete nowPopUpStress;
			nowPopUpStress = NULL;
		}
	}
}

CRectangle CSceneStressCollection::GetRect(int i)
{
	//����:�̉��㏸�N���b�N��
	if (i == CAUSE_Hyperthermia && hyperthermiaFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + hyperthermiaTexture.GetWidth(), iconOneLinePosY + hyperthermiaTexture.GetHeight());
	//����:�̉��ቺ�N���b�N��
	if (i == CAUSE_Frozen && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureTexture.GetHeight());
	//����:�쎀�N���b�N��
	if (i == CAUSE_Starvation && starvationFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationTexture.GetWidth(), iconOneLinePosY + starvationTexture.GetHeight());
	//����:�A�Ɏh����N���b�N��
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatexture.GetWidth(), iconTwoLinePosY + cloggedThroatexture.GetHeight());
	//����:�얞�N���b�N��
	if(i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityTexture.GetWidth(), iconTwoLinePosY + obesityTexture.GetHeight());
	//����:��Q���ƏՓ˃N���b�N��
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactTexture.GetWidth(), iconTwoLinePosY + impactTexture.GetHeight());

	//����:�񐶒��N���b�N��
	if(i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//����:�W�����v�N���b�N��
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpTexture.GetWidth(), iconOneLinePosY + jumpTexture.GetHeight());
	//����:�A�N���b�N��
	if(i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleTexture.GetWidth(), iconOneLinePosY + bubbleTexture.GetHeight());
	//����:�E�~�K���ڐG�N���b�N��
	if(i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleTexture.GetWidth(), iconTwoLinePosY + turtleTexture.GetHeight());
	//����:����
	if(i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + waterFlowTexture.GetWidth(), iconTwoLinePosY + waterFlowTexture.GetHeight());

}

CRectangle CSceneStressCollection::ButtonGetRect(int i)
{
	if (i == 0)
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(leftButtonPosX, leftAndRightButtonPosY, leftButtonPosX + leftButtonTexture.GetWidth(), leftAndRightButtonPosY + leftButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(rightButtonPosX, leftAndRightButtonPosY, rightButtonPosX + rightButtonTexture.GetWidth(), leftAndRightButtonPosY + rightButtonTexture.GetHeight());
}

bool CSceneStressCollection::GetStress(int i)
{

	//�M���ǃQ�b�g
	if (i == CAUSE_Hyperthermia && !hyperthermiaFlg)
	{
		hyperthermiaFlg = true;
		SaveStressFlg();
		return true;
	}
	//�̉��ቺ�Q�b�g
	if (i == CAUSE_Frozen && !lowerBodyTemperatureFlg)
	{
		lowerBodyTemperatureFlg = true;
		SaveStressFlg();
		return true;
	}
	//�쎀
	if (i == CAUSE_Starvation && !starvationFlg)
	{
		starvationFlg = true;
		SaveStressFlg();
		return true;
	}
	//�A�l�܂�
	if (i == CAUSE_ChokeOnShell && !cloggedThroatFlg)
	{
		cloggedThroatFlg = true;
		SaveStressFlg();
		return true;
	}
	//�얞
	if (i == CAUSE_Obesity && !obesityFlg)
	{
		obesityFlg = true;
		SaveStressFlg();
		return true;
	}
	//�Փ�
	if (i == CAUSE_Obstacle && !impactFlg)
	{
		impactFlg = true;
		SaveStressFlg();
		return true;
	}
	//�񐶒�
	if (i == CAUSE_Parasite && !parasiteFlg)
	{
		parasiteFlg = true;
		SaveStressFlg();
		return true;
	}
	//�W�����v
	if (i == CAUSE_Jump && !jumpFlg)
	{
		jumpFlg = true;
		SaveStressFlg();
		return true;
	}
	//�A
	if (i == CAUSE_Bubble && !bubbleFlg)
	{
		bubbleFlg = true;
		SaveStressFlg();
		return true;
	}
	//�E�~�K��
	if (i == CAUSE_SeaTurtle && !turtleFlg)
	{
		turtleFlg = true;
		SaveStressFlg();
		return true;
	}
	//����
	if (i == CAUSE_WaterFlow && !waterFlowFlg)
	{
		waterFlowFlg = true;
		SaveStressFlg();
		return true;
	}
	return false;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "wb");
	if (fp)
	{
		fwrite(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fwrite(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fwrite(&starvationFlg, sizeof(bool), 1, fp);
		fwrite(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fwrite(&obesityFlg, sizeof(bool), 1, fp);
		fwrite(&impactFlg, sizeof(bool), 1, fp);
		fwrite(&parasiteFlg, sizeof(bool), 1, fp);
		fwrite(&jumpFlg, sizeof(bool), 1, fp);
		fwrite(&bubbleFlg, sizeof(bool), 1, fp);
		fwrite(&turtleFlg, sizeof(bool), 1, fp);
		fwrite(&waterFlowFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}

void CSceneStressCollection::LoadStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "rb");
	if (fp)
	{
		fread(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fread(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fread(&starvationFlg, sizeof(bool), 1, fp);
		fread(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fread(&obesityFlg, sizeof(bool), 1, fp);
		fread(&impactFlg, sizeof(bool), 1, fp);
		fread(&parasiteFlg, sizeof(bool), 1, fp);
		fread(&jumpFlg, sizeof(bool), 1, fp);
		fread(&bubbleFlg, sizeof(bool), 1, fp);
		fread(&turtleFlg, sizeof(bool), 1, fp);
		fread(&waterFlowFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}