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

	//トロフィー画像
	if (!riverIconTexture.Load("1_川級.png"))
	{
		return false;
	}
	if (!waterFallIconTexture.Load("2_滝級.png"))
	{
		return false;
	}
	if (!lakeIconTexture.Load("3_湖級.png"))
	{
		return false;
	}
	if (!damIconTexture.Load("4_ダム級.png"))
	{
		return false;
	}
	if (!sewerIconTexture.Load("5_下水道級.png"))
	{
		return false;
	}
	if (!indianOceanIconTexture.Load("6_インド洋級.png"))
	{
		return false;
	}
	if (!amazonRiverIconTexture.Load("7_アマゾン川級.png"))
	{
		return false;
	}
	if (!oceanIconTexture.Load("8_海級.png"))
	{
		return false;
	}
	if (!seaOf​​JapanIconTexture.Load("9_日本海級.png"))
	{
		return false;
	}
	if (!aroundTheGlobeIconTexture.Load("10_地球一周級.png"))
	{
		return false;
	}

	//スタート開始合図
	if (!rady.Load("Rady.png"))
	{
		return false;
	}
	if (!go.Load("Go.png"))
	{
		return false;
	}

	return true;
}

void CUi::Initialize()
{
	font.Create(48, "MS　明朝");
	trophyFont.Create(24, "MS　明朝");
	//点滅設定
	//亀注意
	cautionB.SetBlinkingCount(5);
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
	//スタート合図
	radyGoB.SetBlinkingCount(2);
	radyGoB.SetBlinkingSpeed(100);
	radyGoB.Initialize();
	
	radyScale = 1.5f;
	radyPosx = 550;
	radyPosy = 350;

	goScale = 0.3f;
	goPosx = 850;
	goPosy = 450;
}

void CUi::Update()
{
	//点滅設定
	cautionB.Update();
	cautionHotB.Update();
	cautionColdB.Update();
	radyGoB.Update();
}

void CUi::Render(int parasiteNum,int hungry,float tempRegionNum,double distanceNum,bool jumpFlg,bool eatFlg, bool turtleFlg)
{
	//m数表示 枠組み
	CGraphicsUtilities::RenderFillRect(2, 2, 220, 60, MOF_COLOR_WHITE);
	CGraphicsUtilities::RenderRect(2, 2, 220, 60, MOF_COLOR_BLACK);

	if (distanceNum < 1000)
	{
		font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "%6.0f m", distanceNum);
	}
	else if (distanceNum >= 1000)
	{
		//1.1km,1.2kmのように表記
		//distance = distanceNum / 100;
		//int dis = distance;
		//double trueDis = (double)dis / 10;

		//1km,2kmのように表記
		distance = distanceNum / 1000;
		int dis = distance;
		double trueDis = (double)dis;
		font.RenderFormatString(10, 10, MOF_COLOR_BLACK, "%6.0f km", trueDis);
	}


	//次のトロフィーと距離(仮)
	if (distanceNum < 1000)										//川級
	{
		riverIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 1000 - distanceNum);
	}
	else if (distanceNum >= 1000 && distanceNum < 2500)			//滝級
	{
		waterFallIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 2500 - distanceNum);
	}
	else if (distanceNum >= 2500 && distanceNum < 5000)			//湖級
	{
		lakeIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 5000 - distanceNum);
	}
	else if (distanceNum >= 5000 && distanceNum < 10000)		//ダム級
	{
		damIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 10000 - distanceNum);
	}
	else if (distanceNum >= 10000 && distanceNum < 25000)		//下水道級
	{
		sewerIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 25000 - distanceNum);
	}
	else if (distanceNum >= 25000 && distanceNum < 50000)		//インド洋級
	{
		indianOceanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 50000 - distanceNum);
	}
	else if (distanceNum >= 50000 && distanceNum < 100000)		//アマゾン川級
	{
		amazonRiverIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 100000 - distanceNum);
	}
	else if (distanceNum >= 100000 && distanceNum < 200000)		//海級
	{
		oceanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 200000 - distanceNum);
	}
	else if (distanceNum >= 200000 && distanceNum < 300000)		//日本海級
	{
		seaOf​​JapanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", 300000 - distanceNum);
	}
	else if (distanceNum >= 300000)								//地球一周級
	{
		aroundTheGlobeIconTexture.RenderScale(220, 0, 0.75f);
	}

	//マンボウの顔の枠
	stressMeter.Render(1600, 0);

	//体温UI描画
	if (500 * (tempRegionNum * 0.01f) <= 150)
	{
		tempHot.Render(1600, 0);
		//高温注意UIのフェードインスタート
		cautionHotB.SetInStart(true);
	}
	else if (500 * (tempRegionNum * 0.01f) >= 330)
	{
		tempCold.Render(1600, 0);
		//低温注意UIのフェードインスタート
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
		jumpAlpha = 255;
	}
	else
	{
		jumpAlpha = 70;
	}
	jumpPoss.Render(1400, 0, MOF_ARGB(jumpAlpha, 255, 255, 255));
	//食事
	if (eatFlg)
	{
		eatAlpha = 255;
	}
	else
	{
		eatAlpha = 70;
	}
	eatPoss.Render(1400, 100, MOF_ARGB(eatAlpha, 255, 255, 255));

	//亀注意UIの描画
	int w = g_pGraphics->GetTargetWidth();
	int h = g_pGraphics->GetTargetHeight();
	CRectangle cautionRec(0, 0, w , h);
	if (obs.GetRect(0,0).CollisionRect(cautionRec) && turtleFlg)
	{
		cautionB.SetInStart(true);
	}
	else
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

	riverIconTexture.Release();
	waterFallIconTexture.Release();
	lakeIconTexture.Release();
	damIconTexture.Release();
	sewerIconTexture.Release();
	indianOceanIconTexture.Release();
	amazonRiverIconTexture.Release();
	oceanIconTexture.Release();
	seaOf​​JapanIconTexture.Release();
	aroundTheGlobeIconTexture.Release();

	rady.Release();
	go.Release();

	font.Release();
}

bool CUi::StartSign()
{
	radyGoB.SetInStart(true);

	radyScale -= 0.01f;
	radyPosx += 2.5f;
	radyPosy += 1.0f;

	goScale += 0.01f;
	goPosx -= 2.0f;
	goPosy -= 1.0f;

	switch (radyGoB.GetCount())
	{
	case 0:
		rady.RenderScale(radyPosx, radyPosy,radyScale,
			MOF_ARGB((int)(255 * radyGoB.GetAlpha()), 255,255,255));
		break;
	case 1:
		go.RenderScale(goPosx, goPosy,goScale,
			MOF_ARGB((int)(255 * radyGoB.GetAlpha()), 255,255,255));
		return true;
		break;
	}	
	return false;
}