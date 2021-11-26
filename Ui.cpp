#include "Ui.h"

bool CUi::Load()
{
	//体温アイコンの背景
	if (!stressMeter.Load("sutoresume--ta-.png"))
	{
		return false;
	}

	//体温アイコン
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

	//体温計
	if (!tempMeter.Load("temperatureMeter.png"))
	{
		return false;
	}
	if (!tempMeterFrame.Load("temperatureMeterFrame.png"))
	{
		return false;
	}

	//空腹ゲージ
	if (!hungerGauge.Load("stomach2.png"))
	{
		return false;
	}
	if (!hungerGaugeFrame.Load("stomach.png"))
	{
		return false;
	}

	//寄生虫
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

	//行動可能UI
	//ジャンプ
	if (!jumpPoss.Load("UI_Jump.png"))
	{
		return false;
	}
	//食事
	if (!eatPoss.Load("UI_Eat.png"))
	{
		return false;
	}

	//注意UI
	if (!cautionUi.Load("UI_Caution.png"))
	{
		return false;
	}
	//温度注意UI
	//高温
	if (!cautionHot.Load("UI_CautionTempUp.png"))
	{
		return false;
	}
	//低温
	if (!cautionCold.Load("UI_CautionTempDown.png"))
	{
		return false;
	}

	return true;
}

void CUi::Initialize()
{
	font.Create(48, "MS　明朝");
	//点滅設定
	//注意
	cautionB.SetBlinkingCount(3);
	cautionB.SetBlinkingSpeed(50);
	cautionB.Initialize();
	//高温
	cautionHotB.SetBlinkingCount(3);
	cautionHotB.SetBlinkingSpeed(50);
	cautionHotB.Initialize();
	//低温
	cautionColdB.SetBlinkingCount(3);
	cautionColdB.SetBlinkingSpeed(50);
	cautionColdB.Initialize();
}

void CUi::Update()
{
	//点滅設定
	cautionB.Update();
	cautionHotB.Update();
	cautionColdB.Update();
}

void CUi::Render(int parasiteNum, int hungry, float tempRegionNum, int distanceNum, bool jumpFlg, bool eatFlg, bool tutorialFlg)
{
	//m数表示 枠組み
	CGraphicsUtilities::RenderFillRect(2, 2, 220, 60, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderRect(2, 2, 220, 60, MOF_COLOR_BLACK);

	if (tutorialFlg)
	{
		font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "━━ m");
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

	//体温UI描画
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

	//温度計UI描画
	tempMeterFrame.Render(1550, 200);
	CRectangle rec1(0,500 * (tempRegionNum * 0.01f), 500, 500);
	tempMeter.Render(1550, 200 + (500 * (tempRegionNum * 0.01f)), rec1);

	//寄生虫UIの描画
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

	//空腹ゲージUI描画
	CRectangle rec2(0, 0, 330, 200);
	hungerGaugeFrame.Render(1400, 0, rec2);
	CRectangle rec3(0, 200 * (hungry * 0.01f), 330, 200);
	hungerGauge.Render(1400, 200 * (hungry * 0.01f), rec3);
	
	//行動可能UIの描画
	//ジャンプ
	if (jumpFlg)
	{
		jumpPoss.Render(1400, 0);
	}
	//食事
	if (eatFlg)
	{
		eatPoss.Render(1400, 100);
	}

	//注意UIの描画
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
	//高温注意UI
	cautionHot.Render(1000, 125, MOF_ARGB((int)(255 * cautionHotB.GetAlpha()), 255, 255, 255));
	//低温注意UI
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