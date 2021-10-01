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
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	torophyButtonTexture.Load("ButtonTrophy.png");
	tutorialButtonTexture.Load("ButtonTutorial.png");
	titleButtonTexture.Load("ButtonTitle.png");

	//��Ńe�L�X�g�f�[�^��ǂݍ���
	gamePlayButtonPosX = 100;
	gamePlayButtonPosY = 400;
	configButtonPosX = 100;
	configButtonPosY = 500;
	stressButtonPosX = 100;
	stressButtonPosY = 600;
	torophyButtonPosX = 100;
	torophyButtonPosY = 700;
	tutorialButtonPosX = 100;
	tutorialButtonPosY = 800;
	titleButtonPosX = 1200;
	titleButtonPosY = 800;
	
}
void CSceneGameMenu::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
	{
		if (GetRect(0).CollisionPoint(mousePosX,mousePosY))
		{
			//�Q�[���v���C���
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
		else if (GetRect(1).CollisionPoint(mousePosX,mousePosY))
		{
			//�ݒ���
			endFlg = true;
			nextScene = SCENENO_CONFIG;
			Release();
		}
		else if (GetRect(2).CollisionPoint(mousePosX,mousePosY))
		{
			//�X�g���X�W���
			endFlg = true;
			nextScene = SCENENO_STRESSCOLLECTION;
			Release();
		}
		else if (GetRect(3).CollisionPoint(mousePosX,mousePosY))
		{
			//�g���t�B�[�W
			endFlg = true;
			nextScene = SCENENO_TROPHY;
			Release();
		}
		else if (GetRect(4).CollisionPoint(mousePosX, mousePosY))
		{
			//�`���[�g���A�����[�h
			flgTutorial = true;
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
		else if (GetRect(5).CollisionPoint(mousePosX, mousePosY))
		{
			//�^�C�g�����
			endFlg = true;
			nextScene = SCENENO_TITLE;
			Release();
		}
	}
}
void CSceneGameMenu::Render()
{
	gamePlayButtonTexture.Render(gamePlayButtonPosX, gamePlayButtonPosY);
	configButtonTexture.Render(configButtonPosX, configButtonPosY);
	stressButtonTexture.Render(stressButtonPosX, stressButtonPosY);
	torophyButtonTexture.Render(torophyButtonPosX, torophyButtonPosY);
	tutorialButtonTexture.Render(tutorialButtonPosX, tutorialButtonPosY);
	titleButtonTexture.Render(titleButtonPosX, titleButtonPosY);

	CGraphicsUtilities::RenderString(100, 300, "�Q�[�����j���[���");
}
void CSceneGameMenu::Release()
{
	gamePlayButtonTexture.Release();
	configButtonTexture.Release();
	stressButtonTexture.Release();
	torophyButtonTexture.Release();
	tutorialButtonTexture.Release();
	titleButtonTexture.Release();
}


/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�j���{�^���̋�`���擾
						1...�ݒ�{�^���̋�`���擾
						2...�X�g���X�W�{�^���̋�`���擾
						3...�g���t�B�[�{�^���̋�`���擾
						4...�`���[�g���A���{�^���̋�`���擾
						5...�^�C�g���{�^���̋�`���擾

		@return			�����ɑΉ������{�^���̋�`
*//**************************************************************************/
CRectangle CSceneGameMenu::GetRect(int i)
{
	if (i == 0)
		return CRectangle(gamePlayButtonPosX, gamePlayButtonPosY, gamePlayButtonPosX + gamePlayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePlayButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(configButtonPosX, configButtonPosY, configButtonPosX + configButtonTexture.GetWidth(), configButtonPosY + configButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(stressButtonPosX, stressButtonPosY, stressButtonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(torophyButtonPosX, torophyButtonPosY, torophyButtonPosX + torophyButtonTexture.GetWidth(), torophyButtonPosY + torophyButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(tutorialButtonPosX, tutorialButtonPosY, tutorialButtonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}