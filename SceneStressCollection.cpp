#include "SceneStressCollection.h"
#include "CheckCauseOfDeathWindow.h"

CPopUpWindowBase* nowPopUpStress = NULL;

CSceneStressCollection::CSceneStressCollection()
{

}
CSceneStressCollection::~CSceneStressCollection()
{
	Release();
}

void CSceneStressCollection::PlayBGM()
{
	cSound->BGMStop();
	cSound->Play(SOUND_COLLECTION_BGM);
}

void CSceneStressCollection::Initialize()
{
	//背景読み込み
	backGroundTex.Load("BackGround_CaseOfDeath.png");

	//ストレスフラグ読み込み
	LoadStressFlg();

	//フォント
	font.Load(fontAdd, fontName);
	font.Create(64, fontName);


	page = 1;
	//死因テクスチャ読み込み
	hyperthermiaTexture.Load("マンボウ 体温上昇icon.png");

	lowerBodyTemperatureTexture.Load("マンボウ 体温低下icon.png");

	starvationTexture.Load("マンボウ 空腹icon.png");

	cloggedThroatexture.Load("マンボウ　喉つまりicon.png");

	obesityTexture.Load("肥満マンボウ2icon.png");

	impactTexture.Load("障害物にあたって死亡icon.png");

	parasiteIconTexture.Load("マンボウ寄生虫ストレスicon.png");

	jumpTexture.Load("水面にたたきつけられ死亡 海なしicon.png");

	bubbleTexture.Load("マンボウ泡icon.png");

	turtleTexture.Load("マンボウ亀予感icon.png");

	waterFlowTexture.Load("加速死icon.png");

	shoalFishTexture.Load("マンボウ　魚群衝突死icon.png");

	//ボタンテクスチャ読み込み
	menuButtonTexture.Load("ButtonMenu.png");
	rightButtonTexture.Load("ButtonRight.png");
	leftButtonTexture.Load("ButtonLeft.png");

	//ポップアップ初期化
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
	nowPopUpStress->SetSoundManager(*cSound);
	PlayBGM();

	//選択初期化
	if (hyperthermiaFlg)
		buttonSelect = 1;
	else if (lowerBodyTemperatureFlg)
		buttonSelect = 2;
	else if (starvationFlg)
		buttonSelect = 3;
	else if (cloggedThroatFlg)
		buttonSelect = 4;
	else
		buttonSelect = 0;
}
void CSceneStressCollection::Update()
{
	//ポップアップ処理
	if (popUpFlg)
	{		
		if (nowPopUpStress->IsEnd())
		{
			nowPopUpStress->Release();
			popUpFlg = false;
		}
		nowPopUpStress->Update();
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if(!popUpFlg)
	{
		MouseCollision(mousePosX, mousePosY);
		if (page == 1)
		{
			if (buttonSelect == 0)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;					
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				hyperthermiaScale = scaleController.ScaleControll(hyperthermiaScale, scaleMax, scaleMini, scaleSpeed);
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (starvationFlg)
						buttonSelect = 3;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else
					{
						page = 2;
						if (obesityFlg)
							buttonSelect = 1;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (jumpFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:体温上昇の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleController.ScaleControll(lowerBodyTemperatureScale, scaleMax, scaleMini, scaleSpeed);
				starvationScale = scaleMini;
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (starvationFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (starvationFlg)
						buttonSelect = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:体温低下の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Frozen);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleController.ScaleControll(starvationScale, scaleMax, scaleMini, scaleSpeed);
				cloggedThroatScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
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
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else
					{
						page = 2;
						if (obesityFlg)
							buttonSelect = 1;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (jumpFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:餓死の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Starvation);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				hyperthermiaScale = scaleMini;
				lowerBodyTemperatureScale = scaleMini;
				starvationScale = scaleMini;
				cloggedThroatScale = scaleController.ScaleControll(cloggedThroatScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (lowerBodyTemperatureFlg)
						buttonSelect = 2;
					else if (hyperthermiaFlg)
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
					if (starvationFlg)
						buttonSelect = 3;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (parasiteFlg)
					buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:喉詰まりの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
					nowPopUpStress->Initialize();
				}
			}

			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
				cSound->Play(SOUND_BUTTON_PUSH);
			}
		}
		else if (page == 2)
		{
			if (buttonSelect == 0)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				obesityScale = scaleController.ScaleControll(obesityScale, scaleMax, scaleMini, scaleSpeed);;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (parasiteFlg)
						buttonSelect = 3;
					else if (jumpFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (impactFlg)
						buttonSelect = 2;
					else if (jumpFlg)
						buttonSelect = 4;
					else
					{
						page = 3;
						if (bubbleFlg)
							buttonSelect = 1;
						else if (waterFlowFlg)
							buttonSelect = 3;
						else if (turtleFlg)
							buttonSelect = 2;
						else if (shoalFishFlg)
							buttonSelect = 4;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (starvationFlg)
						buttonSelect = 2;
					else if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else if (starvationFlg)
						buttonSelect = 3;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:肥満の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Obesity);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				obesityScale = scaleMini;
				impactScale = scaleController.ScaleControll(impactScale, scaleMax, scaleMini, scaleSpeed);
				parasiteScale = scaleMini;
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (jumpFlg)
						buttonSelect = 4;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (starvationFlg)
							buttonSelect = 2;
						else if (cloggedThroatFlg)
							buttonSelect = 4;
						else if (hyperthermiaFlg)
							buttonSelect = 1;
						else if (starvationFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (bubbleFlg)
						buttonSelect = 1;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else if (turtleFlg)
						buttonSelect = 2;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:障害物と衝突の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleController.ScaleControll(parasiteScale, scaleMax, scaleMini, scaleSpeed);
				jumpScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (obesityFlg)
						buttonSelect = 1;
					else if (impactFlg)
						buttonSelect = 2;
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
					if (jumpFlg)
						buttonSelect = 4;
					else if (impactFlg)
						buttonSelect = 2;
					else
					{
						page = 3;
						if (waterFlowFlg)
							buttonSelect = 3;
						else if (shoalFishFlg)
							buttonSelect = 4;
						else if (bubbleFlg)
							buttonSelect = 1;
						else if (turtleFlg)
							buttonSelect = 2;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 1;
					if (cloggedThroatFlg)
						buttonSelect = 4;
					else if (starvationFlg)
						buttonSelect = 2;
					else if (starvationFlg)
						buttonSelect = 3;
					else if (hyperthermiaFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:寄生虫の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Parasite);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				obesityScale = scaleMini;
				impactScale = scaleMini;
				parasiteScale = scaleMini;
				jumpScale = scaleController.ScaleControll(jumpScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (impactFlg)
						buttonSelect = 2;
					else if (obesityFlg)
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
					if (parasiteFlg)
						buttonSelect = 3;
					else if (obesityFlg)
						buttonSelect = 1;
					else
					{
						page = 1;
						if (cloggedThroatFlg)
							buttonSelect = 4;
						else if (starvationFlg)
							buttonSelect = 2;
						else if (starvationFlg)
							buttonSelect = 3;
						else if (hyperthermiaFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 3;
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:ジャンプの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Jump);
					nowPopUpStress->Initialize();
				}
			}



			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)&& ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				page = 1;
			}
			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				page = 3;
			}
		}
		else if (page == 3)
		{
			if (buttonSelect == 0)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = scaleController.ScaleControll(menuButtonScale, menuButtonScaleMax, menuButtonScaleMini, scaleSpeed);
				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					endFlg = true;
					nextScene = SCENENO_GAMEMENU;
					CSceneStressCollection::Release();
				}
			}
			else if (buttonSelect == 1)
			{
				bubbleScale = scaleController.ScaleControll(bubbleScale, scaleMax, scaleMini, scaleSpeed);;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (shoalFishFlg)
						buttonSelect = 4;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (turtleFlg)
						buttonSelect = 2;
					else if (shoalFishFlg)
						buttonSelect = 4;
					
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (impactFlg)
						buttonSelect = 2;
					else if (jumpFlg)
						buttonSelect = 4;
					else if (obesityFlg)
						buttonSelect = 1;
					else if (parasiteFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}

				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE) && !popUpFlg)
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:泡の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Bubble);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 2)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleController.ScaleControll(turtleScalse, scaleMax, scaleMini, scaleSpeed);
				waterFlowScale = scaleMini;
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (shoalFishFlg)
						buttonSelect = 4;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else
						buttonSelect = 0;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (waterFlowFlg)
						buttonSelect = 3;
					else
					{
						page = 2;
						if (impactFlg)
							buttonSelect = 2;
						else if (jumpFlg)
							buttonSelect = 4;
						else if (obesityFlg)
							buttonSelect = 1;
						else if (parasiteFlg)
							buttonSelect = 3;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:ウミガメの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 3)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleController.ScaleControll(waterFlowScale, scaleMax, scaleMini, scaleSpeed);
				shoalFishScale = scaleMini;
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (bubbleFlg)
						buttonSelect = 1;
					else if (turtleFlg)
						buttonSelect = 2;
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
					if (shoalFishFlg)
						buttonSelect = 4;
					else if (turtleFlg)
						buttonSelect = 2;
				}
				else if (g_pInput->IsKeyPush(MOFKEY_LEFT))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					page = 2;
					if (jumpFlg)
						buttonSelect = 4;
					else if (impactFlg)
						buttonSelect = 2;
					else if (parasiteFlg)
						buttonSelect = 3;
					else if (obesityFlg)
						buttonSelect = 1;
					else
						buttonSelect = 0;
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:水流の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
					nowPopUpStress->Initialize();
				}
			}
			else if (buttonSelect == 4)
			{
				bubbleScale = scaleMini;
				turtleScalse = scaleMini;
				waterFlowScale = scaleMini;
				shoalFishScale = scaleController.ScaleControll(shoalFishScale, scaleMax, scaleMini, scaleSpeed);
				menuButtonScale = menuButtonScaleMini;

				if (g_pInput->IsKeyPush(MOFKEY_UP))
				{
					cSound->Play(SOUND_BUTTON_SELECT);
					if (turtleFlg)
						buttonSelect = 2;
					else if (bubbleFlg)
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
					if (waterFlowFlg)
						buttonSelect = 3;
					else if (bubbleFlg)
						buttonSelect = 1;
					else
					{
						page = 2;
						if (jumpFlg)
							buttonSelect = 4;
						else if (impactFlg)
							buttonSelect = 2;
						else if (parasiteFlg)
							buttonSelect = 3;
						else if (obesityFlg)
							buttonSelect = 1;
						else
							buttonSelect = 0;
					}
				}
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ShoalFish).CollisionPoint(mousePosX, mousePosY) && !popUpFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
				{
					cSound->Play(SOUND_BUTTON_PUSH);
					popUpFlg = true;
					//ポップアップに死因:ジャンプの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_ShoalFish);
					nowPopUpStress->Initialize();
				}
			}

			if ((g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				cSound->Play(SOUND_BUTTON_PUSH);
				page = 2;
			}
		}
	}
}
void CSceneStressCollection::Render()
{
	backGroundTex.Render(0, 0);
	font.RenderString(textPosX,textPosY, MOF_XRGB(0, 0, 0), "ストレス一覧");
	if (page == 1)
	{
		//1ページ目に表示

		if(hyperthermiaFlg)
		scaleController.ScaleRender(&hyperthermiaTexture, iconFirstRowPosX, iconOneLinePosY, hyperthermiaScale);
		if(lowerBodyTemperatureFlg)
		scaleController.ScaleRender(&lowerBodyTemperatureTexture, iconSecondRowPosX, iconOneLinePosY, lowerBodyTemperatureScale);
		if(starvationFlg)
		scaleController.ScaleRender(&starvationTexture, iconFirstRowPosX, iconTwoLinePosY, starvationScale);
		if(cloggedThroatFlg)
		scaleController.ScaleRender(&cloggedThroatexture, iconSecondRowPosX, iconTwoLinePosY, cloggedThroatScale);
	}
	if (page == 2)
	{
		//2ページ目に表示
		if(obesityFlg)
		scaleController.ScaleRender(&obesityTexture, iconFirstRowPosX, iconOneLinePosY, obesityScale);
		if(impactFlg)
		scaleController.ScaleRender(&impactTexture, iconSecondRowPosX, iconOneLinePosY, impactScale);
		if(parasiteFlg)
		scaleController.ScaleRender(&parasiteIconTexture, iconFirstRowPosX, iconTwoLinePosY, parasiteScale);
		if(jumpFlg)
		scaleController.ScaleRender(&jumpTexture, iconSecondRowPosX, iconTwoLinePosY +10, jumpScale);
	}
	if (page == 3)
	{
		//3ページ目に表示
		if(bubbleFlg)
		scaleController.ScaleRender(&bubbleTexture, iconFirstRowPosX, iconOneLinePosY, bubbleScale);
		if(turtleFlg)
		scaleController.ScaleRender(&turtleTexture, iconSecondRowPosX, iconOneLinePosY, turtleScalse);
		if(waterFlowFlg)
		scaleController.ScaleRender(&waterFlowTexture, iconFirstRowPosX, iconTwoLinePosY+10, waterFlowScale);
		if(shoalFishFlg)
		scaleController.ScaleRender(&shoalFishTexture,iconSecondRowPosX,iconTwoLinePosY+20,shoalFishScale);
	}

	scaleController.ScaleRender(&menuButtonTexture , menuButtonPosX,menuButtonPosY,menuButtonScale);
	
	CGraphicsUtilities::RenderString(leftButtonPosX + leftButtonTexture.GetWidth() + 10, leftAndRightButtonPosY + 5, MOF_XRGB(0, 0, 0), "%d/3",page);
	if(page != 1)
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	if (page !=3)
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);

	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}
}
void CSceneStressCollection::Release()
{
	backGroundTex.Release();
	hyperthermiaTexture.Release();
	lowerBodyTemperatureTexture.Release();
	starvationTexture.Release();
	cloggedThroatexture.Release();
	obesityTexture.Release();
	impactTexture.Release();
	parasiteIconTexture.Release();
	jumpTexture.Release();
	bubbleTexture.Release();
	turtleTexture.Release();
	waterFlowTexture.Release();
	shoalFishTexture.Release();

	menuButtonTexture.Release();
	if (nowPopUpStress != NULL)
	{
		nowPopUpStress->Release();
		if (nowPopUpStress)
		{
			delete nowPopUpStress;
			nowPopUpStress = NULL;
		}
	}
}

CRectangle CSceneStressCollection::GetRect(int i)
{
	//死因:体温上昇クリック時
	if (i == CAUSE_Hyperthermia && hyperthermiaFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + hyperthermiaTexture.GetWidth(), iconOneLinePosY + hyperthermiaTexture.GetHeight());
	//死因:体温低下クリック時
	if (i == CAUSE_Frozen && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureTexture.GetHeight());
	//死因:餓死クリック時
	if (i == CAUSE_Starvation && starvationFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + starvationTexture.GetWidth(), iconTwoLinePosY + starvationTexture.GetHeight());
	//死因:喉に刺さるクリック時
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + cloggedThroatexture.GetWidth(), iconTwoLinePosY + cloggedThroatexture.GetHeight());

	//死因:肥満クリック時
	if (i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + obesityTexture.GetWidth(), iconOneLinePosY + obesityTexture.GetHeight());
	//死因:障害物と衝突クリック時
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + impactTexture.GetWidth(), iconOneLinePosY + impactTexture.GetHeight());
	//死因:寄生虫クリック時
	if (i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconTwoLinePosY + parasiteIconTexture.GetHeight());
	//死因:ジャンプクリック時
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + jumpTexture.GetWidth(), iconTwoLinePosY + jumpTexture.GetHeight());

	//死因:泡クリック時
	if (i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + bubbleTexture.GetWidth(), iconOneLinePosY + bubbleTexture.GetHeight());
	//死因:ウミガメ接触クリック時
	if (i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + turtleTexture.GetWidth(), iconOneLinePosY + turtleTexture.GetHeight());
	//死因:水流
	if (i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + waterFlowTexture.GetWidth(), iconTwoLinePosY + waterFlowTexture.GetHeight());
	//死因:魚群
	if(i == CAUSE_ShoalFish && shoalFishFlg)
		return CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + shoalFishTexture.GetWidth(), iconTwoLinePosY + shoalFishTexture.GetHeight());
}

void CSceneStressCollection::MouseCollision(int posX, int posY)
{
		if (ButtonGetRect(0).CollisionPoint(posX, posY) && buttonSelect != 0)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 0;
		}
	if (page == 1)
	{
		if (GetRect(CAUSE_Hyperthermia).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_Frozen).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_Starvation).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_ChokeOnShell).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
	else if (page == 2)
	{
		if (GetRect(CAUSE_Obesity).CollisionPoint(posX, posY) && buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_Obstacle).CollisionPoint(posX, posY) && buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_Parasite).CollisionPoint(posX, posY) && buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_Jump).CollisionPoint(posX, posY) && buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
	else if (page == 3)
	{
		if (GetRect(CAUSE_Bubble).CollisionPoint(posX, posY) &&buttonSelect != 1)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 1;
		}
		else if (GetRect(CAUSE_SeaTurtle).CollisionPoint(posX, posY)&&buttonSelect != 2)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 2;
		}
		else if (GetRect(CAUSE_WaterFlow).CollisionPoint(posX, posY)&& buttonSelect != 3)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 3;
		}
		else if (GetRect(CAUSE_ShoalFish).CollisionPoint(posX, posY)&& buttonSelect != 4)
		{
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 4;
		}
	}
}

CRectangle CSceneStressCollection::ButtonGetRect(int i)
{
	if (i == 0)
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(leftButtonPosX, leftAndRightButtonPosY, leftButtonPosX + leftButtonTexture.GetWidth(), leftAndRightButtonPosY + leftButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(rightButtonPosX, leftAndRightButtonPosY, rightButtonPosX + rightButtonTexture.GetWidth(), leftAndRightButtonPosY + rightButtonTexture.GetHeight());
}

bool CSceneStressCollection::GetStress(int i)
{

	//熱中症ゲット
	if (i == CAUSE_Hyperthermia && !hyperthermiaFlg)
	{
		hyperthermiaFlg = true;
		SaveStressFlg();
		return true;
	}
	//体温低下ゲット
	if (i == CAUSE_Frozen && !lowerBodyTemperatureFlg)
	{
		lowerBodyTemperatureFlg = true;
		SaveStressFlg();
		return true;
	}
	//餓死
	if (i == CAUSE_Starvation && !starvationFlg)
	{
		starvationFlg = true;
		SaveStressFlg();
		return true;
	}
	//喉詰まり
	if (i == CAUSE_ChokeOnShell && !cloggedThroatFlg)
	{
		cloggedThroatFlg = true;
		SaveStressFlg();
		return true;
	}
	//肥満
	if (i == CAUSE_Obesity && !obesityFlg)
	{
		obesityFlg = true;
		SaveStressFlg();
		return true;
	}
	//衝突
	if (i == CAUSE_Obstacle && !impactFlg)
	{
		impactFlg = true;
		SaveStressFlg();
		return true;
	}
	//寄生虫
	if (i == CAUSE_Parasite && !parasiteFlg)
	{
		parasiteFlg = true;
		SaveStressFlg();
		return true;
	}
	//ジャンプ
	if (i == CAUSE_Jump && !jumpFlg)
	{
		jumpFlg = true;
		SaveStressFlg();
		return true;
	}
	//泡
	if (i == CAUSE_Bubble && !bubbleFlg)
	{
		bubbleFlg = true;
		SaveStressFlg();
		return true;
	}
	//ウミガメ
	if (i == CAUSE_SeaTurtle && !turtleFlg)
	{
		turtleFlg = true;
		SaveStressFlg();
		return true;
	}
	//水流
	if (i == CAUSE_WaterFlow && !waterFlowFlg)
	{
		waterFlowFlg = true;
		SaveStressFlg();
		return true;
	}
	if (i == CAUSE_ShoalFish && !shoalFishFlg)
	{
		shoalFishFlg = true;
		SaveStressFlg();
		return true;
	}
	return false;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("SaveData\\SaveStress.dat", "wb");
	if (fp)
	{
		fwrite(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fwrite(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fwrite(&starvationFlg, sizeof(bool), 1, fp);
		fwrite(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fwrite(&obesityFlg, sizeof(bool), 1, fp);
		fwrite(&impactFlg, sizeof(bool), 1, fp);
		fwrite(&parasiteFlg, sizeof(bool), 1, fp);
		fwrite(&jumpFlg, sizeof(bool), 1, fp);
		fwrite(&bubbleFlg, sizeof(bool), 1, fp);
		fwrite(&turtleFlg, sizeof(bool), 1, fp);
		fwrite(&waterFlowFlg, sizeof(bool), 1, fp);
		fwrite(&shoalFishFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}

void CSceneStressCollection::LoadStressFlg()
{
	FILE* fp = fopen("SaveData\\SaveStress.dat", "rb");
	if (fp)
	{
		fread(&hyperthermiaFlg, sizeof(bool), 1, fp);
		fread(&lowerBodyTemperatureFlg, sizeof(bool), 1, fp);
		fread(&starvationFlg, sizeof(bool), 1, fp);
		fread(&cloggedThroatFlg, sizeof(bool), 1, fp);
		fread(&obesityFlg, sizeof(bool), 1, fp);
		fread(&impactFlg, sizeof(bool), 1, fp);
		fread(&parasiteFlg, sizeof(bool), 1, fp);
		fread(&jumpFlg, sizeof(bool), 1, fp);
		fread(&bubbleFlg, sizeof(bool), 1, fp);
		fread(&turtleFlg, sizeof(bool), 1, fp);
		fread(&waterFlowFlg, sizeof(bool), 1, fp);
		fread(&shoalFishFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}
}
