#include "SceneConfig.h"

CSceneConfig::CSceneConfig()
{

}
CSceneConfig::~CSceneConfig()
{

}
void CSceneConfig::Initialize()
{

}
void CSceneConfig::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
	}
}
void CSceneConfig::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "設定画面");
	CGraphicsUtilities::RenderString(100, 350, "1キーでゲームメニュー");
}
void CSceneConfig::Release()
{

}