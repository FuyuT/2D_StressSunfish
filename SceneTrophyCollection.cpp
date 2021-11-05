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

	//ポップアップ初期化
	popUpFlg = false;
	nowPopUpTrophy = new CTrophyWindow;
	nowPopUpTrophy->Initialize();
}
void CSceneTrophyCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTrophyCollection::Release();
	}

	//ポップアップ処理
	if (popUpFlg)
	{
		if (nowPopUpTrophy->IsEnd())
		{
			nowPopUpTrophy->Release();
			popUpFlg = false;
		}
		nowPopUpTrophy->Initialize();
		nowPopUpTrophy->Update();
	}
	
	if (!popUpFlg)
	{
		if (page == 1)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_RIVER).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:川級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_RIVER);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_WATERFALL).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:滝級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_WATERFALL);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_LAKE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:湖級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_LAKE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_DAM).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:ダム級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_DAM);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEWER).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:下水道級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_SEWER);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_INDIANOCEAN).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:インド洋級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_INDIANOCEAN);
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_AMAZONROVER).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:アマゾン川級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_AMAZONROVER);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OCEAN).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:海級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_OCEAN);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEAOFJAPAN).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:日本海級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_SEAOFJAPAN);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_AROUNDTHEGLOBE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:地球一周級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_AROUNDTHEGLOBE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_ZEROMOTIVATION).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:やる気ゼロ級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_ZEROMOTIVATION);
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
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_MOUNTFJI).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:富士山級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_MOUNTFJI);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OSAKAMARATHON).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:大阪マラソンの画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_OSAKAMARATHON);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_BIWALAKE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:琵琶湖級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_BIWALAKE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_JACKPOD).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:ジャックポット級の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_JACKPOD);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_TALENTEDDEMON).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップにトロフィー:才能魔の画像を表示させる
				nowPopUpTrophy->SetButtonResult(TROPHY_TALENTEDDEMON);
			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 2;
			}
		}
	}
	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
}
void CSceneTrophyCollection::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
	if (page == 1)
	{
		//1ページ目
		riverIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + riverIconTexture.GetHeight() +10, "川級");
		waterFallIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + waterFallIconTexture.GetHeight() + 10, "滝級");
		lakeIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + lakeIconTexture.GetHeight() + 10, "湖級");
		damIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY + damIconTexture.GetHeight() + 10 , "ダム級");
		sewerIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY + sewerIconTexture.GetHeight() + 10, "下水道級");
		indianOceanIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY + indianOceanIconTexture.GetHeight() + 10, "インド洋級");
	}
	if (page == 2)
	{
		//2ページ目
		amazonRiverIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + amazonRiverIconTexture.GetHeight() + 10, "アマゾン川級");
		oceanIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + oceanIconTexture.GetHeight() + 10, "海級");
		seaOf​​JapanIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + seaOf​​JapanIconTexture.GetHeight() + 10, "日本海級");
		aroundTheGlobeIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + aroundTheGlobeIconTexture.GetHeight() + 10, "地球一周級");
		zeroMotivationIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + zeroMotivationIconTexture.GetHeight() + 10, "やる気ゼロ級");
	}
	if (page == 3)
	{
		//3ページ目
		mountFujiIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + mountFujiIconTexture.GetHeight() + 10, "富士山級");
		osakaMarathonIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + osakaMarathonIconTexture.GetHeight() + 10, "大阪マラソン級");
		biwaLakeIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + biwaLakeIconTexture.GetHeight() + 10, "琵琶湖級");
		jackPodIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + jackPodIconTexture.GetHeight() + 10, "ジャックポット級");
		talentedDemonIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + talentedDemonIconTexture.GetHeight() + 10, "才能魔級");
	}

	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
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
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_RIVER;
		}
		return true;
	}
	//トロフィー:滝級ゲット
	if (i == TROPHY_WATERFALL && !waterFallFlg)
	{
		waterFallFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_WATERFALL;
		}
		return true;
	}
	//トロフィー:湖級ゲット
	if (i == TROPHY_LAKE && !lakeFlg)
	{
		lakeFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_LAKE;
		}
		return true;
	}
	//トロフィー:ダム級ゲット
	if (i == TROPHY_DAM && !damFlg)
	{
		damFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_DAM;
		}
		return true;
	}
	//トロフィー:下水道級ゲット
	if (i == TROPHY_SEWER && !sewerFlg)
	{
		sewerFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_SEWER;
		}
		return true;
	}
	//トロフィー:インド洋級ゲット
	if (i == TROPHY_INDIANOCEAN && !indianOceanFlg)
	{
		indianOceanFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_INDIANOCEAN;
		}
		return true;
	}
	//トロフィー:アマゾン川級ゲット
	if (i == TROPHY_AMAZONROVER && !amazonRiverFlg)
	{
		amazonRiverFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_AMAZONROVER;
		}
		return true;
	}
	//トロフィー:海級ゲット
	if (i == TROPHY_OCEAN && !oceanFlg)
	{
		oceanFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_OCEAN;
		}
		return true;
	}
	//トロフィー:日本階級ゲット
	if (i == TROPHY_SEAOFJAPAN && !seaOf​​JapanFlg)
	{
		seaOf​​JapanFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_SEAOFJAPAN;
		}
		return true;
	}
	//トロフィー:地球一周級ゲット
	if (i == TROPHY_AROUNDTHEGLOBE && !aroundTheGlobeFlg)
	{
		aroundTheGlobeFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_AROUNDTHEGLOBE;
		}
		return true;
	}
	//トロフィー:やる気ゼロ級ゲット
	if (i == TROPHY_ZEROMOTIVATION && !zeroMotivationFlg)
	{
		zeroMotivationFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_ZEROMOTIVATION;
		}
		return true;
	}
	//トロフィー:富士山級ゲット
	if (i == TROPHY_MOUNTFJI && !mountFujiFlg)
	{
		mountFujiFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_MOUNTFJI;
		}
		return true;
	}
	//トロフィー:大阪マラソン級ゲット
	if (i == TROPHY_OSAKAMARATHON && !osakaMarathonFlg)
	{
		osakaMarathonFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_OSAKAMARATHON;
		}
		return true;
	}
	//トロフィー:琵琶湖級ゲット
	if (i == TROPHY_BIWALAKE && !biwaLakeFlg)
	{
		biwaLakeFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_BIWALAKE;
		}
		return true;
	}
	//トロフィー:ジャックポット級ゲット
	if (i == TROPHY_JACKPOD && !jackPodFlg)
	{
		jackPodFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_JACKPOD;
		}
		return true;
	}
	//才能魔級
	if (i == TROPHY_TALENTEDDEMON && !talentedDemonFlg)
	{
		talentedDemonFlg = true;
		SaveTrophyFlg();
		for (int i = 0; i < 3; i++)
		{
			if (*numberOfTrophy[i] == NULL)
				*numberOfTrophy[i] = TROPHY_TALENTEDDEMON;
		}
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
