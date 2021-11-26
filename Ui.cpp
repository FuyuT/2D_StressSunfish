#include "Ui.h"

bool CUi::Load()
{
	//�̉��A�C�R���̔w�i
	if (!stressMeter.Load("sutoresume--ta-.png"))
	{
		return false;
	}

	//�̉��A�C�R��
	if (!tempNormal.Load("nicochyan5.png"))
	{
		return false;
	}
	if (!tempHot.Load("nicochyan6.png"))
	{
		return false;
	}
	if (!tempCold.Load("nicochyan4.png"))
	{
		return false;
	}

	//�̉��v
	if (!tempMeter.Load("temperatureMeter.png"))
	{
		return false;
	}
	if (!tempMeterFrame.Load("temperatureMeterFrame.png"))
	{
		return false;
	}

	//�󕠃Q�[�W
	if (!hungerGauge.Load("stomach2.png"))
	{
		return false;
	}
	if (!hungerGaugeFrame.Load("stomach.png"))
	{
		return false;
	}

	//�񐶒�
	if (!parasite1.Load("kiseitilyuu.png"))
	{
		return false;
	}
	if (!parasite2.Load("kiseitilyuu2.png"))
	{
		return false;
	}
	if (!parasite3.Load("kiseitilyuu3.png"))
	{
		return false;
	}
	if (!parasite4.Load("kiseitilyuu4.png"))
	{
		return false;
	}
	if (!parasite5.Load("kiseitilyuu5.png"))
	{
		return false;
	}

	//�s���\UI
	//�W�����v
	if (!jumpPoss.Load("UI_Jump.png"))
	{
		return false;
	}
	//�H��
	if (!eatPoss.Load("UI_Eat.png"))
	{
		return false;
	}

	//����UI
	if (!cautionUi.Load("UI_Caution.png"))
	{
		return false;
	}
	//���x����UI
	//����
	if (!cautionHot.Load("UI_CautionTempUp.png"))
	{
		return false;
	}
	//�ቷ
	if (!cautionCold.Load("UI_CautionTempDown.png"))
	{
		return false;
	}

	return true;
}

void CUi::Initialize()
{
	font.Create(48, "MS�@����");
	//�_�Őݒ�
	//����
	cautionB.SetBlinkingCount(3);
	cautionB.SetBlinkingSpeed(50);
	cautionB.Initialize();
	//����
	cautionHotB.SetBlinkingCount(3);
	cautionHotB.SetBlinkingSpeed(50);
	cautionHotB.Initialize();
	//�ቷ
	cautionColdB.SetBlinkingCount(3);
	cautionColdB.SetBlinkingSpeed(50);
	cautionColdB.Initialize();
}

void CUi::Update()
{
	//�_�Őݒ�
	cautionB.Update();
	cautionHotB.Update();
	cautionColdB.Update();
}

void CUi::Render(int parasiteNum, int hungry, float tempRegionNum, int distanceNum, bool jumpFlg, bool eatFlg, bool tutorialFlg)
{
	//m���\�� �g�g��
	CGraphicsUtilities::RenderFillRect(2, 2, 220, 60, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderRect(2, 2, 220, 60, MOF_COLOR_BLACK);

	if (tutorialFlg)
	{
		font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "���� m");
	}
	else
	{
		if (distanceNum < 1000)
		{
			font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "%d m", distanceNum);
		}
		else if (distanceNum >= 1000)
		{
			distance = distanceNum / 1000;
			font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "%3.1 km", distance);
		}
	}

	stressMeter.Render(1600, 0);

	//�̉�UI�`��
	if (500 * (tempRegionNum * 0.01f) <= 150)
	{
		tempHot.Render(1600, 0);
		cautionHotB.SetInStart(true);
	}
	else if (500 * (tempRegionNum * 0.01f) >= 330)
	{
		tempCold.Render(1600, 0);
		cautionColdB.SetInStart(true);
	}
	else
	{
		tempNormal.Render(1600, 0);
		cautionHotB.SetInStart(false);
		cautionColdB.SetInStart(false);
	}

	//���x�vUI�`��
	tempMeterFrame.Render(1550, 200);
	CRectangle rec1(0,500 * (tempRegionNum * 0.01f), 500, 500);
	tempMeter.Render(1550, 200 + (500 * (tempRegionNum * 0.01f)), rec1);

	//�񐶒�UI�̕`��
	switch (parasiteNum)
	{
	case 1:
		parasite1.Render(1600, 0);
		break;
	case 2:
		parasite2.Render(1600, 0);
		break;
	case 3:
		parasite3.Render(1600, 0);
		break;
	case 4:
		parasite4.Render(1600, 0);
		break;
	case 5:
		parasite5.Render(1600, 0);
		break;
	}

	//�󕠃Q�[�WUI�`��
	CRectangle rec2(0, 0, 330, 200);
	hungerGaugeFrame.Render(1400, 0, rec2);
	CRectangle rec3(0, 200 * (hungry * 0.01f), 330, 200);
	hungerGauge.Render(1400, 200 * (hungry * 0.01f), rec3);
	
	//�s���\UI�̕`��
	//�W�����v
	if (jumpFlg)
	{
		jumpPoss.Render(1400, 0);
	}
	//�H��
	if (eatFlg)
	{
		eatPoss.Render(1400, 100);
	}

	//����UI�̕`��
	int w = g_pGraphics->GetTargetWidth();
	if (turtle.GetShow())
	{
		if (w - w / 4 >= turtle.GetPosx())
		{
			cautionB.SetInStart(true);
		}
	}
	else if (!turtle.GetShow())
	{
		cautionB.SetInStart(false);
	}
	cautionUi.Render(1000, 0, MOF_ARGB((int)(255 * cautionB.GetAlpha()), 255, 255, 255));
	//��������UI
	cautionHot.Render(1000, 125, MOF_ARGB((int)(255 * cautionHotB.GetAlpha()), 255, 255, 255));
	//�ቷ����UI
	cautionCold.Render(1000, 125, MOF_ARGB((int)(255 * cautionColdB.GetAlpha()), 255, 255, 255));
}

void CUi::Release()
{
	stressMeter.Release();

	tempNormal.Release();
	tempHot.Release();
	tempCold.Release();

	tempMeter.Release();
	tempMeterFrame.Release();

	hungerGauge.Release();
	hungerGaugeFrame.Release();

	parasite1.Release();
	parasite2.Release();
	parasite3.Release();
	parasite4.Release();
	parasite5.Release();

	cautionUi.Release();
	cautionHot.Release();
	cautionCold.Release();

	font.Release();
}