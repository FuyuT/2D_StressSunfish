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
#include	"SceneTutorial.h"

#include	"SoundManager.h"
CSoundManager cSound(false,false);
//�V�[���N���X
CSceneBase* nowScene = NULL;

//�f�o�b�O�p
bool debugShowFlg = false;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None

		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void) {
	//���\�[�X�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	cSound.Load();
	//�V�[���̏�����
	nowScene = new CSceneTitle;
	nowScene->SetSoundManager(cSound);
	nowScene->Load();
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

	//�f�o�b�O�p
	if (g_pInput->IsKeyPush(MOFKEY_0))
	{
		if (debugShowFlg) debugShowFlg = false;
		else if(!debugShowFlg) debugShowFlg = true;
	}

	//��ʑJ��
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
		case SCENENO_TUTORIAL:
			nowScene = new CSceneTutorial;
			break;
		}
		if (!nowScene->Load())return false;
		nowScene->SetSoundManager(cSound);
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
	if (debugShowFlg)
	{
		nowScene->RenderDebug();
	}
	//�T�E���h
	//if (!cSound.GetMuteBGM())
	//{
	//	CGraphicsUtilities::RenderString(100, 500, "mute����Ȃ�");
	//}
	//else
	//{
	//	CGraphicsUtilities::RenderString(100, 500, "mute��");
	//}

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
	cSound.Release();
	return TRUE;
}