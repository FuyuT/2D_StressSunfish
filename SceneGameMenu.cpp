#include "SceneGameMenu.h"

CSceneGameMenu:: CSceneGameMenu()
{

}

CSceneGameMenu::~CSceneGameMenu()
{
	Release();
}
void CSceneGameMenu::Initialize()
{

}
void CSceneGameMenu::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		//�Q�[���v���C���
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_2))
	{
		//�Q�[���v���C���
		endFlg = true;
		nextScene = SCENENO_GAME;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_3))
	{
		//�ݒ���
		endFlg = true;
		nextScene = SCENENO_CONFIG;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		//�X�g���X�W���
		endFlg = true;
		nextScene = SCENENO_STRESSCOLLECTION;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_5))
	{
		//�g���t�B�[�W
		endFlg = true;
		nextScene = SCENENO_TROPHY;		
	}
}
void CSceneGameMenu::Render()
{
	CGraphicsUtilities::RenderString(100, 300, "�Q�[�����j���[���");
	CGraphicsUtilities::RenderString(100, 350, "1�L�[�Ń^�C�g�����");
	CGraphicsUtilities::RenderString(100, 400, "2�L�[�ŃQ�[�����");
	CGraphicsUtilities::RenderString(100, 450, "3�L�[�Őݒ���");
	CGraphicsUtilities::RenderString(100, 500, "4�L�[�ŃX�g���X�W���");
	CGraphicsUtilities::RenderString(100, 550, "5�L�[�Ńg���t�B�[���");
}
void CSceneGameMenu::Release()
{

}