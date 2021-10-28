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

	return true;
}

void CUi::Initialize()
{
	Load();

	////タイマー
	//tempTimer.SetTotalTime(2);
	//hungerTimer.SetTotalTime(3);
	//parasiteTimer.SetTotalTime(15);
}

void CUi::Update()
{
	////タイマー
	//tempTimer.Update();
	//hungerTimer.Update();
	//parasiteTimer.Update();

}

void CUi::Render(int parasiteNum,int hungry,int bodyTempNum, float tempRegionNum)
{
	stressMeter.Render(1600, 0);

	//体温UI描画
	if (bodyTempNum >= 40)
	{
		tempHot.Render(1600, 0);
	}
	else if (bodyTempNum <= -20)
	{
		tempCold.Render(1600, 0);
	}
	else
	{
		tempNormal.Render(1600, 0);
	}

	//温度計UI描画
	tempMeterFrame.Render(1550, 200);
	CRectangle rec1(0, tempRegionNum, 500, 500);
	tempMeter.Render(1550, 200 + tempRegionNum, rec1);

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
	CRectangle rec3(0, hungry, 330, 200);
	hungerGauge.Render(1400, hungry, rec3);
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
}