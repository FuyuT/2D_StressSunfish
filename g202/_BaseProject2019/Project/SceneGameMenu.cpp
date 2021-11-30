#include "SceneGameMenu.h"

CSceneGameMenu:: CSceneGameMenu()
{

}

CSceneGameMenu::~CSceneGameMenu()
{
	Release();
}

void CSceneGameMenu::PlayBGM()
{
	cSound.AllStop();
	cSound.Play(SOUND_MENU_BGM);
}


void CSceneGameMenu::Initialize()
{
	backGroundTex.Load("Title.png");
	textTexture.Load("MenuText.png");
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	trophyButtonTexture.Load("ButtonTrophy.png");
	tutorialButtonTexture.Load("ButtonTutorial.png");
	titleButtonTexture.Load("ButtonTitle.png");	

	PlayBGM();
}

void CSceneGameMenu::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (GetRect(0).CollisionPoint(mousePosX,mousePosY))
	{
		gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�Q�[���v���C���
			endFlg = true;
			nextScene = SCENENO_GAME;
			Release();
		}
	}
	else
	{
		gamePlayButtonScale = 1.0f;
	}
	if (GetRect(1).CollisionPoint(mousePosX,mousePosY))
	{
		configButtonScale = scaleController.ScaleControll(configButtonScale, scaleMax, scaleMini, scaleSpeed);
		
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�ݒ���
			endFlg = true;
			nextScene = SCENENO_CONFIG;
			Release();
		}
	}
	else
	{
		configButtonScale = 1.0f;
	}
	if (GetRect(2).CollisionPoint(mousePosX,mousePosY))
	{
		stressButtonScale = scaleController.ScaleControll(stressButtonScale, scaleMax, scaleMini, scaleSpeed);
			
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�X�g���X�W���
			endFlg = true;
			nextScene = SCENENO_STRESSCOLLECTION;
			Release();
		}
	}
	else
	{
		stressButtonScale = 1.0f;
	}
	if (GetRect(3).CollisionPoint(mousePosX,mousePosY))
	{
		trophyButtonScale = scaleController.ScaleControll(trophyButtonScale, scaleMax, scaleMini, scaleSpeed);
		
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�g���t�B�[�W
			endFlg = true;
			nextScene = SCENENO_TROPHY;
			Release();
		}
	}
	else
	{
		trophyButtonScale = 1.0f;
	}
	if (GetRect(4).CollisionPoint(mousePosX, mousePosY))
	{
		tutorialButtonScale = scaleController.ScaleControll(tutorialButtonScale, scaleMax, scaleMini, scaleSpeed);
			
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�`���[�g���A�����[�h
			flgTutorial = true;
			endFlg = true;
			nextScene = SCENENO_TUTORIAL;
			Release();
		}
	}
	else
	{
		tutorialButtonScale = 1.0f;
	}
	if (GetRect(5).CollisionPoint(mousePosX, mousePosY))
	{
		titleButtonScale = scaleController.ScaleControll(titleButtonScale, scaleMax, scaleMini, scaleSpeed);
		
		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON))
		{
			//�^�C�g�����
			endFlg = true;
			nextScene = SCENENO_TITLE;
			Release();
		}
	}
	else
	{
		titleButtonScale = 1.0f;
	}
}
void CSceneGameMenu::SoundUpdate()
{

}

void CSceneGameMenu::Render()
{
	backGroundTex.Render(0,0);
	scaleController.ScaleRender(&gamePlayButtonTexture,buttonPosX,gamePlayButtonPosY,gamePlayButtonScale);
	scaleController.ScaleRender(&configButtonTexture,buttonPosX,configButtonPosY,configButtonScale);
	scaleController.ScaleRender(&stressButtonTexture,buttonPosX,stressButtonPosY,stressButtonScale);
	scaleController.ScaleRender(&trophyButtonTexture,buttonPosX,trophyButtonPosY,trophyButtonScale);
	scaleController.ScaleRender(&tutorialButtonTexture,buttonPosX,tutorialButtonPosY,tutorialButtonScale);
	scaleController.ScaleRender(&titleButtonTexture,titleButtonPosX,titleButtonPosY,titleButtonScale);
	textTexture.Render(textPosX, textPosY);
}
void CSceneGameMenu::Release()
{
	backGroundTex.Release();
	gamePlayButtonTexture.Release();
	configButtonTexture.Release();
	stressButtonTexture.Release();
	trophyButtonTexture.Release();
	tutorialButtonTexture.Release();
	titleButtonTexture.Release();
	textTexture.Release();
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
		return CRectangle(buttonPosX, gamePlayButtonPosY, buttonPosX + gamePlayButtonTexture.GetWidth(), gamePlayButtonPosY + gamePlayButtonTexture.GetHeight());
	else if (i == 1)
		return CRectangle(buttonPosX, configButtonPosY, buttonPosX + configButtonTexture.GetWidth(), configButtonPosY + configButtonTexture.GetHeight());
	else if (i == 2)
		return CRectangle(buttonPosX, stressButtonPosY, buttonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, trophyButtonPosY,buttonPosX + trophyButtonTexture.GetWidth(), trophyButtonPosY + trophyButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(buttonPosX, tutorialButtonPosY,buttonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}