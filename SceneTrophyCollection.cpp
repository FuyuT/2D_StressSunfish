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
	cSound->BGMStop();
	cSound->Play(SOUND_COLLECTION_BGM);
}

void CSceneTrophyCollection::Initialize()
{
	//背景読み込み
	backGroundTex.Load("Title.png");

	page = 1;

	//フォント
	font.Load(fontAdd, fontName);
	font.Create(64, fontName);

	LoadTrophyFlg();

	//トロフィーテクスチャ読み込み
	//フラグがオンなら対応するテクスチャ、フラグがオフなら未取得テクスチャを読み込む。
	//とりあえず仮テクスチャ読み込み
	if (riverFlg)
		riverIconTexture.Load("1_川級.png");

	if(waterFallFlg)
		waterFallIconTexture.Load("2_滝級.png");
	
	if(lakeFlg)
		lakeIconTexture.Load("3_湖級.png");

	if(damFlg)
		damIconTexture.Load("4_ダム級.png");

	if(sewerFlg)
		sewerIconTexture.Load("5_下水道級.png");

	if(indianOceanFlg)
		indianOceanIconTexture.Load("6_インド洋級.png");

	if(amazonRiverFlg)
		amazonRiverIconTexture.Load("7_アマゾン川級.png");

	if(oceanFlg)
		oceanIconTexture.Load("8_海級.png");

	if(seaOf​​JapanFlg)
		seaOf​​JapanIconTexture.Load("9_日本海級.png");

	if(aroundTheGlobeFlg)
		aroundTheGlobeIconTexture.Load("10_地球一周級.png");

	if(zeroMotivationFlg)
		zeroMotivationIconTexture.Load("S1_やる気ゼロ級.png");

	if(mountFujiFlg)
		mountFujiIconTexture.Load("S5_富士山級.png");

	if(osakaMarathonFlg)
		osakaMarathonIconTexture.Load("S4_大阪マラソン級.png");

	if(biwaLakeFlg)
		biwaLakeIconTexture.Load("S2_琵琶湖級.png");

	if(jackPodFlg)
		jackPodIconTexture.Load("S3_ジャックポット級.png");

	if(talentedDemonFlg)
		talentedDemonIconTexture.Load("S6_才能魔級.png");
	

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
	nowPopUpTrophy->SetSoundManager(*cSound);

	PlayBGM();

	//選択初期化
	if (riverFlg)
		buttonSelect = 1;
	else if (waterFallFlg)
		buttonSelect = 2;
	else if (lakeFlg)
		buttonSelect = 3;
	else if (damFlg)
		buttonSelect = 4;
	else if (sewerFlg)
		buttonSelect = 5;
	else if (indianOceanFlg)
		buttonSelect = 6;
	else
		buttonSelect = 0;

	bubbleFade.Load();
	bubbleFade.Initialize();
}



void CSceneTrophyCollection::Update()
{
	//フェード処理
	bubbleFade.Update();
	bubbleFade.FadeIn();
	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		//シーンの遷移
		endFlg = true;
		nextScene = nextSceneTemp;
		CSceneTrophyCollection::Release();
		return;
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

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (!popUpFlg)
	{
		MouseCollision(mousePosX, mousePosY);
		if (page == 1)
		{
			if (buttonSelect == 0)
			{
				riverScale = scaleMini;
				waterFallScale = scaleMini;
				damScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleMini;
				indianOceanScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (damFlg)
						buttonSelect = 4;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else if (riverFlg)
						buttonSelect = 1;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (lakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (riverFlg)
						buttonSelect = 1;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (lakeFlg)
						buttonSelect = 3;
					else if (damFlg)
						buttonSelect = 4;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneTrophyCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				riverScale = scaleController.ScaleControll(riverScale, scaleMax, scaleMini, scaleSpeed);
				waterFallScale = scaleMini;
				damScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleMini;
				indianOceanScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (damFlg)
						buttonSelect = 4;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else
						buttonSelect = 0;

				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFallFlg)
						buttonSelect = 2;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (lakeFlg)
						buttonSelect = 3;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else
					{
						page = 2;
						if (amazonRiverFlg)
							buttonSelect = 1;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else
							buttonSelect = 0;
					}
					buttonSelect = 2;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_RIVER).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:川級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_RIVER);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				riverScale = scaleMini;
				damScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleMini;
				indianOceanScale = scaleMini;
				waterFallScale = scaleController.ScaleControll(waterFallScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = scaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (sewerFlg)
						buttonSelect = 5;
					else if (damFlg)
						buttonSelect = 4;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (riverFlg)
						buttonSelect = 1;
					else if (damFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lakeFlg)
						buttonSelect = 3;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else
					{
						page = 2;
						if (amazonRiverFlg)
							buttonSelect = 1;
						else if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_WATERFALL).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:滝級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_WATERFALL);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				riverScale = scaleMini;
				damScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleController.ScaleControll(lakeScale, scaleMax, scaleMini, scaleSpeed);
				indianOceanScale = scaleMini;
				waterFallScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (indianOceanFlg)
						buttonSelect = 6;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (damFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFallFlg)
						buttonSelect = 2;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (riverFlg)
						buttonSelect = 1;
					else if (damFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (amazonRiverFlg)
						buttonSelect = 1;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_LAKE).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:湖級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_LAKE);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				riverScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleMini;
				damScale = scaleController.ScaleControll(damScale, scaleMax, scaleMini, scaleSpeed);
				indianOceanScale = scaleMini;
				waterFallScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (riverFlg)
						buttonSelect = 1;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (lakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (sewerFlg)
						buttonSelect = 5;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else if (lakeFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (amazonRiverFlg)
							buttonSelect = 1;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_DAM).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:ダム級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_DAM);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 5)
			{
				riverScale = scaleMini;
				sewerScale = scaleController.ScaleControll(sewerScale, scaleMax, scaleMini, scaleSpeed);
				lakeScale = scaleMini;
				damScale = scaleMini;
				indianOceanScale = scaleMini;
				waterFallScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFallFlg)
						buttonSelect = 2;
					else if (riverFlg)
						buttonSelect = 1;
					else if (lakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (damFlg)
						buttonSelect = 4;
					else if (riverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (indianOceanFlg)
						buttonSelect = 6;
					else if (lakeFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (amazonRiverFlg)
							buttonSelect = 1;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEWER).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:下水道級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_SEWER);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 6)
			{
				riverScale = scaleMini;
				sewerScale = scaleMini;
				lakeScale = scaleMini;
				damScale = scaleMini;
				indianOceanScale = scaleController.ScaleControll(indianOceanScale, scaleMax, scaleMini, scaleSpeed);
				waterFallScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lakeFlg)
						buttonSelect = 3;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (riverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (sewerFlg)
						buttonSelect = 5;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (damFlg)
						buttonSelect = 4;
					else if (riverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;

				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_INDIANOCEAN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:インド洋級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_INDIANOCEAN);
					nowPopUpTrophy->Initialize();
				}
			}

			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 1;
				page = 2;
			}

		}
		else if (page == 2)
		{
			if (buttonSelect == 0)
			{
				amazonRiverScale = scaleMini;
				oceanScale = scaleMini;
				seaOf​​JapanScale = scaleMini;
				aroundTheGlobeScale = scaleMini;
				zeroMotivationScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (amazonRiverFlg)
						buttonSelect = 1;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneTrophyCollection::Release();
				}
			}
			if (buttonSelect == 1)
			{
				amazonRiverScale = scaleController.ScaleControll(amazonRiverScale, scaleMax, scaleMini, scaleSpeed);
				oceanScale = scaleMini;
				seaOf​​JapanScale = scaleMini;
				aroundTheGlobeScale = scaleMini;
				zeroMotivationScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (lakeFlg)
						buttonSelect = 3;
					else if (indianOceanFlg)
						buttonSelect = 6;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (riverFlg)
						buttonSelect = 1;
					else if (damFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (oceanFlg)
						buttonSelect = 2;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else
					{
						page = 3;
						if (mountFujiFlg)
							buttonSelect = 1;
						else if (jackPodFlg)
							buttonSelect = 4;
						else if (osakaMarathonFlg)
							buttonSelect = 2;
						else if (talentedDemonFlg)
							buttonSelect = 5;
						else if (biwaLakeFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}

				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_AMAZONROVER).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:アマゾン川級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_AMAZONROVER);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				amazonRiverScale = scaleMini;
				oceanScale = scaleController.ScaleControll(oceanScale, scaleMax, scaleMini, scaleSpeed);
				seaOf​​JapanScale = scaleMini;
				aroundTheGlobeScale = scaleMini;
				zeroMotivationScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (amazonRiverFlg)
						buttonSelect = 1;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else
					{
						page = 1;
						if (lakeFlg)
							buttonSelect = 3;
						else if (indianOceanFlg)
							buttonSelect = 6;
						else if (waterFallFlg)
							buttonSelect = 2;
						else if (sewerFlg)
							buttonSelect = 5;
						else if (riverFlg)
							buttonSelect = 1;
						else if (damFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else
					{
						page = 3;
						if (mountFujiFlg)
							buttonSelect = 1;
						else if (jackPodFlg)
							buttonSelect = 4;
						else if (osakaMarathonFlg)
							buttonSelect = 2;
						else if (talentedDemonFlg)
							buttonSelect = 5;
						else if (biwaLakeFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OCEAN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:海級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_OCEAN);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				amazonRiverScale = scaleMini;
				oceanScale = scaleMini;
				seaOf​​JapanScale = scaleController.ScaleControll(seaOf​​JapanScale, scaleMax, scaleMini, scaleSpeed);
				aroundTheGlobeScale = scaleMini;
				zeroMotivationScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (oceanFlg)
						buttonSelect = 2;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else
					{
						page = 1;
						if (lakeFlg)
							buttonSelect = 3;
						else if (indianOceanFlg)
							buttonSelect = 6;
						else if (waterFallFlg)
							buttonSelect = 2;
						else if (sewerFlg)
							buttonSelect = 5;
						else if (riverFlg)
							buttonSelect = 1;
						else if (damFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (mountFujiFlg)
						buttonSelect = 1;
					else if (jackPodFlg)
						buttonSelect = 4;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_SEAOFJAPAN).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:日本海級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_SEAOFJAPAN);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				amazonRiverScale = scaleMini;
				oceanScale = scaleMini;
				seaOf​​JapanScale = scaleMini;
				aroundTheGlobeScale = scaleController.ScaleControll(aroundTheGlobeScale, scaleMax, scaleMini, scaleSpeed);
				zeroMotivationScale = scaleMini;
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (amazonRiverFlg)
						buttonSelect = 1;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (indianOceanFlg)
						buttonSelect = 6;
					if (lakeFlg)
						buttonSelect = 3;
					else if (sewerFlg)
						buttonSelect = 5;
					else if (waterFallFlg)
						buttonSelect = 2;
					else if (damFlg)
						buttonSelect = 4;
					else if (riverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else
					{
						page = 3;
						if (jackPodFlg)
							buttonSelect = 4;
						else if (mountFujiFlg)
							buttonSelect = 1;
						else if (talentedDemonFlg)
							buttonSelect = 5;
						else if (osakaMarathonFlg)
							buttonSelect = 2;
						else if (biwaLakeFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_AROUNDTHEGLOBE).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:地球一周級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_AROUNDTHEGLOBE);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 5)
			{
				amazonRiverScale = scaleMini;
				oceanScale = scaleMini;
				seaOf​​JapanScale = scaleMini;
				aroundTheGlobeScale = scaleMini;
				zeroMotivationScale = scaleController.ScaleControll(zeroMotivationScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = scaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (amazonRiverFlg)
						buttonSelect = 1;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else
					{
						page = 1;
						if (indianOceanFlg)
							buttonSelect = 6;
						if (lakeFlg)
							buttonSelect = 3;
						else if (sewerFlg)
							buttonSelect = 5;
						else if (waterFallFlg)
							buttonSelect = 2;
						else if (damFlg)
							buttonSelect = 4;
						else if (riverFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (jackPodFlg)
						buttonSelect = 4;
					else if (mountFujiFlg)
						buttonSelect = 1;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_ZEROMOTIVATION).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush((MOFKEY_SPACE)))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:やる気ゼロ級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_ZEROMOTIVATION);
					nowPopUpTrophy->Initialize();
				}
			}


			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 1;
				page = 1;
			}
			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_SELECT);
				buttonSelect = 1;
				page = 3;
			}
		}

		else if (page == 3)
		{
			if (buttonSelect == 0)
			{
				mountFujiScale = scaleMini;
				osakaMarathonScale = scaleMini;
				biwaLakeScale = scaleMini;
				jackPodScale = scaleMini;
				talentedDemonScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jackPodFlg)
						buttonSelect = 4;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else if (mountFujiFlg)
						buttonSelect = 1;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (biwaLakeFlg)
						buttonSelect = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (mountFujiFlg)
						buttonSelect = 1;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else if (jackPodFlg)
						buttonSelect = 4;
					else if (talentedDemonFlg)
						buttonSelect = 5;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					bubbleFade.FadeOut();
					nextSceneTemp = SCENENO_GAMEMENU;

					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneTrophyCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				osakaMarathonScale = scaleMini;
				biwaLakeScale = scaleMini;
				jackPodScale = scaleMini;
				talentedDemonScale = scaleMini;
				menuButtonScale = scaleMini;
				mountFujiScale = scaleController.ScaleControll(mountFujiScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jackPodFlg)
						buttonSelect = 4;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (jackPodFlg)
						buttonSelect = 4;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_MOUNTFJI).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:富士山級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_MOUNTFJI);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				mountFujiScale = scaleMini;
				osakaMarathonScale = scaleController.ScaleControll(osakaMarathonScale, scaleMax, scaleMini, scaleSpeed);
				biwaLakeScale = scaleMini;
				jackPodScale = scaleMini;
				talentedDemonScale = scaleMini;
				menuButtonScale = scaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jackPodFlg)
						buttonSelect = 4;
					else if (talentedDemonFlg)
						buttonSelect = 5;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (mountFujiFlg)
						buttonSelect = 1;
					else if (jackPodFlg)
						buttonSelect = 4;
					else
					{
						page = 2;
						if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (amazonRiverFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (biwaLakeFlg)
						buttonSelect = 3;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else
						buttonSelect = 0;

				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_OSAKAMARATHON).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:大阪マラソンの画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_OSAKAMARATHON);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				mountFujiScale = scaleMini;
				osakaMarathonScale = scaleMini;
				biwaLakeScale = scaleController.ScaleControll(biwaLakeScale, scaleMax, scaleMini, scaleSpeed);
				jackPodScale = scaleMini;
				talentedDemonScale = scaleMini;
				menuButtonScale = scaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (talentedDemonFlg)
						buttonSelect = 5;
					else if (jackPodFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (talentedDemonFlg)
						buttonSelect = 5;
					else if (jackPodFlg)
						buttonSelect = 4;
					else if (mountFujiFlg)
						buttonSelect = 1;
					else
					{
						page = 2;
						if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (amazonRiverFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_BIWALAKE).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:琵琶湖級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_BIWALAKE);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				mountFujiScale = scaleMini;
				osakaMarathonScale = scaleMini;
				biwaLakeScale = scaleMini;
				jackPodScale = scaleController.ScaleControll(jackPodScale, scaleMax, scaleMini, scaleSpeed);
				talentedDemonScale = scaleMini;
				menuButtonScale = scaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (mountFujiFlg)
						buttonSelect = 1;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (zeroMotivationFlg)
						buttonSelect = 5;
					else if (seaOf​​JapanFlg)
						buttonSelect = 3;
					else if (aroundTheGlobeFlg)
						buttonSelect = 4;
					else if (oceanFlg)
						buttonSelect = 2;
					else if (amazonRiverFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (talentedDemonFlg)
						buttonSelect = 5;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (biwaLakeFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_JACKPOD).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:ジャックポット級の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_JACKPOD);
					nowPopUpTrophy->Initialize();
				}
			}
			else if (buttonSelect == 5)
			{
				mountFujiScale = scaleMini;
				osakaMarathonScale = scaleMini;
				biwaLakeScale = scaleMini;
				jackPodScale = scaleMini;
				talentedDemonScale = scaleController.ScaleControll(talentedDemonScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = scaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (biwaLakeFlg)
						buttonSelect = 3;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (mountFujiFlg)
						buttonSelect = 1;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jackPodFlg)
						buttonSelect = 4;
					else if (osakaMarathonFlg)
						buttonSelect = 2;
					else if (mountFujiFlg)
						buttonSelect = 1;
					else
					{
						page = 2;
						if (zeroMotivationFlg)
							buttonSelect = 5;
						else if (seaOf​​JapanFlg)
							buttonSelect = 3;
						else if (aroundTheGlobeFlg)
							buttonSelect = 4;
						else if (oceanFlg)
							buttonSelect = 2;
						else if (amazonRiverFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(TROPHY_TALENTEDDEMON).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップにトロフィー:才能魔の画像を表示させる
					nowPopUpTrophy->SetButtonResult(TROPHY_TALENTEDDEMON);
					nowPopUpTrophy->Initialize();

				}
			}
			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				buttonSelect = 1;
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
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 31, leftAndRightButtonPosY - 2, MOF_XRGB(255, 255, 255), "1/3");

		if(riverFlg)
		scaleController.ScaleRender(&riverIconTexture, iconFirstRowPosX, iconOneLinePosY,riverScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + riverIconTexture.GetHeight() +10, "川級");
		if(waterFallFlg)
		scaleController.ScaleRender(&waterFallIconTexture, iconSecondRowPosX, iconOneLinePosY, waterFallScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + waterFallIconTexture.GetHeight() + 10, "滝級");
		if(lakeFlg)
		scaleController.ScaleRender(&lakeIconTexture, iconThirdRowPosX, iconOneLinePosY, lakeScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + lakeIconTexture.GetHeight() + 10, "湖級");
		if(damFlg)
		scaleController.ScaleRender(&damIconTexture, iconFirstRowPosX, iconTwoLinePosY, damScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY + damIconTexture.GetHeight() + 10 , "ダム級");
		if(sewerFlg)
		scaleController.ScaleRender(&sewerIconTexture, iconSecondRowPosX, iconTwoLinePosY, sewerScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY + sewerIconTexture.GetHeight() + 10, "下水道級");
		if(indianOceanFlg)
		scaleController.ScaleRender(&indianOceanIconTexture, iconThirdRowPosX, iconTwoLinePosY, indianOceanScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY + indianOceanIconTexture.GetHeight() + 10, "インド洋級");
	}
	if (page == 2)
	{
		backGroundTexture2.Render(0,0);
		//2ページ目
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 10, leftAndRightButtonPosY - 2, MOF_XRGB(255, 255, 255), "2/3");

		if(amazonRiverFlg)
		scaleController.ScaleRender(&amazonRiverIconTexture, iconFirstRowPosX, iconOneLinePosY, amazonRiverScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + amazonRiverIconTexture.GetHeight() + 10, "アマゾン川級");
		if(oceanFlg)
		scaleController.ScaleRender(&oceanIconTexture, iconSecondRowPosX, iconOneLinePosY, oceanScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + oceanIconTexture.GetHeight() + 10, "海級");
		if(seaOf​​JapanFlg)
		scaleController.ScaleRender(&seaOf​​JapanIconTexture, iconThirdRowPosX, iconOneLinePosY, seaOf​​JapanScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + seaOf​​JapanIconTexture.GetHeight() + 10, "日本海級");
		if(aroundTheGlobeFlg)
		scaleController.ScaleRender(&aroundTheGlobeIconTexture, icon2PageFirstRowPosX, iconTwoLinePosY, aroundTheGlobeScale);
		//CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + aroundTheGlobeIconTexture.GetHeight() + 10, "地球一周級");
		if(zeroMotivationFlg)
		scaleController.ScaleRender(&zeroMotivationIconTexture, icon2pageSecondRowPosX, iconTwoLinePosY, zeroMotivationScale);
		//CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + zeroMotivationIconTexture.GetHeight() + 10, "やる気ゼロ級");
	}
	if (page == 3)
	{
		backGroundTexture2.Render(0, 0);
		//3ページ目
		font.RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 9, leftAndRightButtonPosY - 2, MOF_XRGB(255, 255, 255), "3/3");

		if(mountFujiFlg)
		scaleController.ScaleRender(&mountFujiIconTexture, iconFirstRowPosX, iconOneLinePosY, mountFujiScale);
		//CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY + mountFujiIconTexture.GetHeight() + 10, "富士山級");
		if(osakaMarathonFlg)
		scaleController.ScaleRender(&osakaMarathonIconTexture, iconSecondRowPosX, iconOneLinePosY, osakaMarathonScale);
		//CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY + osakaMarathonIconTexture.GetHeight() + 10, "大阪マラソン級");
		if(biwaLakeFlg)
		scaleController.ScaleRender(&biwaLakeIconTexture, iconThirdRowPosX, iconOneLinePosY, biwaLakeScale);
		//CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY + biwaLakeIconTexture.GetHeight() + 10, "琵琶湖級");
		if(jackPodFlg)
		scaleController.ScaleRender(&jackPodIconTexture, icon2PageFirstRowPosX, iconTwoLinePosY, jackPodScale);
		//CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY + jackPodIconTexture.GetHeight() + 10, "ジャックポット級");
		if(talentedDemonFlg)
		scaleController.ScaleRender(&talentedDemonIconTexture, icon2pageSecondRowPosX+30, iconTwoLinePosY, talentedDemonScale);
		//CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY + talentedDemonIconTexture.GetHeight() + 10, "才能魔級");
	}

	scaleController.ScaleRender(&menuButtonTexture,menuButtonPosX,menuButtonPosY,menuButtonScale);
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);
	font.RenderString(textPosX, textPosY, MOF_XRGB(255, 255, 255), "トロフィー集");
	if (popUpFlg)
	{
		nowPopUpTrophy->Render();
	}
	bubbleFade.Render();
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
	bubbleFade.Release();

}

void CSceneTrophyCollection::MouseCollision(int posX, int posY)
{
	if (ButtonGetRect(0).CollisionPoint(posX,posY) && buttonSelect != 0)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 0;
	}
	if (page == 1)
	{
		if (GetRect(TROPHY_RIVER).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}

		else if (GetRect(TROPHY_WATERFALL).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}

		else if (GetRect(TROPHY_LAKE).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}

		else if (GetRect(TROPHY_DAM).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}

		else if (GetRect(TROPHY_SEWER).CollisionPoint(posX, posY) && buttonSelect != 5)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 5;
		}

		else if (GetRect(TROPHY_INDIANOCEAN).CollisionPoint(posX, posY) && buttonSelect != 6)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}
	}
	else if (page == 2)
	{
		if (GetRect(TROPHY_AMAZONROVER).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		if (GetRect(TROPHY_OCEAN).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		if (GetRect(TROPHY_SEAOFJAPAN).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		if (GetRect(TROPHY_AROUNDTHEGLOBE).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
		if (GetRect(TROPHY_ZEROMOTIVATION).CollisionPoint(posX, posY) && buttonSelect != 5)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 5;
		}
	}
	else if (page == 3)
	{
		if (GetRect(TROPHY_MOUNTFJI).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(TROPHY_OSAKAMARATHON).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}

		else if (GetRect(TROPHY_BIWALAKE).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(TROPHY_JACKPOD).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
		else if (GetRect(TROPHY_TALENTEDDEMON).CollisionPoint(posX, posY) && buttonSelect != 5)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 5;
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
	FILE* fp = fopen("SaveData\\SaveTrophy.dat", "wb");
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
	FILE* fp = fopen("SaveData\\SaveTrophy.dat", "rb");
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
