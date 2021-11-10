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
	Release();
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
	for (int i = 0; i < 3; i++)
	{
		numberOfTrophy[i] = TROPHY_NULL;
	}
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
	CaseOfDethController();

	//R�Ń|�[�Y���
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
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
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat());

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
	sceneConfig.Release();

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
			TrophyController();
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

void CSceneGame::CaseOfDethController()
{
	if ((g_pInput->IsKeyPush(MOFKEY_F1) || pl.GetDead()) && !popUpFlg)
	{
		nowPopUpGame = new CCauseOfDeathWindow;
		switch (pl.GetCauseOfDeath() - 1)
		{
			//�M����
		case CASE_INCREASEDBODYTEMPERATURE:
			nowPopUpGame->SetDethResult(CASE_INCREASEDBODYTEMPERATURE);
			newGetDeth = caseOfDeth.GetStress(CASE_INCREASEDBODYTEMPERATURE);
			break;
			//�̉��ቺ
		case CASE_LOWERBODYTEMPERATURE:
			nowPopUpGame->SetDethResult(CASE_LOWERBODYTEMPERATURE);
			newGetDeth = caseOfDeth.GetStress(CASE_LOWERBODYTEMPERATURE);
			break;
			//�쎀
		case CASE_STARVATION:
			nowPopUpGame->SetDethResult(CASE_STARVATION);
			newGetDeth = caseOfDeth.GetStress(CASE_STARVATION);
			break;
			//�A�l�܂�
		case CASE_CLOGGEDTHROAT:
			nowPopUpGame->SetDethResult(CASE_CLOGGEDTHROAT);
			newGetDeth = caseOfDeth.GetStress(CASE_CLOGGEDTHROAT);
			break;
			//�얞
		case CASE_OBESITY:
			nowPopUpGame->SetDethResult(CASE_OBESITY);
			newGetDeth = caseOfDeth.GetStress(CASE_OBESITY);
			break;
			//�Փ�
		case CASE_IMPACT:
			nowPopUpGame->SetDethResult(CASE_IMPACT);
			newGetDeth = caseOfDeth.GetStress(CASE_IMPACT);
			break;
			//�񐶒�
		case CASE_PARASITE:
			nowPopUpGame->SetDethResult(CASE_PARASITE);
			newGetDeth = caseOfDeth.GetStress(CASE_PARASITE);
			break;
			//�W�����v
		case CASE_JUMP:
			nowPopUpGame->SetDethResult(CASE_JUMP);
			newGetDeth = caseOfDeth.GetStress(CASE_JUMP);
			break;
			//�A
		case CASE_BUBBLE:
			nowPopUpGame->SetDethResult(CASE_BUBBLE);
			newGetDeth = caseOfDeth.GetStress(CASE_BUBBLE);
			break;
			//�E�~�K��
		case CASE_TURTLE:
			nowPopUpGame->SetDethResult(CASE_TURTLE);
			newGetDeth = caseOfDeth.GetStress(CASE_TURTLE);
			break;
			//����
		case CASE_WATERFLOW:
			nowPopUpGame->SetDethResult(CASE_WATERFLOW);
			newGetDeth = caseOfDeth.GetStress(CASE_WATERFLOW);
			break;
		}
		nowPopUpGame->SetNewGetDeth(newGetDeth);
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
}

void CSceneGame::TrophyController()
{
	//�싉
	if (pl.GetDistance() <= 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_RIVER);
		numberOfTrophy[0] = TROPHY_RIVER;
	}
	//�ꋉ
	else if (pl.GetDistance() <= 50000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_WATERFALL);
		numberOfTrophy[0] = TROPHY_WATERFALL;
	}
	//�΋�
	else if (pl.GetDistance() <= 100000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_LAKE);
		numberOfTrophy[0] = TROPHY_LAKE;
	}
	//�_����
	else if (pl.GetDistance() <= 500000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_DAM);
		numberOfTrophy[0] = TROPHY_DAM;
	}
	//��������
	else if (pl.GetDistance() <= 1000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEWER);
		numberOfTrophy[0] = TROPHY_SEWER;
	}
	//�C���h�m��
	else if (pl.GetDistance() <= 3000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_INDIANOCEAN);
		numberOfTrophy[0] = TROPHY_INDIANOCEAN;
	}
	//�A�}�]���싉
	else if (pl.GetDistance() <= 5000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AMAZONROVER);
		numberOfTrophy[0] = TROPHY_AMAZONROVER;
	}
	//�C��
	else if (pl.GetDistance() <= 10000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OCEAN);
		numberOfTrophy[0] = TROPHY_OCEAN;
	}
	//���{�C��
	else if (pl.GetDistance() <= 30000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEAOFJAPAN);
		numberOfTrophy[0] = TROPHY_SEAOFJAPAN;
	}
	//�n�������
	else if (pl.GetDistance() <= 40000000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AROUNDTHEGLOBE);
		numberOfTrophy[0] = TROPHY_AROUNDTHEGLOBE;
	}

	//���ʋ�
	//���C�[����
	if (pl.GetDistance() < 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_ZEROMOTIVATION);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_ZEROMOTIVATION;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_ZEROMOTIVATION;
		}
	}
	//�x�m�R��
	if (3000 <= pl.GetDistance() <= 5000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_MOUNTFJI);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_MOUNTFJI;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_MOUNTFJI;
		}
	}
	//���}���\����
	if (20000 <= pl.GetDistance() <= 42000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OSAKAMARATHON);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_OSAKAMARATHON;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_OSAKAMARATHON;
		}
	}
	//���i�΋�
	if (40000 <= pl.GetDistance() <= 63000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_BIWALAKE);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_BIWALAKE;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_BIWALAKE;
		}
	}
	//�W���b�N�|�b�g��
	if (777000 <= pl.GetDistance() <= 888000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_JACKPOD);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_JACKPOD;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_JACKPOD;
		}
	}
	//�˔\����
	if (99999000 <= pl.GetDistance())
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_TALENTEDDEMON);
		if (numberOfTrophy[1] == TROPHY_NULL)
		{
			numberOfTrophy[1] = TROPHY_TALENTEDDEMON;
		}
		else if (numberOfTrophy[2] == TROPHY_NULL)
		{
			numberOfTrophy[2] = TROPHY_TALENTEDDEMON;
		}
	}

	nowPopUpGame->SetNumberOfTrophy(numberOfTrophy);
}