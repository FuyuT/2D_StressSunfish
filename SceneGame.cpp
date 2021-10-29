#include "SceneGame.h"
#include "SceneConfig.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "SceneTrophyCollection.h"
#include "SceneStressCollection.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"
#include "SceneBase.h"

#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;
CSceneTrophyCollection trophy;
CSceneStressCollection caseOfDeth;
CPopUpWindowBase* nowPopUpGame = NULL;
//GameApp�őJ�ڂ���Ɛݒ��ʂ���Q�[���V�[���ɖ߂����ۂɃQ�[���V�[��������������邽�߁A
//�����Ő錾���A�Q�[���V�[���̏ォ��ݒ��ʂ�\������悤�ɂ���B
CSceneConfig sceneConfig;

CSceneGame::CSceneGame():
//scrollValueX(0),
//scrollValueY(0),
deadFlag(false),
posX(0.0f),
posY(0.0f),
poseFlg(false)
{
}

CSceneGame::~CSceneGame()
{
}

bool CSceneGame::Load()
{
	if (!pl.Load())return false;
	if (!ui.Load())return false;
	if (!stg.Load())return false;
	if(!cObstacle.Load())return false;
	return true;
}

void CSceneGame::Initialize()
{
	pl.Initialize();
	ui.Initialize();
	stg.Initialize();
	cObstacle.Initialize();



	//�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//�|�b�v�A�b�v
	popUpFlg = false;

	configFlg = false;
	poseFlg = false;

	trophy.LoadTrophyFlg();
	caseOfDeth.LoadStressFlg();
}

void CSceneGame::Update()
{
	//�f�o�b�O�p�@�G���^�[�ŏ�����
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		Initialize();
	}
	//��ʑJ�� �|�b�v�A�b�v��� 
	//���񂾂�A��������F1�ŃQ�[���I�[�o�[���
	if (g_pInput->IsKeyPush(MOFKEY_F1) || pl.GetDead() && !popUpFlg)
	{
		//�M����
		if(pl.GetCauseOfDeath() + 1 == CASE_INCREASEDBODYTEMPERATURE);
		{
			nowPopUpGame = new CCauseOfDeathWindow;
			nowPopUpGame->Initialize();
			popUpFlg = true;
			nowPopUpGame->SetButtonResult(CASE_INCREASEDBODYTEMPERATURE);
			caseOfDeth.GetStress(CASE_INCREASEDBODYTEMPERATURE);
		}
		nowPopUpGame = new CCauseOfDeathWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
	//R�Ń|�[�Y���
	else if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}

	//�ݒ�\��
	//�Q�[����ʂɖ߂�����configFlg��false
	if (!sceneConfig.GetGamePlayFlg())   //�Q�[���ɖ߂�{�^������������
		configFlg = false;
		
	if (configFlg)
	{
		sceneConfig.Update();
	}
	if (popUpFlg && !configFlg)
	{
		PopUpController();
	}
	//�|�[�Y��ʂ��J���Ă�����A����܂ōX�V���Ȃ�
	if (poseFlg)return;

	//�X�N���[��
	stg.Update(pl);

	//�v���C���[
	pl.Update();

	for (int i = 0; i < 3; i++)
	{
		pl.Collision(cObstacle,i);
	}
	//��Q��
	cObstacle.Update(pl.GetDistance(),pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY());
}

void CSceneGame::Render()
{

	stg.Render();
	/*int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);*/
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	//UI�̕`��
	ui.Render(pl.GetParasite(),pl.GetHungry(),pl.GetBodyTemp(),pl.GetTemperature());

	pl.Render(stg.GetScrollX(), stg.GetScrollY());

	//��Q��
	cObstacle.Render(stg.GetScrollX(), stg.GetScrollY());
	//�|�b�v�A�b�v�`��
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}
	if (configFlg)
	{
		sceneConfig.Render();
	}
}

//�f�o�b�O
void CSceneGame::RenderDebug()
{
	//�v���C���[
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
	//��Q��
	cObstacle.RenderDebug(stg.GetScrollX(), stg.GetScrollY());

	//�f�o�b�O�p
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
} 

void CSceneGame::Release()
{
	stg.Release();
	pl.Release();
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
		nextScene = SCENENO_CONFIG;
		configFlg = true;
		sceneConfig.SetGamePlayFlg();
		sceneConfig.Initialize();
		//�ݒ�̏��������|�b�v�A�b�v�̏������s��Ȃ��̂ŁA������buttonResult��������
		nowPopUpGame->SetButtonResult(0);
	}
	else if (nowPopUpGame->GetButtonResult() == 5)
	{
		//�Q�[���ɖ߂邪�����ꂽ��
		poseFlg = false;
	}


	//�|�b�v�A�b�v�̕ύX
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
			//nowPopUpGame = new CBackToTitleWindow;
			//nowPopUpGame->Initialize();
			break;
		case POPUPNO_RETRY:
			//nowPopUpGame = new CRetryWindow;
			//nowPopUpGame->Initialize();
			break;
		case NULL:
			nowPopUpGame = NULL;
			popUpFlg = false;
			break;
		}
	}
}