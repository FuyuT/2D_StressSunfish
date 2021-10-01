#include "SceneStressCollection.h"

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
}
void CSceneStressCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneStressCollection::Release();
	}
}
void CSceneStressCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "ストレス集画面");
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
}
void CSceneStressCollection::Release()
{
	menuButtonTexture.Release();
}