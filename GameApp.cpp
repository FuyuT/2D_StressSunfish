/*************************************************************************//*!

					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneTitle.h"
#include	"SceneGame.h"
#include	"SceneGameMenu.h"
#include	"SceneConfig.h"
#include	"SceneStressCollection.h"
#include	"SceneTrophyCollection.h"

//�V�[���N���X
CSceneBase* nowScene = NULL;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");

	//�V�[���̏�����
	nowScene = new CSceneTitle;
	nowScene->Initialize();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void) {
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	nowScene->Update();
	if (nowScene->IsEnd())
	{
		//���̃V�[���̎擾
		short nextScene = nowScene->GetNextScene();		
		//�Â��V�[���̏���
		delete nowScene;
		//���̃V�[���ԍ��ɉ����ăV�[��������ď�����
		switch (nextScene)
		{
		case SCENENO_TITLE:
			nowScene = new CSceneTitle;
			break;
		case SCENENO_GAME:
			nowScene = new CSceneGame;
			break;
		case SCENENO_GAMEMENU:
			nowScene = new CSceneGameMenu;
			break;
		case SCENENO_CONFIG:
			nowScene = new CSceneConfig;
			break;
		case SCENENO_STRESSCOLLECTION:
			nowScene = new CSceneStressCollection;
			break;
		case SCENENO_TROPHY:
			nowScene = new CSceneTrophyCollection;
			break;
		}
		nowScene->Initialize();
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void) {
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0);
	
	//�V�[���̕`��
	nowScene->Render();

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void) {
	nowScene->Release();
	if (nowScene)
	{
		delete nowScene;
		nowScene = NULL;
	}
	return TRUE;
}