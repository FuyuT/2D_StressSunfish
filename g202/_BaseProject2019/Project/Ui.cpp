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
	font.Create(48, "MS　明朝");
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

void CUi::RenderNumber(int x,int num)
{
	switch (num)
	{
		case 0:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "0");
			break;
		case 1:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "1");
			break;
		case 2:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "2");
			break;
		case 3:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "3");
			break;
		case 4:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "4");
			break;
		case 5:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "5");
			break;
		case 6:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "6");
			break;
		case 7:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "7");
			break;
		case 8:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "8");
			break;
		case 9:
			font.RenderString(x, 10, MOF_COLOR_BLACK, "9");
			break;
	}
}

void CUi::Render(int parasiteNum,int hungry,int bodyTempNum, float tempRegionNum,int distanceNum)
{
	//m数表示 枠組み
	CGraphicsUtilities::RenderFillRect(2, 2, 220, 60, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderRect(2, 2, 220, 60, MOF_COLOR_BLACK);

	//m数表示 数字
	int headFlg = false;
	int num = distanceNum;
	if (num / 100000 != 0 || headFlg)
	{
		RenderNumber(10, num / 100000);
		headFlg = true;
	}
	num = num % 100000;
	if (num / 10000 != 0 || headFlg)
	{
		RenderNumber(35, num / 10000);
		headFlg = true;
	}
	num = num % 10000;
	if (num / 1000 != 0 || headFlg)
	{
		RenderNumber(60, num / 1000);
		headFlg = true;
	}
	num = num % 1000;
	if (num / 100 != 0 || headFlg)
	{
		RenderNumber(85, num / 100);
		headFlg = true;
	}
	num = num % 100;
	if (num / 10 != 0 || headFlg)
	{
		RenderNumber(110, num / 10);
		headFlg = true;
	}
	if (num % 10 != 0 || headFlg)
	{
		RenderNumber(135, num % 10);
		headFlg = true;
	}
	//m数表示 m
	font.RenderString(160, 10,MOF_COLOR_BLACK, " m");
	//CGraphicsUtilities::RenderString(160, 10, MOF_COLOR_BLACK, "%d", num);
	//font.RenderString(160, 10, MOF_COLOR_BLACK, "%d");

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
	font.Release();
}