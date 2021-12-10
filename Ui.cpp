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

	//イベント
	if (!eventSummer.Load("sheet_anim5_anim5_anime_1.png"))
	{
		return false;
	}
	if (!eventWinter.Load("sheet_anim4_anim4_anime_1.png"))
	{
		return false;
	}
	if (!eventTurtle.Load("sheet_anim3_anim3_anime_1.png"))
	{
		return false;
	}
	if (!eventShoalSardine.Load("sheet_anim1_anim1_anime_1.png"))
	{
		return false;
	}
	if (!eventGarbage.Load("sheet_anim2_anim2_anime_1.png"))
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
	radyGoB.SetBlinkingCount(1);
	radyGoB.SetBlinkingSpeed(100);
	radyGoB.Initialize();

	//タイマー設定
	eventTimer.SetTotalTime(3);

	//イベントアニメーション
	SpriteAnimationCreate anim[] = {
		{
			"夏",
			0,0,
			131,68,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},
				 {5,0,1},{5,1,1},{5,2,1},{5,3,1},{5,4,1},{5,5,1},{5,6,1},
		         {5,0,2}}
		},
		{
			"冬",
			0,0,
			106,81,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0},{5,8,0},
				 {5,0,1},{5,1,1},{5,2,1},{5,3,1},{5,4,1},{5,5,1}}
		},
		{
			"亀大量発生",
			0,0,
			218,81,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},
				 {4,0,3},{4,1,3},{4,2,3}}
		},
		{
			"魚群大量発生",
			0,0,
			200,62,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2}}
		},
		{
			"ごみ大量発生",
			0,0,
			200,62,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},{4,4,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},{4,4,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},{4,4,2}}
		},
	};
	motion.Create(anim, EVENTMOTION_COUNT);
	
	//スタート合図初期化
	radyAlpha = 255;
	radyScale = 1.5f;
	radyPosx = 550;
	radyPosy = 350;

	goScale = 1.0f;
	goPosx = 700;
	goPosy = 370;
}

void CUi::Update(int eventNum)
{
	//点滅設定
	cautionB.Update();
	cautionHotB.Update();
	cautionColdB.Update();
	radyGoB.Update();

	//タイマー
	eventTimer.Update();

	//イベントアニメーション
	switch (eventNum)
	{
	case Event_Summer:
		//夏
		motion.ChangeMotion(EVENTMOTION_SUMMER, false);
		break;
	case Event_Winter:
		//冬
		motion.ChangeMotion(EVENTMOTION_WINTER, false);
		break;
	case Event_Turtle:
		//亀大量発生
		motion.ChangeMotion(EVENTMOTION_TURTLE, false);
		break;
	case Event_ShoalSardine:
		//魚群大量発生
		motion.ChangeMotion(EVENTMOTION_SHOALSARDINE, false);
		break;
	case Event_Garbage:
		//ゴミ大量発生
		motion.ChangeMotion(EVENTMOTION_GARBAGE, false);
		break;
	default:
		break;
	}
	motion.AddTimer(CUtilities::GetFrameSecond());
}

void CUi::Render(int parasiteNum, int hungry, float tempRegionNum, double distanceNum, bool jumpFlg, bool eatFlg, bool tutorialFlg,int eventNum)
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
	}

	//イベントの表示
	// 
	//todo:画像に変える、動きを持たす
	//今は仮として「○○イベント」という文字を表示している
	switch (eventNum)
	{
		case Event_Summer:
			//夏イベント
			if (eventPosX > 850)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 850)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}

			eventSummer.RenderScale(eventPosX, 450, 1.5f, motion.GetSrcRect());
			break;
		case Event_Winter:
			//冬イベント
			if (eventPosX > 870)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 870)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}

			eventWinter.RenderScale(eventPosX, 450, 1.5f, motion.GetSrcRect());
			break;
		case Event_Turtle:
			//亀大量発生イベント
			if (eventPosX > 800)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 800)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}

			eventTurtle.RenderScale(eventPosX, 450, 1.5f, motion.GetSrcRect());
			break;
		case Event_ShoalSardine:
			//魚群大量発生イベント
			if (eventPosX > 800)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 800)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}

			eventShoalSardine.RenderScale(eventPosX, 450, 1.5f, motion.GetSrcRect());
			break;
		case Event_Garbage:
			//ゴミ大量発生イベント
			if (eventPosX > 800)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 800)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}

			eventGarbage.RenderScale(eventPosX, 450, 1.5f, motion.GetSrcRect());
			break;
		default:
			eventPosX = 1920;
			eventTimer.SetTotalTime(3);
			break;
	}


	//現在獲得中のトロフィーと次にトロフィーを獲得できるまでの距離
	if (tutorialFlg)
	{
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと━━ m");
	}
	else if (distanceNum < RIVER)										//川級
	{
		riverIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", RIVER - distanceNum);
	}
	else if (distanceNum >= RIVER && distanceNum < WATERFALL)			//滝級
	{
		waterFallIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", WATERFALL - distanceNum);
	}
	else if (distanceNum >= WATERFALL && distanceNum < LAKE)			//湖級
	{
		lakeIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", LAKE - distanceNum);
	}
	else if (distanceNum >= LAKE && distanceNum < DAM)		//ダム級
	{
		damIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", DAM - distanceNum);
	}
	else if (distanceNum >= DAM && distanceNum < SEWER)		//下水道級
	{
		sewerIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", SEWER - distanceNum);
	}
	else if (distanceNum >= SEWER && distanceNum < INDIANOCEAN)		//インド洋級
	{
		indianOceanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", INDIANOCEAN - distanceNum);
	}
	else if (distanceNum >= INDIANOCEAN && distanceNum < AMAZONRIVER)		//アマゾン川級
	{
		amazonRiverIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", AMAZONRIVER - distanceNum);
	}
	else if (distanceNum >= AMAZONRIVER && distanceNum < OCEAN)		//海級
	{
		oceanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", OCEAN - distanceNum);
	}
	else if (distanceNum >= OCEAN && distanceNum < SEAOFJAPAN)		//日本海級
	{
		seaOf​​JapanIconTexture.RenderScale(220, 0, 0.75f);
		trophyFont.RenderFormatString(380, 0, MOF_COLOR_BLACK, "次のトロフィー\n獲得まであと%6.0f m", SEAOFJAPAN - distanceNum);
	}
	else if (distanceNum >= SEAOFJAPAN)								//地球一周級
	{
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
		jumpAlpha = MAX_ALPHA;
	}
	else
	{
		jumpAlpha = TIN_ALPHA;
	}
	jumpPoss.Render(1400, 0, MOF_ARGB(jumpAlpha, 255, 255, 255));
	//食事
	if (eatFlg)
	{
		eatAlpha = MAX_ALPHA;
	}
	else
	{
		eatAlpha = TIN_ALPHA;
	}
	eatPoss.Render(1400, 100, MOF_ARGB(eatAlpha, 255, 255, 255));

	//亀注意UIの描画
	int w = g_pGraphics->GetTargetWidth();
	if (turtle.GetShow())
	{
		if (w - w / 4 >= turtle.GetPosX())
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

	eventSummer.Release();
	eventWinter.Release();
	eventTurtle.Release();
	eventShoalSardine.Release();
	eventGarbage.Release();

	motion.Release();

	rady.Release();
	go.Release();

	font.Release();
}

bool CUi::StartSign(bool pose)
{
	if (!pose)
	{
		if (radyAlpha > 0)
		{
			radyScale -= 0.01f;
			radyPosx += 2.5f;
			radyPosy += 1.0f;
			radyAlpha -= 2.55f;

			rady.RenderScale(radyPosx, radyPosy, radyScale,
				MOF_ARGB((int)radyAlpha, 255, 255, 255));
		}
		else if (radyAlpha <= 0)
		{
			goScale += 0.01f;
			goPosx -= 2.0f;
			goPosy -= 1.0f;

			radyGoB.SetInStart(true);
			go.RenderScale(goPosx, goPosy, goScale,
				MOF_ARGB((int)(255 * radyGoB.GetAlpha()), 255, 255, 255));
			return true;
		}
	}
	return false;
}