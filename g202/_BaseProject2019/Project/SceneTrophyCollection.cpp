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
	CGraphicsUtilities::RenderString(100, 300, "�g���t�B�[���");
	CGraphicsUtilities::RenderString(100, 350, "1�L�[�ŃQ�[�����j���[");
}
void CSceneTrophyCollection::Release()
{

}