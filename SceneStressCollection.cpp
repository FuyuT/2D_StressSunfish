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
void CSceneStressCollection::Initialize()
{
	//ストレスフラグ読み込み
	LoadStressFlg();

	page = 1;
	//死因テクスチャ読み込み
	//フラグがオンなら対応するテクスチャ、フラグがオフなら未取得テクスチャを読み込む。
	if(increasedBodyTemperatureFlg)
		increasedBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		increasedBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		lowerBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(starvationFlg)
		starvationIconTexture.Load("siin_aikon.png");
	else
		starvationIconTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatFlg)
		cloggedThroatIconTexture.Load("siin_aikon.png");
	else
		cloggedThroatIconTexture.Load("siin_aikon_Enpty.png");

	if(obesityFlg)
		obesityIconTexture.Load("siin_aikon.png");
	else
		obesityIconTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactIconTexture.Load("siin_aikon.png");
	else
		impactIconTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("siin_aikon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");
	if(jumpFlg)
		jumpIconTexture.Load("siin_aikon.png");
	else
		jumpIconTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleIconTexture.Load("siin_aikon.png");
	else
		bubbleIconTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleIconTexture.Load("siin_aikon.png");
	else
		turtleIconTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowIconTexture.Load("siin_aikon.png");
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
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_INCREASEDBODYTEMPERATURE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:体温上昇の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_INCREASEDBODYTEMPERATURE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_LOWERBODYTEMPERATURE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:体温低下の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_LOWERBODYTEMPERATURE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_STARVATION).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:餓死の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_STARVATION);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_CLOGGEDTHROAT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:喉詰まりの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_CLOGGEDTHROAT);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_OBESITY).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:肥満の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_OBESITY);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_IMPACT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:障害物と衝突の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_IMPACT);
			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect(2).CollisionPoint(mousePosX,mousePosY)))
			{
				page = 2;
			}
		}
		else if (page == 2)
		{
			if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_PARASITE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:寄生虫の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_PARASITE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_JUMP).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ジャンプの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_JUMP);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_BUBBLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:泡の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_BUBBLE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_TURTLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ウミガメの死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_TURTLE);
			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_WATERFLOW).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:水流の死因画像を表示させる
				nowPopUpStress->SetButtonResult(CASE_WATERFLOW);
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
	nowPopUpStress->Release();
}

CRectangle CSceneStressCollection::GetRect(int i)
{
	//死因:体温上昇クリック時
	if (i == CASE_INCREASEDBODYTEMPERATURE && increasedBodyTemperatureFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + increasedBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + increasedBodyTemperatureIconTexture.GetHeight());
	//死因:体温低下クリック時
	if (i == CASE_LOWERBODYTEMPERATURE && lowerBodyTemperatureFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + lowerBodyTemperatureIconTexture.GetWidth(), iconOneLinePosY + lowerBodyTemperatureIconTexture.GetHeight());
	//死因:餓死クリック時
	if (i == CASE_STARVATION && starvationFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + starvationIconTexture.GetWidth(), iconOneLinePosY + starvationIconTexture.GetHeight());
	//死因:喉に刺さるクリック時
	if (i == CASE_CLOGGEDTHROAT && cloggedThroatFlg)
		return CRectangle(iconFirstRowPosX, iconTwoLinePosY, iconFirstRowPosX + cloggedThroatIconTexture.GetWidth(), iconTwoLinePosY + cloggedThroatIconTexture.GetHeight());
	//死因:肥満クリック時
	if(i == CASE_OBESITY && obesityFlg)
		return  CRectangle(iconSecondRowPosX, iconTwoLinePosY, iconSecondRowPosX + obesityIconTexture.GetWidth(), iconTwoLinePosY + obesityIconTexture.GetHeight());
	//死因:障害物と衝突クリック時
	if (i == CASE_IMPACT && impactFlg)
		return CRectangle(iconThirdRowPosX, iconTwoLinePosY, iconThirdRowPosX + impactIconTexture.GetWidth(), iconTwoLinePosY + impactIconTexture.GetHeight());

	//死因:寄生虫クリック時
	if(i == CASE_PARASITE && parasiteFlg)
		return CRectangle(iconFirstRowPosX, iconOneLinePosY, iconFirstRowPosX + parasiteIconTexture.GetWidth(), iconOneLinePosY +parasiteIconTexture.GetHeight());
	//死因:ジャンプクリック時
	if (i == CASE_JUMP && jumpFlg)
		return CRectangle(iconSecondRowPosX, iconOneLinePosY, iconSecondRowPosX + jumpIconTexture.GetWidth(), iconOneLinePosY + jumpIconTexture.GetHeight());
	//死因:泡クリック時
	if(i == CASE_BUBBLE && bubbleFlg)
		return CRectangle(iconThirdRowPosX, iconOneLinePosY, iconThirdRowPosX + bubbleIconTexture.GetWidth(), iconOneLinePosY + bubbleIconTexture.GetHeight());
	//死因:ウミガメ接触クリック時
	if(i == CASE_TURTLE && turtleFlg)
		return CRectangle(icon2PageFirstRowPosX, iconTwoLinePosY, icon2PageFirstRowPosX + turtleIconTexture.GetWidth(), iconTwoLinePosY + turtleIconTexture.GetHeight());
	//死因:水流
	if(i == CASE_WATERFLOW && waterFlowFlg)
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

void CSceneStressCollection::GetStress(int i)
{
	//死因:体温上昇ゲット
	if (i == CASE_INCREASEDBODYTEMPERATURE)
		increasedBodyTemperatureFlg = true;
	//死因:体温低下ゲット
	if (i == CASE_LOWERBODYTEMPERATURE)
		lowerBodyTemperatureFlg = true;
	//死因:餓死ゲット
	if (i == CASE_STARVATION)
		starvationFlg == true;
	//死因:喉詰まりゲット
	if (i == CASE_CLOGGEDTHROAT)
		cloggedThroatFlg = true;
	//死因:肥満ゲット
	if (i == CASE_OBESITY)
		obesityFlg = true;
	//死因:障害物と衝突ゲット
	if (i == CASE_IMPACT)
		impactFlg = true;
	//死因:寄生虫ゲット
	if (i == CASE_PARASITE)
		parasiteFlg = true;
	//死因:ジャンプゲット
	if (i == CASE_JUMP)
		jumpFlg == true;
	//死因:泡ゲット
	if (i == CASE_BUBBLE)
		bubbleFlg = true;
	//死因:ウミガメゲット
	if (i == CASE_TURTLE)
		turtleFlg = true;
	//死因:水流ゲット
	if (i == CASE_WATERFLOW)
		waterFlowFlg = true;
}

void CSceneStressCollection::SaveStressFlg()
{
	FILE* fp = fopen("Save.dat", "wb");
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
	FILE* fp = fopen("Save.dat", "rb");
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