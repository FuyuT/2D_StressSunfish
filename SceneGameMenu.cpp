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
	if (cSound->GetNowSound() != SOUND_MENU_BGM)
	{
		cSound->BGMStop();
		cSound->Play(SOUND_MENU_BGM);
	}
}


void CSceneGameMenu::Initialize()
{
	FILE* fp = fopen("SaveDeta\\SaveTutorial.dat", "rb");
	if (fp)
	{
		fread(&tutorialFlg, sizeof(bool), 1, fp);
		fclose(fp);
	}

	buttonSelect = 1;
	backGroundTex.Load("Title.png");
	textTexture.Load("MenuText.png");
	gamePlayButtonTexture.Load("ButtonSwimGo.png");
	configButtonTexture.Load("ButtonConfig.png");
	stressButtonTexture.Load("ButtonStressCollection.png");
	trophyButtonTexture.Load("ButtonTrophy.png");
	if(tutorialFlg)
		tutorialButtonTexture.Load("ButtonTutorial.png");
	else
		tutorialButtonTexture.Load("ButtonTutorialBigin.png");

	titleButtonTexture.Load("ButtonTitle.png");	

	PlayBGM();
	bubbleFade.Load();
	bubbleFade.Initialize();
}

void CSceneGameMenu::Update()
{
	//�t�F�[�h����
	bubbleFade.Update();
	bubbleFade.FadeIn();
	if (bubbleFade.GetFade())
	{
		return;
	}
	if (bubbleFade.GetFadeOutEnd())
	{
		//�V�[���̑J��
		endFlg = true;
		nextScene = nextSceneTemp;
		Release();
		return;
	}

	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	MouseCollision(mousePosX, mousePosY);

	//�Q�[���v���C�{�^��
	if (buttonSelect == 1)
	{
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}
		gamePlayButtonScale = scaleController.ScaleControll(gamePlayButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(0).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�Q�[���v���C���
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_GAME;

			//endFlg = true;
			//nextScene = SCENENO_GAME;
			cSound->Play(SOUND_BUTTON_PUSH);
			cSound->Play(SOUND_BUTTON_OK);
			//Release();
		}
	}
	//�ݒ�{�^��
	else if (buttonSelect == 2)
	{
		gamePlayButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		configButtonScale = scaleController.ScaleControll(configButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 3;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(1).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�ݒ���
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_CONFIG;

			//endFlg = true;
			//nextScene = SCENENO_CONFIG;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//�g���t�B�[�W�{�^��
	else if (buttonSelect == 3)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		trophyButtonScale = scaleController.ScaleControll(trophyButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 4;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 2;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 3;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(2).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�g���t�B�[�W
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TROPHY;

			//endFlg = true;
			//nextScene = SCENENO_TROPHY;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//�X�g���X�ꗗ�{�^��
	else if (buttonSelect == 4)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		stressButtonScale = scaleController.ScaleControll(stressButtonScale, scaleMax, scaleMini, scaleSpeed);
			
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 3;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 4;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(3).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�X�g���X�W���
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_STRESSCOLLECTION;

			//endFlg = true;
			//nextScene = SCENENO_STRESSCOLLECTION;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
	}
	//�`���[�g���A���{�^��
	else if (buttonSelect == 5)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		titleButtonScale = scaleMini;

		tutorialButtonScale = scaleController.ScaleControll(tutorialButtonScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 4;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			beforButtonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
			buttonSelect = 6;
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(4).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�`���[�g���A�����[�h
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TUTORIAL;

			tutorialFlg = true;
			//endFlg = true;
			cSound->Play(SOUND_BUTTON_PUSH);
			//nextScene = SCENENO_TUTORIAL;
			FILE* fp = fopen("SaveDeta\\SaveTutorial.dat", "wb");
			if (fp)
			{
				fwrite(&tutorialFlg, sizeof(bool), 1, fp);
				fclose(fp);
			}
			//Release();
		}
	}
	//�^�C�g���{�^��
	else if (buttonSelect == 6)
	{
		gamePlayButtonScale = scaleMini;
		configButtonScale = scaleMini;
		stressButtonScale = scaleMini;
		trophyButtonScale = scaleMini;
		tutorialButtonScale = scaleMini;
		titleButtonScale = scaleController.ScaleControll(titleButtonScale, scaleMax, scaleMini, scaleSpeed);
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			buttonSelect = 1;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			buttonSelect = 5;
			cSound->Play(SOUND_BUTTON_SELECT);
		}
		if (g_pInput->IsKeyPush(MOFKEY_LEFT) || g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			buttonSelect = beforButtonSelect;
			cSound->Play(SOUND_BUTTON_SELECT);
		}

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect(5).CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			//�^�C�g�����
			bubbleFade.FadeOut();
			nextSceneTemp = SCENENO_TITLE;
			//endFlg = true;
			//nextScene = SCENENO_TITLE;
			cSound->Play(SOUND_BUTTON_PUSH);
			//Release();
		}
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
	bubbleFade.Render();
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
	bubbleFade.Release();
}

void CSceneGameMenu::MouseCollision(int posX, int posY)
{
	if (GetRect(0).CollisionPoint(posX, posY) && buttonSelect != 1)
	{
		buttonSelect = 1;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(1).CollisionPoint(posX, posY) && buttonSelect != 2)
	{
		buttonSelect = 2;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(2).CollisionPoint(posX, posY) && buttonSelect != 3)
	{
		buttonSelect = 3;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(3).CollisionPoint(posX, posY) && buttonSelect != 4)
	{
		buttonSelect = 4;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(4).CollisionPoint(posX, posY) && buttonSelect != 5)
	{
		buttonSelect = 5;
		cSound->Play(SOUND_BUTTON_SELECT);
	}
	else if (GetRect(5).CollisionPoint(posX, posY) && buttonSelect != 6)
	{
		buttonSelect = 6;
		cSound->Play(SOUND_BUTTON_SELECT);
		beforButtonSelect = 1;
	}
}

/*************************************************************************//*!
		@brief			�e�{�^���̋�`�̎擾
		@param			0...�j���{�^���̋�`���擾
						1...�ݒ�{�^���̋�`���擾
						2...�g���t�B�[�{�^���̋�`���擾
						3...�X�g���X�W�{�^���̋�`���擾
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
		return CRectangle(buttonPosX, trophyButtonPosY,buttonPosX + trophyButtonTexture.GetWidth(), trophyButtonPosY + trophyButtonTexture.GetHeight());
	else if (i == 3)
		return CRectangle(buttonPosX, stressButtonPosY, buttonPosX + stressButtonTexture.GetWidth(), stressButtonPosY + stressButtonTexture.GetHeight());
	else if (i == 4)
		return CRectangle(buttonPosX, tutorialButtonPosY,buttonPosX + tutorialButtonTexture.GetWidth(), tutorialButtonPosY + tutorialButtonTexture.GetHeight());
	else if (i == 5)
		return CRectangle(titleButtonPosX, titleButtonPosY, titleButtonPosX + titleButtonTexture.GetWidth(), titleButtonPosY + titleButtonTexture.GetHeight());

}