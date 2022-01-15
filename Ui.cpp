#include "Ui.h"

bool CUi::Load()
{
	if (!nowPosFrameTex.Load("UI\\現在UI.png"))return false;
	if (!nextTrophyDistanceFrameTex.Load("UI\\目標UI.png"))return false;
	if (!nextTrophyFrameTex.Load("UI\\トロフィーの枠.png"))return false;
	if (!eventFrameTex.Load("UI\\イベントUI.png"))return false;

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
	if (!hungerGauge.Load("UI\\stomachGaugeOn.png"))
	{
		return false;
	}
	if (!hungerGaugeFrame.Load("UI\\stomachGaugeUnder.png"))
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

	//イベントUI
	if (!eventGarbageUI.Load("UI\\EventGarbage.png"))
	{
		return false;
	}
	if (!eventFishUI.Load("UI\\EventFish.png"))
	{
		return false;
	}
	if (!eventTurtleUI.Load("UI\\EventTurtle.png"))
	{
		return false;
	}
	if (!eventSummerUI.Load("UI\\EventSummer.png"))
	{
		return false;
	}
	if (!eventWinterUI.Load("UI\\EventWinter.png"))
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
	//フォント
	font.Load(fileAdd, fontName);
	font.Create(72, fontName);

	trophyFont.Load(fileAdd, fontName);
	trophyFont.Create(72, fontName);
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
			486,276,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},
				 {5,0,1},{5,1,1},{5,2,1},{5,3,1},
				 {5,0,2},{5,1,2},{5,2,2},{5,3,2},
		         {5,0,3},{5,1,3},{5,2,3}}
		},
		{
			"冬",
			0,0,
			306,181,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
		         {5,0,1},{5,1,1},{5,2,1},{5,3,1},{5,4,1},{5,5,1},
		         {5,0,2},{5,1,2},{5,2,2}}
		},
		{
			"亀大量発生",
			0,0,
			486,181,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},
				 {4,0,3},{4,1,3},{4,2,3}}
		},
		{
			"魚群大量発生",
			0,0,
			486,181,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},
				 {4,0,3},{4,1,3},{4,2,3}}
		},
		{
			"ごみ大量発生",
			0,0,
			486,181,
			TRUE,{{4,0,0},{4,1,0},{4,2,0},{4,3,0},
				 {4,0,1},{4,1,1},{4,2,1},{4,3,1},
				 {4,0,2},{4,1,2},{4,2,2},{4,3,2},
				 {4,0,3},{4,1,3},{4,2,3}}
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
	//間隔、幅
	constexpr int FrameSpace = 10;
	constexpr int FrameWidth = 20;
	constexpr int FrameHeight = 30;
	constexpr float ShortSpace = 4.5f;

	//フレームとトロフィーの位置
	const Vector2 torophyFrame(g_pGraphics->GetTargetWidth() - FrameSpace - nextTrophyFrameTex.GetWidth(), FrameSpace);
	const Vector2 torophyPos(torophyFrame.x + FrameWidth, torophyFrame.y + FrameHeight);

	const Vector2 torophyNowPosFrame(torophyFrame.x - FrameSpace - nowPosFrameTex.GetWidth(), FrameSpace);
	const Vector2 torophyDistanceFrame(torophyFrame.x - FrameSpace - nextTrophyDistanceFrameTex.GetWidth(), torophyNowPosFrame.y + nowPosFrameTex.GetHeight() + ShortSpace);
	const Vector2 eventFrame(torophyFrame.x - FrameSpace - eventFrameTex.GetWidth(), torophyDistanceFrame.y + nextTrophyDistanceFrameTex.GetHeight() + ShortSpace);

	//テキスト
	constexpr int torophyDistanceTextPosX = 1200;
	constexpr int torophyDistanceTextPosY = 50;
	constexpr int adjustmentTextPosX = 40;
	constexpr int adjustmentTextPosY = 30;
	constexpr int adjustmentEventTextPosX = 20;

	const Vector2 nowPosTextPos(torophyNowPosFrame.x + adjustmentTextPosX, torophyNowPosFrame.y + adjustmentTextPosY);
	const Vector2 NextTrophyTextPos(torophyNowPosFrame.x + adjustmentTextPosX, torophyDistanceFrame.y + adjustmentTextPosY);
	const Vector2 nowEventText(torophyNowPosFrame.x + adjustmentTextPosX + adjustmentEventTextPosX, eventFrame.y + adjustmentTextPosY);
	//フレームを描画
	nowPosFrameTex.Render(torophyNowPosFrame.x, torophyNowPosFrame.y);
	nextTrophyDistanceFrameTex.Render(torophyDistanceFrame.x, torophyDistanceFrame.y);
	nextTrophyFrameTex.Render(torophyFrame.x, torophyFrame.y);
	eventFrameTex.Render(eventFrame.x, eventFrame.y);

	//todo:後で消す 位置はかる用
	Vector2 mousePos;
	g_pInput->GetMousePos(mousePos);
	CGraphicsUtilities::RenderString(500, 50, MOF_COLOR_RED, "%1.0f:%1.0f", mousePos.x,mousePos.y);


	////m数表示
	if (tutorialFlg)
	{
		font.RenderFormatString(nowPosTextPos.x, nowPosTextPos.y, MOF_COLOR_BLACK, "      0 m");
	}
	else
	{
		if (distanceNum < 1000)
		{
			font.RenderFormatString(nowPosTextPos.x, nowPosTextPos.y, MOF_COLOR_BLACK, "%6.0f m", distanceNum);
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
			font.RenderFormatString(nowPosTextPos.x, nowPosTextPos.y, MOF_COLOR_BLACK, "%6.0f km", trueDis);
		}
	}

	//イベントの表示
	switch (eventNum)
	{
		case Event_None:
			font.RenderString(nowEventText.x + 50, nowEventText.y, MOF_COLOR_BLACK, "なし");
			break;
		case Event_Summer:
			//夏イベント
			if (eventPosX > 730)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 730)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}
			eventSummerUI.Render(nowEventText.x, nowEventText.y - 4);
			eventSummer.RenderScale(eventPosX, 380,0.75f, motion.GetSrcRect());
			break;
		case Event_Winter:
			//冬イベント
			if (eventPosX > 820)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 820)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}
			eventWinterUI.Render(nowEventText.x, nowEventText.y - 8);
			eventWinter.Render(eventPosX, 380, motion.GetSrcRect());
			break;
		case Event_Turtle:
			//亀大量発生イベント
			if (eventPosX > 750)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 750)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}
			eventTurtleUI.Render(nowEventText.x, nowEventText.y - 2);
			eventTurtle.Render(eventPosX, 380, motion.GetSrcRect());
			break;
		case Event_ShoalSardine:
			//魚群大量発生イベント
			if (eventPosX > 750)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 750)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}
			eventFishUI.Render(nowEventText.x, nowEventText.y - 5);
			eventShoalSardine.Render(eventPosX, 380, motion.GetSrcRect());
			break;
		case Event_Garbage:
			//ゴミ大量発生イベント
			if (eventPosX > 750)eventPosX -= EVENT_MOVE;
			else if (eventPosX <= 750)
			{
				eventTimer.StartTimer();
				if (eventTimer.GetNowtime() < 0)
				{
					eventPosX -= EVENT_MOVE;
				}
			}
			eventGarbageUI.Render(nowEventText.x, nowEventText.y - 3);
			eventGarbage.Render(eventPosX, 380, motion.GetSrcRect());
			break;
		default:
			eventPosX = 1920;
			eventTimer.SetTotalTime(3);
			break;
	}

	//現在獲得中のトロフィーと次にトロフィーを獲得できるまでの距離
	if (tutorialFlg)
	{
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "      0 m");
	}
	else if (distanceNum < RIVER)										//川級
	{
		riverIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", RIVER - distanceNum);
	}
	else if (distanceNum >= RIVER && distanceNum < WATERFALL)			//滝級
	{
		waterFallIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", WATERFALL - distanceNum);
	}
	else if (distanceNum >= WATERFALL && distanceNum < LAKE)			//湖級
	{
		lakeIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", LAKE - distanceNum);
	}
	else if (distanceNum >= LAKE && distanceNum < DAM)		//ダム級
	{
		damIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", DAM - distanceNum);
	}
	else if (distanceNum >= DAM && distanceNum < SEWER)		//下水道級
	{
		sewerIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", SEWER - distanceNum);
	}
	else if (distanceNum >= SEWER && distanceNum < INDIANOCEAN)		//インド洋級
	{
		indianOceanIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", INDIANOCEAN - distanceNum);
	}
	else if (distanceNum >= INDIANOCEAN && distanceNum < AMAZONRIVER)		//アマゾン川級
	{
		amazonRiverIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", AMAZONRIVER - distanceNum);
	}
	else if (distanceNum >= AMAZONRIVER && distanceNum < OCEAN)		//海級
	{
		oceanIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", OCEAN - distanceNum);
	}
	else if (distanceNum >= OCEAN && distanceNum < SEAOFJAPAN)		//日本海級
	{
		seaOf​​JapanIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
		trophyFont.RenderFormatString(NextTrophyTextPos.x, NextTrophyTextPos.y, MOF_COLOR_BLACK, "%6.0f m", SEAOFJAPAN - distanceNum);
	}
	else if (distanceNum >= SEAOFJAPAN)								//地球一周級
	{
		aroundTheGlobeIconTexture.RenderScale(torophyPos.x, torophyPos.y, 1.0f);
	}

	//顔のUI
	//マンボウの顔の枠
	const Vector2 stressMeterFramePos(50, 800);
	const Vector2 stressMeterPos(stressMeterFramePos.x + 14, stressMeterFramePos.y + 11);

	stressMeter.Render(stressMeterFramePos.x, stressMeterFramePos.y);

	//体温UI描画(マンボウの顔)
	if (500 * (tempRegionNum * 0.01f) <= 150)
	{
		tempHot.Render(stressMeterPos.x, stressMeterPos.y);
		//高温注意UIのフェードインスタート
		cautionHotB.SetInStart(true);
	}
	else if (500 * (tempRegionNum * 0.01f) >= 330)
	{
		tempCold.Render(stressMeterPos.x, stressMeterPos.y);
		//低温注意UIのフェードインスタート
		cautionColdB.SetInStart(true);
	}
	else
	{
		tempNormal.Render(stressMeterPos.x, stressMeterPos.y);
		cautionHotB.SetInStart(false);
		cautionColdB.SetInStart(false);
	}

	//寄生虫UIの描画
	switch (parasiteNum)
	{
	case 1:
		parasite1.Render(stressMeterFramePos.x + 22, stressMeterFramePos.y + 21);
		break;
	case 2:
		parasite2.Render(stressMeterFramePos.x + 22, stressMeterFramePos.y + 21);
		break;
	case 3:
		parasite3.Render(stressMeterFramePos.x + 22, stressMeterFramePos.y + 21);
		break;
	case 4:
		parasite4.Render(stressMeterFramePos.x + 22, stressMeterFramePos.y + 21);
		break;
	case 5:
		parasite5.Render(stressMeterFramePos.x + 22, stressMeterFramePos.y + 21);
		break;
	}

	//温度計UI描画
	const Vector2 tempMeterPos(50, 280);
	tempMeterFrame.Render(tempMeterPos.x, tempMeterPos.y);
	CRectangle rec1(0, tempMeterFrame.GetHeight() * (tempRegionNum * 0.01f), tempMeterFrame.GetWidth(), tempMeterFrame.GetHeight());
	tempMeter.Render(tempMeterPos.x, tempMeterPos.y + (tempMeterFrame.GetHeight() * (tempRegionNum * 0.01f)), rec1);

	//空腹ゲージUI描画
	const Vector2 hungerGaugePos(275, 800);
	CRectangle rec2(0, 0, hungerGaugeFrame.GetWidth(), hungerGaugeFrame.GetHeight());
	hungerGaugeFrame.Render(hungerGaugePos.x, hungerGaugePos.y, rec2);
	//空腹値の調整（表示する割合がバグる）
	if (hungry >= 100)
	{
		hungry = 100;
	}
	else if (hungry <= 0)
	{
		hungry = 0;
	}

	CRectangle rec3(0, hungerGaugeFrame.GetHeight()* (hungry * 0.01f),
					hungerGaugeFrame.GetWidth(), hungerGaugeFrame.GetHeight());
	hungerGauge.Render(hungerGaugePos.x, hungerGaugePos.y + hungerGaugeFrame.GetHeight() * (hungry * 0.01f), rec3);

	//警戒UI
	//亀注意
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
	//危険注意
	cautionUi.Render(torophyNowPosFrame.x - FrameSpace - cautionHot.GetWidth(), torophyNowPosFrame.y, MOF_ARGB((int)(255 * cautionB.GetAlpha()), 255, 255, 255));
	//高温注意
	cautionHot.Render(torophyNowPosFrame.x - FrameSpace - cautionHot.GetWidth(), torophyNowPosFrame.y, MOF_ARGB((int)(255 * cautionHotB.GetAlpha()), 255, 255, 255));
	//低温注意
	cautionCold.Render(torophyNowPosFrame.x - FrameSpace - cautionHot.GetWidth(), torophyNowPosFrame.y, MOF_ARGB((int)(255 * cautionColdB.GetAlpha()), 255, 255, 255));
}

void CUi::Release()
{
	nowPosFrameTex.Release();
	nextTrophyDistanceFrameTex.Release();
	nextTrophyFrameTex.Release();
	eventFrameTex.Release();

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