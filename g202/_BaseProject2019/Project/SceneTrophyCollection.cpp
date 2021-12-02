#include "SceneTrophyCollection.h"
#include "TrophyWindow.h"

CPopUpWindowBase* nowPopUpTrophy = NULL;


CSceneTrophyCollection::CSceneTrophyCollection()
{

}
CSceneTrophyCollection::~CSceneTrophyCollection()
{
	Release();
}

void CSceneTrophyCollection::PlayBGM()
{
	cSound.AllStop();
	cSound.Play(SOUND_COLLECTION_BGM);
}

void CSceneTrophyCollection::Initialize()
{
	//背景読み込み
	backGroundTex.Load("Title.png");

	page = 1;

	LoadTrophyFlg();

	//トロフィーテクスチャ読み込み
	//フラグがオンなら対応するテクスチャ、フラグがオフなら未取得テクスチャを読み込む。
	//とりあえず仮テクスチャ読み込み
	if (riverFlg)
		riverIconTexture.Load("1_川級.png");
	else
		riverIconTexture.Load("Trophy_Enpty.png");

	if(waterFallFlg)
		waterFallIconTexture.Load("2_滝級.png");
	else
		waterFallIconTexture.Load("Trophy_Enpty.png");

	if(lakeFlg)
		lakeIconTexture.Load("3_湖級.png");
	else
		lakeIconTexture.Load("Trophy_Enpty.png");

	if(damFlg)
		damIconTexture.Load("4_ダム級.png");
	else
		damIconTexture.Load("Trophy_Enpty.png");

	if(sewerFlg)
		sewerIconTexture.Load("5_下水道級.png");
	else 
		sewerIconTexture.Load("Trophy_Enpty.png");

	if(indianOceanFlg)
		indianOceanIconTexture.Load("6_インド洋級.png");
	else
		indianOceanIconTexture.Load("Trophy_Enpty.png");

	if(amazonRiverFlg)
		amazonRiverIconTexture.Load("7_アマゾン川級.png");
	else
		amazonRiverIconTexture.Load("Trophy_Enpty.png");

	if(oceanFlg)
		oceanIconTexture.Load("8_海級.png");
	else
		oceanIconTexture.Load("Trophy_Enpty.png");

	if(seaOf​​JapanFlg)
		seaOf​​JapanIconTexture.Load("9_日本海級.png");
	else
		seaOf​​JapanIconTexture.Load("Trophy_Enpty.png");

	if(aroundTheGlobeFlg)
		aroundTheGlobeIconTexture.Load("10_地球一周級.png");
	else
		aroundTheGlobeIconTexture.Load("Trophy_Enpty.png");

	if(zeroMotivationFlg)
		zeroMotivationIconTexture.Load("S1_やる気ゼロ級.png");
	else
		zeroMotivationIconTexture.Load("Trophy_Enpty.png");

	if(mountFujiFlg)
		mountFujiIconTexture.Load("S5_富士山級.png");
	else
		mountFujiIconTexture.Load("Trophy_Enpty.png");

	if(osakaMarathonFlg)
		osakaMarathonIconTexture.Load("S4_大阪マラソン級.png");
	else
		osakaMarathonIconTexture.Load("Trophy_Enpty.png");

	if(biwaLakeFlg)
		biwaLakeIconTexture.Load("S2_琵琶湖級.png");
	else
		biwaLakeIconTexture.Load("Trophy_Enpty.png");

	if(jackPodFlg)
		jackPodIconTexture.Load("S3_ジャックポット級.png");
	else
		jackPodIconTexture.Load("Trophy_Enpty.png");

	if(talentedDemonFlg)
		talentedDemonIconTexture.Load("S6_才能魔級.png");
	else
		talentedDemonIconTexture.Load("Trophy_Enpty.png");

	//ボタンテクスチャ読み込み
	menuButtonTexture.Load("ButtonMenu.png");
	rightButtonTexture.Load("ButtonRight.png");
	leftButtonTexture.Load("ButtonLeft.png");

	//背景テクスチャ読込
	backGroundTexture1.Load("TrophyPage2.png");
	backGroundTexture2.Load("TrophyPage1.png");

	//ポップアップ初期化
	popUpFlg = false;
	nowPopUpTrophy = new CTrophyWindow;
	PlayBGM();
}
void CSceneTrophyCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if ( ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		menuButtonScale = scaleController.ScaleControll(menuButtonScale,scaleMax,scaleMini,scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneTrophyCollection::Release();
		}
	}
	else
	{
		menuButtonScale = scaleMini;
	}

	//ポップアップ処理
	if (popUpFlg)
	{
		if (nowPopUpTrophy->IsEnd())
		{
			nowPopUpTrophy->Release();
			popUpFlg = false;
		}
		nowPopUpTrophy->Update();
	}
	
	if (!popUpFlg)
	{
		if (page == 1)
		{
			if (GetRect(TROPHY_RIVER).CollisionPoint(mousePosX, mousePosY))
			{
				riverScale = scaleController.ScaleControll(riverScale,scaleMax,scaleMini,scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:川級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_RIVER);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				riverScale = scaleMini;
			}
			if (GetRect(TROPHY_WATERFALL).CollisionPoint(mousePosX, mousePosY))
			{
				waterFallScale = scaleController.ScaleControll(waterFallScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:滝級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_WATERFALL);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				waterFallScale = scaleMini;
			}
			if (GetRect(TROPHY_LAKE).CollisionPoint(mousePosX, mousePosY))
			{
				lakeScale = scaleController.ScaleControll(lakeScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:湖級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_LAKE);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				lakeScale = scaleMini;
			}
			if (GetRect(TROPHY_DAM).CollisionPoint(mousePosX, mousePosY))
			{
				damScale = scaleController.ScaleControll(damScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:ダム級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_DAM);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				damScale = scaleMini;
			}
			if (GetRect(TROPHY_SEWER).CollisionPoint(mousePosX, mousePosY))
			{
				sewerScale = scaleController.ScaleControll(sewerScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:下水道級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_SEWER);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				sewerScale = scaleMini;
			}
			if (GetRect(TROPHY_INDIANOCEAN).CollisionPoint(mousePosX, mousePosY))
			{
				indianOceanScale = scaleController.ScaleControll(indianOceanScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:インド洋級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_INDIANOCEAN);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				indianOceanScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (GetRect(TROPHY_AMAZONROVER).CollisionPoint(mousePosX, mousePosY))
			{
				amazonRiverScale = scaleController.ScaleControll(amazonRiverScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:アマゾン川級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_AMAZONROVER);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				amazonRiverScale = scaleMini;
			}
			if (GetRect(TROPHY_OCEAN).CollisionPoint(mousePosX, mousePosY))
			{
				oceanScale = scaleController.ScaleControll(oceanScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:海級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_OCEAN);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				oceanScale = scaleMini;
			}
			if (GetRect(TROPHY_SEAOFJAPAN).CollisionPoint(mousePosX, mousePosY))
			{
				seaOf​​JapanScale = scaleController.ScaleControll(seaOf​​JapanScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:日本海級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_SEAOFJAPAN);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				seaOf​​JapanScale = scaleMini;
			}
			if (GetRect(TROPHY_AROUNDTHEGLOBE).CollisionPoint(mousePosX, mousePosY))
			{
				aroundTheGlobeScale = scaleController.ScaleControll(aroundTheGlobeScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:地球一周級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_AROUNDTHEGLOBE);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				aroundTheGlobeScale = scaleMini;
			}
			if (GetRect(TROPHY_ZEROMOTIVATION).CollisionPoint(mousePosX, mousePosY))
			{
				zeroMotivationScale = scaleController.ScaleControll(zeroMotivationScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:やる気ゼロ級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_ZEROMOTIVATION);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				zeroMotivationScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 1;
			}
			else if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 3;
			}
		}
		else if (page == 3)
		{
			if (GetRect(TROPHY_MOUNTFJI).CollisionPoint(mousePosX, mousePosY))
			{
				mountFujiScale = scaleController.ScaleControll(mountFujiScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:富士山級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_MOUNTFJI);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				mountFujiScale = scaleMini;
			}
			if (GetRect(TROPHY_OSAKAMARATHON).CollisionPoint(mousePosX, mousePosY))
			{
				osakaMarathonScale = scaleController.ScaleControll(osakaMarathonScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:大阪マラソンの画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_OSAKAMARATHON);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				osakaMarathonScale = scaleMini;
			}
			if (GetRect(TROPHY_BIWALAKE).CollisionPoint(mousePosX, mousePosY))
			{
				biwaLakeScale = scaleController.ScaleControll(biwaLakeScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:琵琶湖級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_BIWALAKE);
					nowPopUpTrophy->Initialize();
				}
			}
			if (GetRect(TROPHY_JACKPOD).CollisionPoint(mousePosX, mousePosY))
			{
				jackPodScale = scaleController.ScaleControll(jackPodScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:ジャックポット級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_JACKPOD);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				jackPodScale = scaleMini;
			}
			if (GetRect(TROPHY_TALENTEDDEMON).CollisionPoint(mousePosX, mousePosY))
			{
				talentedDemonScale = scaleController.ScaleControll(talentedDemonScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップにトロフィー:才能魔の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_TALENTEDDEMON);
					nowPopUpTrophy->Initialize();
				}
			}
			else
			{
				talentedDemonScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 2;
			}
		}
	}
}
void CSceneTrophyCollection::Render()
{
	backGroundTex.Render(0, 0);
	if (page == 1)
	{
		backGroundTexture1.Render(0, 0);
		//1ページ目
		scaleController.ScaleRender(&riverIconTexture, iconFirstRowPosX, iconOneLinePosY,riverScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + riverIconTexture.GetHeight() +10, "川級");
		scaleController.ScaleRender(&waterFallIconTexture, iconSecondRowPosX, iconOneLinePosY, waterFallScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + waterFallIconTexture.GetHeight() + 10, "滝級");
		scaleController.ScaleRender(&lakeIconTexture, iconThirdRowPosX, iconOneLinePosY, lakeScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + lakeIconTexture.GetHeight() + 10, "湖級");
		scaleController.ScaleRender(&damIconTexture, iconFirstRowPosX, iconTwoLinePosY, damScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY + damIconTexture.GetHeight() + 10 , "ダム級");
		scaleController.ScaleRender(&sewerIconTexture, iconSecondRowPosX, iconTwoLinePosY, sewerScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY + sewerIconTexture.GetHeight() + 10, "下水道級");
		scaleController.ScaleRender(&indianOceanIconTexture, iconThirdRowPosX, iconTwoLinePosY, indianOceanScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY + indianOceanIconTexture.GetHeight() + 10, "インド洋級");
	}
	if (page == 2)
	{
		backGroundTexture2.Render(0,0);
		//2ページ目
		scaleController.ScaleRender(&amazonRiverIconTexture, iconFirstRowPosX, iconOneLinePosY, amazonRiverScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + amazonRiverIconTexture.GetHeight() + 10, "アマゾン川級");
		scaleController.ScaleRender(&oceanIconTexture, iconSecondRowPosX, iconOneLinePosY, oceanScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + oceanIconTexture.GetHeight() + 10, "海級");
		scaleController.ScaleRender(&seaOf​​JapanIconTexture, iconThirdRowPosX, iconOneLinePosY, seaOf​​JapanScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + seaOf​​JapanIconTexture.GetHeight() + 10, "日本海級");
		scaleController.ScaleRender(&aroundTheGlobeIconTexture, icon2PageFirstRowPosX, iconTwoLinePosY, aroundTheGlobeScale);
		//CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + aroundTheGlobeIconTexture.GetHeight() + 10, "地球一周級");
		scaleController.ScaleRender(&zeroMotivationIconTexture, icon2pageSecondRowPosX, iconTwoLinePosY, zeroMotivationScale);
		//CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + zeroMotivationIconTexture.GetHeight() + 10, "やる気ゼロ級");
	}
	if (page == 3)
	{
		backGroundTexture2.Render(0, 0);
		//3ページ目
		scaleController.ScaleRender(&mountFujiIconTexture, iconFirstRowPosX, iconOneLinePosY, mountFujiScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + mountFujiIconTexture.GetHeight() + 10, "富士山級");
		scaleController.ScaleRender(&osakaMarathonIconTexture, iconSecondRowPosX, iconOneLinePosY, osakaMarathonScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + osakaMarathonIconTexture.GetHeight() + 10, "大阪マラソン級");
		scaleController.ScaleRender(&biwaLakeIconTexture, iconThirdRowPosX, iconOneLinePosY, biwaLakeScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + biwaLakeIconTexture.GetHeight() + 10, "琵琶湖級");
		scaleController.ScaleRender(&jackPodIconTexture, icon2PageFirstRowPosX, iconTwoLinePosY, jackPodScale);
		//CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + jackPodIconTexture.GetHeight() + 10, "ジャックポット級");
		scaleController.ScaleRender(&talentedDemonIconTexture, icon2pageSecondRowPosX+30, iconTwoLinePosY, talentedDemonScale);
		//CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + talentedDemonIconTexture.GetHeight() + 10, "才能魔級");
	}

	scaleController.ScaleRender(&menuButtonTexture,menuButtonPosX,menuButtonPosY,menuButtonScale);
	CGraphicsUtilities::RenderString(900, 900, "%d/3", page);
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);

	if (popUpFlg)
	{
		nowPopUpTrophy->Render();
	}
}
void CSceneTrophyCollection::Release()
{
	backGroundTex.Release();
	backGroundTexture1.Release();
	backGroundTexture2.Release();
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
	zeroMotivationIconTexture.Release();
	mountFujiIconTexture.Release();
	osakaMarathonIconTexture.Release();
	biwaLakeIconTexture.Release();
	jackPodIconTexture.Release();
	talentedDemonIconTexture.Release();

	menuButtonTexture.Release();
	if (nowPopUpTrophy != NULL)
	{
		nowPopUpTrophy->Release();
		if (nowPopUpTrophy)
		{
			delete nowPopUpTrophy;
			nowPopUpTrophy = NULL;
		}
	}
}

CRectangle CSceneTrophyCollection::GetRect(int i)
{
	// 川級
	if(i == TROPHY_RIVER && riverFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + riverIconTexture.GetWidth(), iconOneLinePosY + riverIconTexture.GetHeight());
	//滝級
	if(i ==TROPHY_WATERFALL && waterFallFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + waterFallIconTexture.GetWidth(), iconOneLinePosY + waterFallIconTexture.GetHeight());
	//湖級
	if(i == TROPHY_LAKE && lakeFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + lakeIconTexture.GetWidth(), iconOneLinePosY + lakeIconTexture.GetHeight());
	//ダム級
	if(i == TROPHY_DAM && damFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + damIconTexture.GetWidth(), iconTwoLinePosY + damIconTexture.GetHeight());
	//下水道級
	if(i == TROPHY_SEWER && sewerFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + sewerIconTexture.GetWidth(), iconTwoLinePosY + sewerIconTexture.GetHeight());
	//インド洋級
	if(i == TROPHY_INDIANOCEAN && indianOceanFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + indianOceanIconTexture.GetWidth(), iconTwoLinePosY + indianOceanIconTexture.GetHeight());

	//アマゾン川級
	if(i == TROPHY_AMAZONROVER && amazonRiverFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + amazonRiverIconTexture.GetWidth(), iconOneLinePosY + amazonRiverIconTexture.GetHeight());
	//海級
	if(i == TROPHY_OCEAN && oceanFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + oceanIconTexture.GetWidth(), iconOneLinePosY + oceanIconTexture.GetHeight());
	//日本海級
	if(i == TROPHY_SEAOFJAPAN && seaOf​​JapanFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + seaOf​​JapanIconTexture.GetWidth(), iconOneLinePosY + seaOf​​JapanIconTexture.GetHeight());
	//地球一周級
	if(i == TROPHY_AROUNDTHEGLOBE && aroundTheGlobeFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + aroundTheGlobeIconTexture.GetWidth(), iconTwoLinePosY + aroundTheGlobeIconTexture.GetHeight());
	//やる気ゼロ級
	if(i == TROPHY_ZEROMOTIVATION && zeroMotivationFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + zeroMotivationIconTexture.GetWidth(), iconTwoLinePosY + zeroMotivationIconTexture.GetHeight());

	//富士山級
	if(i == TROPHY_MOUNTFJI && mountFujiFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + mountFujiIconTexture.GetWidth(), iconOneLinePosY + mountFujiIconTexture.GetHeight());
	//大阪マラソン級
	if(i == TROPHY_OSAKAMARATHON && osakaMarathonFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX +osakaMarathonIconTexture.GetWidth(), iconOneLinePosY + osakaMarathonIconTexture.GetHeight());
	//琵琶湖級
	if(i == TROPHY_BIWALAKE && biwaLakeFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + biwaLakeIconTexture.GetWidth(), iconOneLinePosY + biwaLakeIconTexture.GetHeight());
	//ジャックポット級
	if(i == TROPHY_JACKPOD && jackPodFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + jackPodIconTexture.GetWidth(), iconTwoLinePosY + jackPodIconTexture.GetHeight());
	//才能魔級
	if(i == TROPHY_TALENTEDDEMON && talentedDemonFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + talentedDemonIconTexture.GetWidth(), iconTwoLinePosY + talentedDemonIconTexture.GetHeight());
}

CRectangle CSceneTrophyCollection::ButtonGetRect(int i)
{
	if (i == 0)
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(leftButtonPosX, leftAndRightButtonPosY, leftButtonPosX + leftButtonTexture.GetWidth(), leftAndRightButtonPosY + leftButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(rightButtonPosX, leftAndRightButtonPosY, rightButtonPosX + rightButtonTexture.GetWidth(), leftAndRightButtonPosY + rightButtonTexture.GetHeight());
}

bool CSceneTrophyCollection::GetTrophy(int i)
{
	//トロフィー:川級ゲット
	if (i == TROPHY_RIVER && !riverFlg)
	{
		riverFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:滝級ゲット
	if (i == TROPHY_WATERFALL && !waterFallFlg)
	{
		waterFallFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:湖級ゲット
	if (i == TROPHY_LAKE && !lakeFlg)
	{
		lakeFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:ダム級ゲット
	if (i == TROPHY_DAM && !damFlg)
	{
		damFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:下水道級ゲット
	if (i == TROPHY_SEWER && !sewerFlg)
	{
		sewerFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:インド洋級ゲット
	if (i == TROPHY_INDIANOCEAN && !indianOceanFlg)
	{
		indianOceanFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:アマゾン川級ゲット
	if (i == TROPHY_AMAZONROVER && !amazonRiverFlg)
	{
		amazonRiverFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:海級ゲット
	if (i == TROPHY_OCEAN && !oceanFlg)
	{
		oceanFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:日本階級ゲット
	if (i == TROPHY_SEAOFJAPAN && !seaOf​​JapanFlg)
	{
		seaOf​​JapanFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:地球一周級ゲット
	if (i == TROPHY_AROUNDTHEGLOBE && !aroundTheGlobeFlg)
	{
		aroundTheGlobeFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:やる気ゼロ級ゲット
	if (i == TROPHY_ZEROMOTIVATION && !zeroMotivationFlg)
	{
		zeroMotivationFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:富士山級ゲット
	if (i == TROPHY_MOUNTFJI && !mountFujiFlg)
	{
		mountFujiFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:大阪マラソン級ゲット
	if (i == TROPHY_OSAKAMARATHON && !osakaMarathonFlg)
	{
		osakaMarathonFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:琵琶湖級ゲット
	if (i == TROPHY_BIWALAKE && !biwaLakeFlg)
	{
		biwaLakeFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//トロフィー:ジャックポット級ゲット
	if (i == TROPHY_JACKPOD && !jackPodFlg)
	{
		jackPodFlg = true;
		SaveTrophyFlg();
		return true;
	}
	//才能魔級
	if (i == TROPHY_TALENTEDDEMON && !talentedDemonFlg)
	{
		talentedDemonFlg = true;
		SaveTrophyFlg();
		return true;
	}

	return false;
}

void CSceneTrophyCollection::SaveTrophyFlg()
{
	FILE* fp = fopen("SaveTrophy.dat", "wb");
	if (fp)
	{
		fwrite(&riverFlg, sizeof(bool), 1, fp);
		fwrite(&waterFallFlg, sizeof(bool), 1, fp);
		fwrite(&lakeFlg, sizeof(bool), 1, fp);
		fwrite(&damFlg, sizeof(bool), 1, fp);
		fwrite(&sewerFlg, sizeof(bool), 1, fp);
		fwrite(&indianOceanFlg, sizeof(bool), 1, fp);
		fwrite(&amazonRiverFlg, sizeof(bool), 1, fp);
		fwrite(&oceanFlg, sizeof(bool), 1, fp);
		fwrite(&seaOf​​JapanFlg, sizeof(bool), 1, fp);
		fwrite(&aroundTheGlobeFlg, sizeof(bool), 1, fp);
		fwrite(&zeroMotivationFlg, sizeof(bool), 1, fp);
		fwrite(&mountFujiFlg, sizeof(bool), 1, fp);
		fwrite(&osakaMarathonFlg, sizeof(bool), 1, fp);
		fwrite(&biwaLakeFlg, sizeof(bool), 1, fp);
		fwrite(&jackPodFlg, sizeof(bool), 1, fp);
		fwrite(&talentedDemonFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}

void CSceneTrophyCollection::LoadTrophyFlg()
{
	FILE* fp = fopen("SaveTrophy.dat", "rb");
	if (fp)
	{
		fread(&riverFlg, sizeof(bool), 1, fp);
		fread(&waterFallFlg, sizeof(bool), 1, fp);
		fread(&lakeFlg, sizeof(bool), 1, fp);
		fread(&damFlg, sizeof(bool), 1, fp);
		fread(&sewerFlg, sizeof(bool), 1, fp);
		fread(&indianOceanFlg, sizeof(bool), 1, fp);
		fread(&amazonRiverFlg, sizeof(bool), 1, fp);
		fread(&oceanFlg, sizeof(bool), 1, fp);
		fread(&seaOf​​JapanFlg, sizeof(bool), 1, fp);
		fread(&aroundTheGlobeFlg, sizeof(bool), 1, fp);
		fread(&zeroMotivationFlg, sizeof(bool), 1, fp);
		fread(&mountFujiFlg, sizeof(bool), 1, fp);
		fread(&osakaMarathonFlg, sizeof(bool), 1, fp);
		fread(&biwaLakeFlg, sizeof(bool), 1, fp);
		fread(&jackPodFlg, sizeof(bool), 1, fp);
		fread(&talentedDemonFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}
