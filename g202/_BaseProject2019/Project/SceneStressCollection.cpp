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
	if(hyperthermiaFlg)
		hyperthermiaTexture.Load("マンボウ 体温上昇icon.png");
	else
		hyperthermiaTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureTexture.Load("マンボウ 体温低下icon.png");
	else
		lowerBodyTemperatureTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationTexture.Load("マンボウ 空腹icon.png");
	else
		starvationTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatexture.Load("マンボウ　喉つまりicon.png");
	else
		cloggedThroatexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityTexture.Load("肥満マンボウ2icon.png");
	else
		obesityTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactTexture.Load("障害物にあたって死亡icon.png");
	else
		impactTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("マンボウ寄生虫ストレスicon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");

	if(jumpFlg)
		jumpTexture.Load("水面にたたきつけられ死亡 海なしicon.png");
	else
		jumpTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleTexture.Load("siin_aikon.png");
	else
		bubbleTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleTexture.Load("マンボウ亀予感icon.png");
	else
		turtleTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowTexture.Load("加速死icon.png");
	else
		waterFlowTexture.Load("siin_aikon_Enpty.png");

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
	if (ButtonGetRect(0).CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		menuButtonScale =  scaleController.ScaleControll(menuButtonScale,scaleMax,scaleMini,scaleSpeed);
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			endFlg = true;
			nextScene = SCENENO_GAMEMENU;
			CSceneStressCollection::Release();
		}
	}
	else
	{
		menuButtonScale = scaleMini;
	}

	if(!popUpFlg)
	{
		if (page == 1)
		{
			if (GetRect(CAUSE_Hyperthermia).CollisionPoint(mousePosX, mousePosY))
			{
				hyperthermiaScale = scaleController.ScaleControll(hyperthermiaScale,scaleMax,scaleMini,scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:体温上昇の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Hyperthermia);
				}
			}
			else
			{
				hyperthermiaScale = scaleMini;
			}
			if (GetRect(CAUSE_Frozen).CollisionPoint(mousePosX, mousePosY))
			{
				lowerBodyTemperatureScale = scaleController.ScaleControll(lowerBodyTemperatureScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:体温低下の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Frozen);
				}
			}
			else
			{
				lowerBodyTemperatureScale = scaleMini;
			}
			if (GetRect(CAUSE_Starvation).CollisionPoint(mousePosX, mousePosY))
			{
				starvationScale = scaleController.ScaleControll(starvationScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:餓死の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Starvation);
				}
			}
			else
			{
				starvationScale = scaleMini;
			}
			if (GetRect(CAUSE_ChokeOnShell).CollisionPoint(mousePosX, mousePosY))
			{
				cloggedThroatScale = scaleController.ScaleControll(cloggedThroatScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:喉詰まりの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_ChokeOnShell);
				}
			}
			else
			{
				cloggedThroatScale = scaleMini;
			}
			if (GetRect(CAUSE_Obesity).CollisionPoint(mousePosX, mousePosY))
			{
				obesityScale = scaleController.ScaleControll(obesityScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:肥満の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Obesity);
				}
			}
			else
			{
				obesityScale = scaleMini;
			}
			if (GetRect(CAUSE_Obstacle).CollisionPoint(mousePosX, mousePosY))
			{
				impactScale = scaleController.ScaleControll(impactScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:障害物と衝突の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Obstacle);
				}
			}
			else
			{
				impactScale = scaleMini;
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (GetRect(CAUSE_Parasite).CollisionPoint(mousePosX, mousePosY))
			{
				parasiteScale = scaleController.ScaleControll(parasiteScale,scaleMax,scaleMini,scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:寄生虫の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Parasite);
				}
			}
			else
			{
				parasiteScale = scaleMini;
			}
			if (GetRect(CAUSE_Jump).CollisionPoint(mousePosX, mousePosY))
			{
				jumpScale = scaleController.ScaleControll(jumpScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:ジャンプの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Jump);
				}
			}
			else
			{
				jumpScale = scaleMini;
			}
			if (GetRect(CAUSE_Bubble).CollisionPoint(mousePosX, mousePosY))
			{
				bubbleScale = scaleController.ScaleControll(bubbleScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:泡の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_Bubble);
				}
			}
			else
			{
				bubbleScale = scaleMini;
			}
			if (GetRect(CAUSE_SeaTurtle).CollisionPoint(mousePosX, mousePosY))
			{
				turtleScalse = scaleController.ScaleControll(turtleScalse, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:ウミガメの死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_SeaTurtle);
				}
			}
			else
			{
				turtleScalse = scaleMini;
			}
			if (GetRect(CAUSE_WaterFlow).CollisionPoint(mousePosX, mousePosY))
			{
				waterFlowScale = scaleController.ScaleControll(waterFlowScale, scaleMax, scaleMini, scaleSpeed);
				if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
				{
					popUpFlg = true;
					//ポップアップに死因:水流の死因画像を表示させる
					nowPopUpStress->SetButtonResult(CAUSE_WaterFlow);
				}
			}
			else
			{
				waterFlowScale = scaleMini;
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
	if (page == 1)
	{
		//1ページ目に表示
		//hyperthermiaTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&hyperthermiaTexture, iconFirstRowPosX, iconOneLinePosY,hyperthermiaScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "体温上昇");
		//lowerBodyTemperatureIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&lowerBodyTemperatureTexture, iconSecondRowPosX, iconOneLinePosY, lowerBodyTemperatureScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "体温低下");
		//starvationIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&starvationTexture, iconThirdRowPosX, iconOneLinePosY, starvationScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "餌");
		//cloggedThroatIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&cloggedThroatexture, iconFirstRowPosX, iconTwoLinePosY, cloggedThroatScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconTwoLinePosY - 30, "魚の骨・甲殻類の殻");
		//obesityIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&obesityTexture, iconSecondRowPosX, iconTwoLinePosY, obesityScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconTwoLinePosY - 30, "食べ過ぎ");
		//impactIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&impactTexture, iconThirdRowPosX, iconTwoLinePosY, impactScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconTwoLinePosY - 30, "障害物");
	}
	if (page == 2)
	{
		//2ページ目に表示
		//parasiteIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&parasiteIconTexture, iconFirstRowPosX, iconOneLinePosY, parasiteScale);
		CGraphicsUtilities::RenderString(iconFirstRowPosX, iconOneLinePosY - 30, "寄生虫");
		//jumpTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&jumpTexture, iconSecondRowPosX, iconOneLinePosY, jumpScale);
		CGraphicsUtilities::RenderString(iconSecondRowPosX, iconOneLinePosY - 30, "ジャンプ");
		//bubbleTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		scaleController.ScaleRender(&bubbleTexture, iconThirdRowPosX, iconOneLinePosY, bubbleScale);
		CGraphicsUtilities::RenderString(iconThirdRowPosX, iconOneLinePosY - 30, "泡");
		//turtleTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&turtleTexture, icon2PageFirstRowPosX, iconTwoLinePosY, turtleScalse);
		CGraphicsUtilities::RenderString(icon2PageFirstRowPosX, iconTwoLinePosY - 30, "ウミガメ");
		//waterFlowTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
		scaleController.ScaleRender(&waterFlowTexture, icon2pageSecondRowPosX, iconTwoLinePosY, waterFlowScale);
		CGraphicsUtilities::RenderString(icon2pageSecondRowPosX, iconTwoLinePosY - 30, "水流");
	}

	scaleController.ScaleRender(&menuButtonTexture , menuButtonPosX,menuButtonPosY,menuButtonScale);
	
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
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationTexture.GetWidth(), iconOneLinePosY + starvationTexture.GetHeight());
	//死因:喉に刺さるクリック時
	if (i == CAUSE_ChokeOnShell && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatexture.GetWidth(), iconTwoLinePosY + cloggedThroatexture.GetHeight());
	//死因:肥満クリック時
	if(i == CAUSE_Obesity && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityTexture.GetWidth(), iconTwoLinePosY + obesityTexture.GetHeight());
	//死因:障害物と衝突クリック時
	if (i == CAUSE_Obstacle && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactTexture.GetWidth(), iconTwoLinePosY + impactTexture.GetHeight());

	//死因:寄生虫クリック時
	if(i == CAUSE_Parasite && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//死因:ジャンプクリック時
	if (i == CAUSE_Jump && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpTexture.GetWidth(), iconOneLinePosY + jumpTexture.GetHeight());
	//死因:泡クリック時
	if(i == CAUSE_Bubble && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleTexture.GetWidth(), iconOneLinePosY + bubbleTexture.GetHeight());
	//死因:ウミガメ接触クリック時
	if(i == CAUSE_SeaTurtle && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleTexture.GetWidth(), iconTwoLinePosY + turtleTexture.GetHeight());
	//死因:水流
	if(i == CAUSE_WaterFlow && waterFlowFlg)
		return CRectangle(icon2pageSecondRowPosX, iconTwoLinePosY, icon2pageSecondRowPosX + waterFlowTexture.GetWidth(), iconTwoLinePosY + waterFlowTexture.GetHeight());

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
	return false;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "wb");
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
		fclose(fp);
	}
}

void CSceneStressCollection::LoadStressFlg()
{
	FILE* fp = fopen("SaveStress.dat", "rb");
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
		fclose(fp);
	}
}