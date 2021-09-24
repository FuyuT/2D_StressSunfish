#include "SceneTrophyCollection.h"
CSceneTrophyCollection::CSceneTrophyCollection()
{

}
CSceneTrophyCollection::~CSceneTrophyCollection()
{

}
void CSceneTrophyCollection::Initialize()
{

}
void CSceneTrophyCollection::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
	}
}
void CSceneTrophyCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "トロフィー画面");
	CGraphicsUtilities::RenderString(100, 350, "1キーでゲームメニュー");
}
void CSceneTrophyCollection::Release()
{

}