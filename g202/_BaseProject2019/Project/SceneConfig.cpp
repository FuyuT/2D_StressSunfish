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
	CGraphicsUtilities::RenderString(100, 300, "�ݒ���");
	CGraphicsUtilities::RenderString(100, 350, "1�L�[�ŃQ�[�����j���[");
}
void CSceneConfig::Release()
{

}