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
	if(increasedBodyTemperatureFlg)
		increasedBodyTemperatureIconTexture.Load("�}���{�E �̉��㏸icon.png");
	else
		increasedBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureIconTexture.Load("�}���{�E �̉��ቺicon.png");
	else
		lowerBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationIconTexture.Load("�}���{�E ��icon.png");
	else
		starvationIconTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatIconTexture.Load("�}���{�E�@�A�܂�icon.png");
	else
		cloggedThroatIconTexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityIconTexture.Load("�얞�}���{�E2icon.png");
	else
		obesityIconTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactIconTexture.Load("��Q���ɂ������Ď��Sicon.png");
	else
		impactIconTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("�}���{�E�񐶒��X�g���Xicon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");

	if(jumpFlg)
		jumpIconTexture.Load("���ʂɂ���������ꎀ�S �C�Ȃ�icon.png");
	else
		jumpIconTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleIconTexture.Load("siin_aikon.png");
	else
		bubbleIconTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleIconTexture.Load("�}���{�E�T�\��icon.png");
	else
		turtleIconTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowIconTexture.Load("������icon.png");
	else
		waterFlowIconTexture.Load("siin_aikon_Enpty.png");

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
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneStressCollection::Release();
	}

	if(!popUpFlg)
	{
		if (page == 1)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�̉��㏸�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�̉��ቺ�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Frozen);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�쎀�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Starvation);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�A�l�܂�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�얞�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Obesity);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:��Q���ƏՓ˂̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�񐶒��̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Parasite);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�W�����v�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Jump);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�A�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_Bubble);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_SeaTurtle).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�E�~�K���̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�����̎����摜��\��������
				nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
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
	CGraphicsUtilities::RenderString(100, 100, "�X�g���X�W���");
	if (page == 1)
	{
		//1�y�[�W�ڂɕ\��
		increasedBodyTemperatureIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "�̉��㏸");
		lowerBodyTemperatureIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "�̉��ቺ");
		starvationIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "�a");
		cloggedThroatIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY - 30, "���̍��E�b�k�ނ̊k");
		obesityIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY - 30, "�H�׉߂�");
		impactIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY - 30, "��Q��");
	}
	if (page == 2)
	{
		//2�y�[�W�ڂɕ\��
		parasiteIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "�񐶒�");
		jumpIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "�W�����v");
		bubbleIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "�A");
		turtleIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY - 30, "�E�~�K��");
		waterFlowIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY - 30, "����");
	}

	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	
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
	increasedBodyTemperatureIconTexture.Release();
	lowerBodyTemperatureIconTexture.Release();
	starvationIconTexture.Release();
	cloggedThroatIconTexture.Release();
	obesityIconTexture.Release();
	impactIconTexture.Release();
	parasiteIconTexture.Release();
	jumpIconTexture.Release();
	bubbleIconTexture.Release();
	turtleIconTexture.Release();
	waterFlowIconTexture.Release();

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
	if (i == CAUSE_Hyperthermia && increasedBodyTemperatureFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + increasedBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + increasedBodyTemperatureIconTexture.GetHeight());
	//����:�̉��ቺ�N���b�N��
	if (i == CAUSE_Frozen && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureIconTexture.GetHeight());
	//����:�쎀�N���b�N��
	if (i == CAUSE_Starvation && starvationFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationIconTexture.GetWidth(), iconOneLinePosY + starvationIconTexture.GetHeight());
	//����:�A�Ɏh����N���b�N��
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatIconTexture.GetWidth(), iconTwoLinePosY + cloggedThroatIconTexture.GetHeight());
	//����:�얞�N���b�N��
	if(i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityIconTexture.GetWidth(), iconTwoLinePosY + obesityIconTexture.GetHeight());
	//����:��Q���ƏՓ˃N���b�N��
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactIconTexture.GetWidth(), iconTwoLinePosY + impactIconTexture.GetHeight());

	//����:�񐶒��N���b�N��
	if(i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//����:�W�����v�N���b�N��
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpIconTexture.GetWidth(), iconOneLinePosY + jumpIconTexture.GetHeight());
	//����:�A�N���b�N��
	if(i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleIconTexture.GetWidth(), iconOneLinePosY + bubbleIconTexture.GetHeight());
	//����:�E�~�K���ڐG�N���b�N��
	if(i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleIconTexture.GetWidth(), iconTwoLinePosY + turtleIconTexture.GetHeight());
	//����:����
	if(i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + waterFlowIconTexture.GetWidth(), iconTwoLinePosY + waterFlowIconTexture.GetHeight());

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
	if (i == CAUSE_Hyperthermia && !increasedBodyTemperatureFlg)
	{
		increasedBodyTemperatureFlg = true;
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
		fwrite(&increasedBodyTemperatureFlg, sizeof(bool), 1, fp);
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
		fread(&increasedBodyTemperatureFlg, sizeof(bool), 1, fp);
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