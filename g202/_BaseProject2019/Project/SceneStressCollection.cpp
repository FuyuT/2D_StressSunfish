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

	menuButtonTexture.Load("ButtonMenu.png");
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
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && ButtonGetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
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

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_LOWERBODYTEMPERATURE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:体温低下の死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_STARVATION).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:餓死の死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_CLOGGEDTHROAT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:喉詰まりの死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_OBESITY).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:肥満の死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_IMPACT).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:障害物と衝突の死因画像を表示させる

			}

			if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
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

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_JUMP).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ジャンプの死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_BUBBLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:泡の死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_TURTLE).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:ウミガメの死因画像を表示させる

			}
			else if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(CASE_WATERFLOW).CollisionPoint(mousePosX, mousePosY))
			{
				popUpFlg = true;
				//ポップアップに死因:水流の死因画像を表示させる

			}

			if (g_pInput->IsKeyPush(MOFKEY_LEFT))
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
		lowerBodyTemperatureIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		starvationIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		cloggedThroatIconTexture.Render(iconFirstRowPosX, iconTwoLinePosY);
		obesityIconTexture.Render(iconSecondRowPosX, iconTwoLinePosY);
		impactIconTexture.Render(iconThirdRowPosX, iconTwoLinePosY);
	}
	if (page == 2)
	{
		parasiteIconTexture.Render(iconFirstRowPosX, iconOneLinePosY);
		jumpIconTexture.Render(iconSecondRowPosX, iconOneLinePosY);
		bubbleIconTexture.Render(iconThirdRowPosX, iconOneLinePosY);
		turtleIconTexture.Render(icon2PageFirstRowPosX, iconTwoLinePosY);
		waterFlowIconTexture.Render(icon2pageSecondRowPosX, iconTwoLinePosY);
	}

	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);

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