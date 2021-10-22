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
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneTrophyCollection::Release();
	}

	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		nowPopUpTrophy->Initialize();
		nowPopUpTrophy->Update();
		if (nowPopUpTrophy->IsEnd())
		{
			popUpFlg = false;
		}
	}
}
void CSceneTrophyCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
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