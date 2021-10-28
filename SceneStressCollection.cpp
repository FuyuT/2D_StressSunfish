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
void CSceneStressCollection::Initialize()
{
	//�X�g���X�t���O�ǂݍ���
	LoadStressFlg();

	page = 1;
	//�����e�N�X�`���ǂݍ���
	//�t���O���I���Ȃ�Ή�����e�N�X�`���A�t���O���I�t�Ȃ疢�擾�e�N�X�`����ǂݍ��ށB
	if(increasedBodyTemperatureFlg)
		increasedBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		increasedBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		lowerBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationIconTexture.Load("siin_aikon.png");
	else
		starvationIconTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatIconTexture.Load("siin_aikon.png");
	else
		cloggedThroatIconTexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityIconTexture.Load("siin_aikon.png");
	else
		obesityIconTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactIconTexture.Load("siin_aikon.png");
	else
		impactIconTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("siin_aikon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");
	if(jumpFlg)
		jumpIconTexture.Load("siin_aikon.png");
	else
		jumpIconTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleIconTexture.Load("siin_aikon.png");
	else
		bubbleIconTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleIconTexture.Load("siin_aikon.png");
	else
		turtleIconTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowIconTexture.Load("siin_aikon.png");
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
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_INCREASEDBODYTEMPERATURE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�̉��㏸�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_INCREASEDBODYTEMPERATURE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_LOWERBODYTEMPERATURE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�̉��ቺ�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_LOWERBODYTEMPERATURE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_STARVATION).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�쎀�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_STARVATION);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_CLOGGEDTHROAT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�A�l�܂�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_CLOGGEDTHROAT);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_OBESITY).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�얞�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_OBESITY);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_IMPACT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:��Q���ƏՓ˂̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_IMPACT);
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_PARASITE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�񐶒��̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_PARASITE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_JUMP).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�W�����v�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_JUMP);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_BUBBLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�A�̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_BUBBLE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_TURTLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�E�~�K���̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_TURTLE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_WATERFLOW).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//�|�b�v�A�b�v�Ɏ���:�����̎����摜��\��������
				nowPopUpStress->SetButtonResult(CASE_WATERFLOW);
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
	nowPopUpStress->Release();
}

CRectangle CSceneStressCollection::GetRect(int i)
{
	//����:�̉��㏸�N���b�N��
	if (i == CASE_INCREASEDBODYTEMPERATURE && increasedBodyTemperatureFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + increasedBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + increasedBodyTemperatureIconTexture.GetHeight());
	//����:�̉��ቺ�N���b�N��
	if (i == CASE_LOWERBODYTEMPERATURE && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureIconTexture.GetHeight());
	//����:�쎀�N���b�N��
	if (i == CASE_STARVATION && starvationFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationIconTexture.GetWidth(), iconOneLinePosY + starvationIconTexture.GetHeight());
	//����:�A�Ɏh����N���b�N��
	if (i == CASE_CLOGGEDTHROAT && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatIconTexture.GetWidth(), iconTwoLinePosY + cloggedThroatIconTexture.GetHeight());
	//����:�얞�N���b�N��
	if(i == CASE_OBESITY && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityIconTexture.GetWidth(), iconTwoLinePosY + obesityIconTexture.GetHeight());
	//����:��Q���ƏՓ˃N���b�N��
	if (i == CASE_IMPACT && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactIconTexture.GetWidth(), iconTwoLinePosY + impactIconTexture.GetHeight());

	//����:�񐶒��N���b�N��
	if(i == CASE_PARASITE && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//����:�W�����v�N���b�N��
	if (i == CASE_JUMP && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpIconTexture.GetWidth(), iconOneLinePosY + jumpIconTexture.GetHeight());
	//����:�A�N���b�N��
	if(i == CASE_BUBBLE && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleIconTexture.GetWidth(), iconOneLinePosY + bubbleIconTexture.GetHeight());
	//����:�E�~�K���ڐG�N���b�N��
	if(i == CASE_TURTLE && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleIconTexture.GetWidth(), iconTwoLinePosY + turtleIconTexture.GetHeight());
	//����:����
	if(i == CASE_WATERFLOW && waterFlowFlg)
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

void CSceneStressCollection::GetStress(int i)
{
	//����:�̉��㏸�Q�b�g
	if (i == CASE_INCREASEDBODYTEMPERATURE)
		increasedBodyTemperatureFlg = true;
	//����:�̉��ቺ�Q�b�g
	if (i == CASE_LOWERBODYTEMPERATURE)
		lowerBodyTemperatureFlg = true;
	//����:�쎀�Q�b�g
	if (i == CASE_STARVATION)
		starvationFlg == true;
	//����:�A�l�܂�Q�b�g
	if (i == CASE_CLOGGEDTHROAT)
		cloggedThroatFlg = true;
	//����:�얞�Q�b�g
	if (i == CASE_OBESITY)
		obesityFlg = true;
	//����:��Q���ƏՓ˃Q�b�g
	if (i == CASE_IMPACT)
		impactFlg = true;
	//����:�񐶒��Q�b�g
	if (i == CASE_PARASITE)
		parasiteFlg = true;
	//����:�W�����v�Q�b�g
	if (i == CASE_JUMP)
		jumpFlg == true;
	//����:�A�Q�b�g
	if (i == CASE_BUBBLE)
		bubbleFlg = true;
	//����:�E�~�K���Q�b�g
	if (i == CASE_TURTLE)
		turtleFlg = true;
	//����:�����Q�b�g
	if (i == CASE_WATERFLOW)
		waterFlowFlg = true;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("Save.dat", "wb");
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
	FILE* fp = fopen("Save.dat", "rb");
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