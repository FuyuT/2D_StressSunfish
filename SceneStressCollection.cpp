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
	menuButtonTexture.Load("ButtonMenu.png");
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
}
void CSceneStressCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneStressCollection::Release();
	}

	//とりあえずF1でポップアップが出るように
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		nowPopUpStress->Initialize();
		nowPopUpStress->Update();
		if (nowPopUpStress->IsEnd())
		{
			popUpFlg = false;
		}
	}
}
void CSceneStressCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ストレス集画面");
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}
}
void CSceneStressCollection::Release()
{
	menuButtonTexture.Release();
	nowPopUpStress->Release();
}