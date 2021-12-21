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
poseFlg(false),
startFlg(false)
{
}

CSceneGame::~CSceneGame()
{
	Release();
}

void CSceneGame::PlayBGM()
{
	cSound->BGMStop();
	cSound->Play(SOUND_GAME_BGM);
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
	pl.SetSoundManager(*cSound);
	ui.SetSoundManager(*cSound);
	sceneConfig.SetSoundManager(*cSound);

	//�C�x���g
	eventRandom.SetSeed((MofU32)time(NULL));
	//�m�F�̂��߂ɃC�x���g�̔����܂ł𑁂����Ă���
	eventTimer.SetTotalTime(20);
	eventNum = Event::Event_None;

	//�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	//�|�b�v�A�b�v
	popUpFlg = false;

	configFlg = false;
	poseFlg = false;
	startFlg = false;

	trophy.LoadTrophyFlg();
	caseOfDeth.LoadStressFlg();
	for (int i = 0; i < 3; i++)
	{
		numberOfTrophy[i] = TROPHY_NULL;
	}
	PlayBGM();
	//cSound->Play(SOUND_READY);
	seFlg = false;
}

void CSceneGame::EventUpdate()
{
	if (!pl.GetDead())
	{
		eventTimer.StartTimer();
		if (eventTimer.GetNowtime() < 0)
		{
			eventNum = eventRandom.Random(Event::Event_Summer, Event_Count);
			seFlg = true;
			eventTimer.SetTotalTime(40);
		}
		else if (eventTimer.GetNowtime() < 20)
		{
			eventNum = Event::Event_None;
		}
		eventTimer.Update();

		if (seFlg)
		{
			if (eventNum == Event::Event_ShoalSardine)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Garbage)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Turtle)
			{
				cSound->Play(SOUND_EVENT_OTHERS);
				seFlg = false;
			}
			if (eventNum == Event::Event_Summer)
			{
				cSound->Play(SOUND_EVENT_SUMMER);
				seFlg = false;
			}
			if (eventNum == Event::Event_Winter)
			{
				cSound->Play(SOUND_EVENT_WINTER);
				seFlg = false;
			}
		}				
	}
	else
	{
		eventNum = Event::Event_None;
	}
}

void CSceneGame::Update()
{
	if (!startFlg) 
		cSound->Play(SOUND_GO);
	//�f�o�b�O�p�@�G���^�[�ŏ�����
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		Initialize();
		if (nowPopUpGame != nullptr)
		{
			nowPopUpGame->Release();
		}
	}

	//��ʑJ�� �|�b�v�A�b�v��� 
	//���񂾂�A��������F1�ŃQ�[���I�[�o�[���
	CaseOfDethController();

	//R�Ń|�[�Y���
	if (g_pInput->IsKeyPush(MOFKEY_R) && !popUpFlg)
	{
		nowPopUpGame = new CPoseWindow;
		nowPopUpGame->SetSoundManager(*cSound);
		nowPopUpGame->Initialize();
		popUpFlg = true;
		poseFlg = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_R) && popUpFlg && !pl.GetDead())
	{
		nowPopUpGame->Release();
		nowPopUpGame = NULL;
		popUpFlg = false;
		poseFlg = false;
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

	ui.Update(eventNum);
	if (!startFlg)
		return;



	//�C�x���g
	EventUpdate();	

	//�v���C���[
	for (int i = 0; i < 5; i++)
	{
		pl.Collision(cObstacle,i,false, Task_End);
	}
	//�v���C���[
	pl.Update(false, Task_End, eventNum);

	//��Q��
	cObstacle.Update(pl.GetDistance(),pl.GetPosX(), stg.GetScrollX(), stg.GetScrollY(), Task_End,eventNum);

}

void CSceneGame::Render()
{
	stg.Render();
	/*int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);*/
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	//UI�̕`��
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetTemperature(), pl.GetDistance(), pl.GetJump(), pl.GetEat(),false,eventNum);
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	if (ui.StartSign(poseFlg))startFlg = true;

	//��Q��
	cObstacle.Render(stg.GetScrollX(), stg.GetScrollY());
	
	//�őO�ʂ̊�w�i
	stg.ForeGroundRender();

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
		sceneConfig.Load();
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
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			TrophyController();
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_POSE:
			nowPopUpGame = new CPoseWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_BACKTOTITLE:
			nowPopUpGame = new CBackToTitleWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
			break;
		case POPUPNO_RETRY:
			nowPopUpGame = new CRetryWindow;
			nowPopUpGame->Initialize();
			nowPopUpGame->SetSoundManager(*cSound);
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
	if ((pl.GetDead()) && !popUpFlg)
	{
		cSound->Play(SOUND_RESULT);
		nowPopUpGame = new CCauseOfDeathWindow;
		switch (pl.GetCauseOfDeath())
		{
			//�M����
		case CAUSE_Hyperthermia:
			nowPopUpGame->SetDethResult(CAUSE_Hyperthermia);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Hyperthermia);
			break;
			//�̉��ቺ
		case CAUSE_Frozen:
			nowPopUpGame->SetDethResult(CAUSE_Frozen);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Frozen);
			break;
			//�쎀
		case CAUSE_Starvation:
			nowPopUpGame->SetDethResult(CAUSE_Starvation);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Starvation);
			break;
			//�A�l�܂�
		case CAUSE_ChokeOnShell:
			nowPopUpGame->SetDethResult(CAUSE_ChokeOnShell);
			newGetDeth = caseOfDeth.GetStress(CAUSE_ChokeOnShell);
			break;
			//�얞
		case CAUSE_Obesity:
			nowPopUpGame->SetDethResult(CAUSE_Obesity);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Obesity);
			break;
			//�Փ�
		case CAUSE_Obstacle:
			nowPopUpGame->SetDethResult(CAUSE_Obstacle);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Obstacle);
			break;
			//�񐶒�
		case CAUSE_Parasite:
			nowPopUpGame->SetDethResult(CAUSE_Parasite);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Parasite);
			break;
			//�W�����v
		case CAUSE_Jump:
			nowPopUpGame->SetDethResult(CAUSE_Jump);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Jump);
			break;
			//�A
		case CAUSE_Bubble:
			nowPopUpGame->SetDethResult(CAUSE_Bubble);
			newGetDeth = caseOfDeth.GetStress(CAUSE_Bubble);
			break;
			//�E�~�K��
		case CAUSE_SeaTurtle:
			nowPopUpGame->SetDethResult(CAUSE_SeaTurtle);
			newGetDeth = caseOfDeth.GetStress(CAUSE_SeaTurtle);
			break;
			//����
		case CAUSE_WaterFlow:
			nowPopUpGame->SetDethResult(CAUSE_WaterFlow);
			newGetDeth = caseOfDeth.GetStress(CAUSE_WaterFlow);
			break;
		case CAUSE_ShoalFish:
			nowPopUpGame->SetDethResult(CAUSE_ShoalFish);
			newGetDeth = caseOfDeth.GetStress(CAUSE_ShoalFish);
			break;
		}
		nowPopUpGame->SetSoundManager(*cSound);
		nowPopUpGame->SetNewGetDeath(newGetDeth);
		nowPopUpGame->Initialize();
		popUpFlg = true;
	}
}

void CSceneGame::TrophyController()
{
	//�싉
	if (pl.GetDistance() > 0)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_RIVER);
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_RIVER;
		//���C�[����
		if (pl.GetDistance() <= 500)
		{
			newGetTrophy = trophy.GetTrophy(TROPHY_ZEROMOTIVATION);
			numberOfTrophy[1] = numberOfTrophy[0];
			numberOfTrophy[0] = TROPHY_ZEROMOTIVATION;
		}
	}
	//�ꋉ
	if (pl.GetDistance() > 1000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_WATERFALL);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_WATERFALL;
	}
	//�΋�
	if (pl.GetDistance() > 2500)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_LAKE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_LAKE;
	}

	//�x�m�R��
	if (3000 <= pl.GetDistance() && pl.GetDistance() < 4000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_MOUNTFJI);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_MOUNTFJI;
	}

	//�_����
	if (pl.GetDistance() > 5000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_DAM);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_DAM;
	}
	//��������
	if (pl.GetDistance() > 10000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEWER);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_SEWER;
	}
	//�C���h�m��
	if (pl.GetDistance() > 25000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_INDIANOCEAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_INDIANOCEAN;
	}
	//���}���\����
	if (42000 <= pl.GetDistance() && pl.GetDistance() < 43000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OSAKAMARATHON);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_OSAKAMARATHON;
	}
	//�A�}�]���싉
	if (pl.GetDistance() > 50000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AMAZONROVER);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_AMAZONROVER;
	}
	//���i�΋�
	if (63000 <= pl.GetDistance() && pl.GetDistance() < 64000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_BIWALAKE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_BIWALAKE;
	}
	//�C��
	if (pl.GetDistance() > 100000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_OCEAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_OCEAN;
	}
	//���{�C��
	if (pl.GetDistance() > 200000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_SEAOFJAPAN);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_SEAOFJAPAN;
	}
	//�n�������
	if ( pl.GetDistance() > 300000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_AROUNDTHEGLOBE);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_AROUNDTHEGLOBE;
	}
	//�W���b�N�|�b�g��
	if (777000 <= pl.GetDistance() && pl.GetDistance() < 778000)
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_JACKPOD);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_JACKPOD;
	}
	//�˔\����
	if (999000 <= pl.GetDistance())
	{
		newGetTrophy = trophy.GetTrophy(TROPHY_TALENTEDDEMON);
		numberOfTrophy[2] = numberOfTrophy[1];
		numberOfTrophy[1] = numberOfTrophy[0];
		numberOfTrophy[0] = TROPHY_TALENTEDDEMON;
	}

	nowPopUpGame->SetNewGetTrophy(newGetTrophy);
	nowPopUpGame->SetDistance(pl.GetDistance());
	nowPopUpGame->SetNumberOfTrophy(numberOfTrophy);
}