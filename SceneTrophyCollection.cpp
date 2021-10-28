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
	page = 1;
	//トロフィーテクスチャ読み込み
	//フラグがオンなら対応するテクスチャ、フラグがオフなら未取得テクスチャを読み込む。
	//とりあえず仮テクスチャ読み込み
	if (riverFlg)
		riverIconTexture.Load("Trophy.png");
	else
		riverIconTexture.Load("Trophy_Enpty.png");

	if(waterFallFlg)
		waterFallIconTexture.Load("Trophy.png");
	else
		waterFallIconTexture.Load("Trophy_Enpty.png");

	if(lakeFlg)
		lakeIconTexture.Load("Trophy.png");
	else
		lakeIconTexture.Load("Trophy_Enpty.png");

	if(damFlg)
		damIconTexture.Load("Trophy.png");
	else
		damIconTexture.Load("Trophy_Enpty.png");

	if(sewerFlg)
		sewerIconTexture.Load("Trophy.png");
	else 
		sewerIconTexture.Load("Trophy_Enpty.png");

	if(indianOceanFlg)
		indianOceanIconTexture.Load("Trophy.png");
	else
		indianOceanIconTexture.Load("Trophy_Enpty.png");

	if(amazonRiverFlg)
		amazonRiverIconTexture.Load("Trophy.png");
	else
		amazonRiverIconTexture.Load("Trophy_Enpty.png");

	if(oceanFlg)
		oceanIconTexture.Load("Trophy.png");
	else
		oceanIconTexture.Load("Trophy_Enpty.png");

	if(seaOf​​JapanFlg)
		seaOf​​JapanIconTexture.Load("Trophy.png");
	else
		seaOf​​JapanIconTexture.Load("Trophy_Enpty.png");

	if(aroundTheGlobeFlg)
		aroundTheGlobeIconTexture.Load("Trophy.png");
	else
		aroundTheGlobeIconTexture.Load("Trophy_Enpty.png");

	if(zeroMotivationFlg)
		zeroMotivationIconTexture.Load("Trophy.png");
	else
		zeroMotivationIconTexture.Load("Trophy_Enpty.png");

	if(mountFujiFlg)
		mountFujiIconTexture.Load("Trophy.png");
	else
		mountFujiIconTexture.Load("Trophy_Enpty.png");

	if(osakaMarathonFlg)
		osakaMarathonIconTexture.Load("Trophy.png");
	else
		osakaMarathonIconTexture.Load("Trophy_Enpty.png");

	if(biwaLakeFlg)
		biwaLakeIconTexture.Load("Trophy.png");
	else
		biwaLakeIconTexture.Load("Trophy_Enpty.png");

	if(jackPodFlg)
		jackPodIconTexture.Load("Trophy.png");
	else
		jackPodIconTexture.Load("Trophy_Enpty.png");

	if(talentedDemonFlg)
		talentedDemonIconTexture.Load("Trophy.png");
	else
		talentedDemonIconTexture.Load("Trophy_Enpty.png");

	menuButtonTexture.Load("ButtonMenu.png");
	popUpFlg = false;
	nowPopUpTrophy = new CTrophyWindow;
	nowPopUpTrophy->Initialize();
}
void CSceneTrophyCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTrophyCollection::Release();
	}
	if (popUpFlg)
	{
		if (nowPopUpTrophy->IsEnd())
		{
			popUpFlg = false;
		}
		nowPopUpTrophy->Initialize();
		nowPopUpTrophy->Update();
	}
	if (page == 1)
	{
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_RIVER).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:川級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_WATERFALL).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:滝級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_LAKE).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:湖級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_DAM).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:ダム級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEWER).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:下水道級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_INDIANOCEAN).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:インド洋級の画像を表示させる

		}

		if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
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

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OCEAN).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:海級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEAOFJAPAN).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:日本海級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_AROUNDTHEGLOBE).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:地球一周級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_ZEROMOTIVATION).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:やる気ゼロ級の画像を表示させる

		}

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			page = 1;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
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

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OSAKAMARATHON).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:大阪マラソンの画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_BIWALAKE).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:琵琶湖級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_JACKPOD).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:ジャックポット級の画像を表示させる

		}
		else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_TALENTEDDEMON).CollisionPoint(mousePosX, mousePosY))
		{
			popUpFlg = true;
			//ポップアップにトロフィー:才能魔の画像を表示させる

		}

		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			page = 2;
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
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
	if (page == 1)
	{
		riverIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		waterFallIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		lakeIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		damIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		sewerIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		indianOceanIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
	}
	if (page == 2)
	{
		amazonRiverIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		oceanIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		seaOf​​JapanIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		aroundTheGlobeIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		zeroMotivationIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
	}
	if (page == 3)
	{
		mountFujiIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		osakaMarathonIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		biwaLakeIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		jackPodIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		talentedDemonIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
	}
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	if (popUpFlg)
	{
		nowPopUpTrophy->Render();
	}
}
void CSceneTrophyCollection::Release()
{
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
	nowPopUpTrophy->Release();
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