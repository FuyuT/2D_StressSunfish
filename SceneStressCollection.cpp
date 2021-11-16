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
	cSound.AllStop();
	cSound.Play(SOUND_COLLECTION_BGM);
}

void CSceneStressCollection::Initialize()
{
	//背景読み込み
	backGroundTex.Load("Title.png");

	//ストレスフラグ読み込み
	LoadStressFlg();

	page = 1;
	//死因テクスチャ読み込み
	//フラグがオンなら対応するテクスチャ、フラグがオフなら未取得テクスチャを読み込む。
	if(increasedBodyTemperatureFlg)
		increasedBodyTemperatureIconTexture.Load("マンボウ 体温上昇icon.png");
	else
		increasedBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureIconTexture.Load("マンボウ 体温低下icon.png");
	else
		lowerBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationIconTexture.Load("マンボウ 空腹icon.png");
	else
		starvationIconTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatIconTexture.Load("マンボウ　喉つまりicon.png");
	else
		cloggedThroatIconTexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityIconTexture.Load("肥満マンボウ2icon.png");
	else
		obesityIconTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactIconTexture.Load("障害物にあたって死亡icon.png");
	else
		impactIconTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("マンボウ寄生虫ストレスicon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");

	if(jumpFlg)
		jumpIconTexture.Load("水面にたたきつけられ死亡 海なしicon.png");
	else
		jumpIconTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleIconTexture.Load("siin_aikon.png");
	else
		bubbleIconTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleIconTexture.Load("マンボウ亀予感icon.png");
	else
		turtleIconTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowIconTexture.Load("加速死icon.png");
	else
		waterFlowIconTexture.Load("siin_aikon_Enpty.png");

	//ボタンテクスチャ読み込み
	menuButtonTexture.Load("ButtonMenu.png");
	rightButtonTexture.Load("ButtonRight.png");
	leftButtonTexture.Load("ButtonLeft.png");

	//ポップアップ初期化
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
	PlayBGM();
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
		nowPopUpStress->Initialize();
		nowPopUpStress->Update();
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneStressCollection::Release();
	}

	if(!popUpFlg)
	{
		if (page == 1)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:体温上昇の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:体温低下の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Frozen);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:餓死の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Starvation);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:喉詰まりの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:肥満の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Obesity);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:障害物と衝突の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:寄生虫の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Parasite);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ジャンプの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Jump);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:泡の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_Bubble);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_SeaTurtle).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ウミガメの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:水流の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT) ||  (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON)&& ButtonGetRect(1).CollisionPoint(mousePosX, mousePosY)))
			{
				page = 1;
			}
		}
	}


	//F1でポップアップ表示
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
}
void CSceneStressCollection::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 100, "ストレス集画面");
	if (page == 1)
	{
		//1ページ目に表示
		increasedBodyTemperatureIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "体温上昇");
		lowerBodyTemperatureIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "体温低下");
		starvationIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "餌");
		cloggedThroatIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY - 30, "魚の骨・甲殻類の殻");
		obesityIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY - 30, "食べ過ぎ");
		impactIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY - 30, "障害物");
	}
	if (page == 2)
	{
		//2ページ目に表示
		parasiteIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "寄生虫");
		jumpIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "ジャンプ");
		bubbleIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "泡");
		turtleIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY - 30, "ウミガメ");
		waterFlowIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY - 30, "水流");
	}

	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	
	CGraphicsUtilities::RenderString(900, 800, "%d/2",page);
	leftButtonTexture.Render(leftButtonPosX, leftAndRightButtonPosY);
	rightButtonTexture.Render(rightButtonPosX, leftAndRightButtonPosY);

	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}
}
void CSceneStressCollection::Release()
{
	backGroundTex.Release();
	increasedBodyTemperatureIconTexture.Release();
	lowerBodyTemperatureIconTexture.Release();
	starvationIconTexture.Release();
	cloggedThroatIconTexture.Release();
	obesityIconTexture.Release();
	impactIconTexture.Release();
	parasiteIconTexture.Release();
	jumpIconTexture.Release();
	bubbleIconTexture.Release();
	turtleIconTexture.Release();
	waterFlowIconTexture.Release();

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
	if (i == CAUSE_Hyperthermia && increasedBodyTemperatureFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + increasedBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + increasedBodyTemperatureIconTexture.GetHeight());
	//死因:体温低下クリック時
	if (i == CAUSE_Frozen && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureIconTexture.GetHeight());
	//死因:餓死クリック時
	if (i == CAUSE_Starvation && starvationFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationIconTexture.GetWidth(), iconOneLinePosY + starvationIconTexture.GetHeight());
	//死因:喉に刺さるクリック時
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatIconTexture.GetWidth(), iconTwoLinePosY + cloggedThroatIconTexture.GetHeight());
	//死因:肥満クリック時
	if(i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityIconTexture.GetWidth(), iconTwoLinePosY + obesityIconTexture.GetHeight());
	//死因:障害物と衝突クリック時
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactIconTexture.GetWidth(), iconTwoLinePosY + impactIconTexture.GetHeight());

	//死因:寄生虫クリック時
	if(i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//死因:ジャンプクリック時
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpIconTexture.GetWidth(), iconOneLinePosY + jumpIconTexture.GetHeight());
	//死因:泡クリック時
	if(i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleIconTexture.GetWidth(), iconOneLinePosY + bubbleIconTexture.GetHeight());
	//死因:ウミガメ接触クリック時
	if(i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleIconTexture.GetWidth(), iconTwoLinePosY + turtleIconTexture.GetHeight());
	//死因:水流
	if(i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + waterFlowIconTexture.GetWidth(), iconTwoLinePosY + waterFlowIconTexture.GetHeight());

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
	if (i == CAUSE_Hyperthermia && !increasedBodyTemperatureFlg)
	{
		increasedBodyTemperatureFlg = true;
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
	return false;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "wb");
	if (fp)
	{
		fwrite(&increasedBodyTemperatureFlg, sizeof(bool), 1, fp);
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
		fclose(fp);
	}
}

void CSceneStressCollection::LoadStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "rb");
	if (fp)
	{
		fread(&increasedBodyTemperatureFlg, sizeof(bool), 1, fp);
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
		fclose(fp);
	}
}