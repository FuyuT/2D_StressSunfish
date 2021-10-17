#include "SceneGame.h"
#include "SceneConfig.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"

#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;
CPopUpWindowBase* nowPopUpGame = NULL;
//GameApp�őJ�ڂ���Ɛݒ��ʂ���Q�[���V�[���ɖ߂����ۂɃQ�[���V�[��������������邽�߁A
//�����Ő錾���A�Q�[���V�[���̏ォ��ݒ��ʂ�\������悤�ɂ���B
CSceneConfig sceneConfig;

CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0),
deadFlag(false),
posX(0.0f),
posY(0.0f)
{
}

CSceneGame::~CSceneGame()
{
}

bool CSceneGame::Load()
{
	//��Q��
	if(!cObstacle.Load())return false;
	return true;
}

void CSceneGame::Initialize()
{
	pl.Initialize();
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");

	ui.Initialize();

	//��Q��
	ene.Initialize();
	ene.Start(scrollValueX, scrollValueY, 0);
	posX = 500;
	posY = 500;
	cObstacle.Initialize();
	//�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//�|�b�v�A�b�v
	popUpFlg = false;

	configFlg = false;
}

void CSceneGame::Update()
{
	//��ʑJ��
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}

	//�X�N���[��
	CRectangle prec = pl.GetRect();
	//�X�N���[����
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�̕��l���̋��E��
	float hsw = sw * 0.4f;
	float hsh = sh * 0.4f;
	//�X�e�[�W�S�̂̕� �Ƃ肠�����摜�̕���
	float stgw = backGroundTexture.GetWidth();
	float stgh = backGroundTexture.GetHeight();
	//��
	if (prec.Left - scrollValueX < hsw)
	{
		//���E��hsw���i�񂾒l���AscrolValue�ɓ����
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//�E
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		if (scrollValueX >= stgw - sw)
		{
			scrollValueX = stgw - sw;
		}
	}
	//��
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//��
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}


	//�Ƃ肠����F1�Ń|�b�v�A�b�v���o��悤��
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		nowPopUpGame = new CCauseOfDeathWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		PopUpController();
	}

	//�v���C���[
	pl.Update();
	pl.Collision(ene);

	//��Q��
	ene.Update();
	cObstacle.Update(scrollValueX, scrollValueY);

	if (!sceneConfig.GetGamePlayFlg())
		configFlg = false;


	//�ݒ�\��
	if (configFlg)
	{
		sceneConfig.Update();
	}
}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	//UI�̕`��
	ui.Render(pl.GetParasite(),pl.GetHungry(),pl.GetBodyTemp(),pl.GetTemperature());

	//�|�b�v�A�b�v�`��
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}
	if (configFlg)
	{
		sceneConfig.Render();
	}

	//��Q��
	cObstacle.Render(scrollValueX, scrollValueY);

}

//�f�o�b�O
void CSceneGame::RenderDebug()
{
	//�v���C���[
	pl.RenderDebug(scrollValueX, scrollValueY);
	//��Q��
	cObstacle.RenderDebug(scrollValueX, scrollValueY);

	//��Q��
	ene.Render(scrollValueX, scrollValueY);
	pl.Render(scrollValueX, scrollValueY);
	//�f�o�b�O�p
	pl.RenderDebug(scrollValueX, scrollValueY);
} 

void CSceneGame::Release()
{
	backGroundTexture.Release();
	pl.Release();
	ene.Release();
	ui.Release();


	if (nowPopUpGame != NULL)
	{
		nowPopUpGame->Release();
		if (nowPopUpGame)
		{
			delete nowPopUpGame;
			nowPopUpGame = NULL;
		}
	}

	//��Q��
	cObstacle.Release();
}

void CSceneGame::PopUpController()
{
	nowPopUpGame->Update();
	if (nowPopUpGame->GetButtonResult() == 1)
	{
		//���g���C�A�������̓R���e�B�j���[�{�^���������ꂽ�珉����
		Initialize();
	}
	else if (nowPopUpGame->GetButtonResult() == 2)
	{
		//���j���[�{�^���������ꂽ�烁�j���[��ʂɑJ��
		nextScene = SCENENO_GAMEMENU;
		endFlg = true;
	}
	else if (nowPopUpGame->GetButtonResult() == 3)
	{
		//�^�C�g���{�^���������ꂽ��^�C�g����ʂɑJ��
		nextScene = SCENENO_TITLE;
		endFlg = true;
	}
	else if (nowPopUpGame->GetButtonResult() == 4)
	{
		//�ݒ肪�����ꂽ��ݒ��ʂ�\��
		configFlg = true;
		sceneConfig.SetGamePlayFlg();
		sceneConfig.Initialize();
	}
	if (nowPopUpGame->IsEnd())
	{
		//���̃|�b�v�A�b�v�̎擾
		short nextPopUp = nowPopUpGame->GetNextPopUp();
		//�Â��|�b�v�A�b�v�̏���
		nowPopUpGame->Release();
		delete nowPopUpGame;
		//���̃|�b�v�A�b�v�ԍ��ɉ����ă|�b�v�A�b�v��������
		switch (nextPopUp)
		{
		case POPUPNO_CAUSEOFDEATH:
			nowPopUpGame = new CCauseOfDeathWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_POSE:
			nowPopUpGame = new CPoseWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_BACKTOTITLE:
			nowPopUpGame = new CBackToTitleWindow;
			nowPopUpGame->Initialize();
			break;
		case POPUPNO_RETRY:
			nowPopUpGame = new CRetryWindow;
			nowPopUpGame->Initialize();
			break;
		case NULL:
			nowPopUpGame = NULL;
			popUpFlg = false;
			break;
		}
	}
}