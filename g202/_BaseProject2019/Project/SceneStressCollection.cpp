#include "SceneStressCollection.h"

CSceneStressCollection::CSceneStressCollection()
{

}
CSceneStressCollection::~CSceneStressCollection()
{

}
void CSceneStressCollection::Initialize()
{

}
void CSceneStressCollection::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
	}
}
void CSceneStressCollection::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "�X�g���X�W���");
	CGraphicsUtilities::RenderString(100, 350, "1�L�[�ŃQ�[�����j���[");
}
void CSceneStressCollection::Release()
{

}