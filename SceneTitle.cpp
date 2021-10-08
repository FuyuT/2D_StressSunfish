#include "SceneTitle.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
	Release();
}

void CSceneTitle::Initialize()
{

}

void CSceneTitle::Update()
{
	if ( g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
	}
}

void CSceneTitle::Render()
{
	buttonTexture.Render(100, 300);
	CGraphicsUtilities::RenderString(100, 350, "1�L�[�ŃQ�[�����j���[");
}

void CSceneTitle::Release()
{
	buttonTexture.Release();
}
