#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"

#define	 MESSAGE_WINDOW_POS_X 210
#define	 MESSAGE_WINDOW_POS_Y 650
#define  FIRST_LETTER_POS_X   400
#define  FIRST_LETTER_POS_Y   750

class CSceneTutorial : public CSceneBase
{
private:
	Stage			 stg;
	CUi				 ui;
	CPlayer			 pl;
	CObstacleManager obs;

	//�^�C�}�[
	CTimer			 tempTimer;
	CTimer			 hungerTimer;
	CTimer			 parasiteTimer;

	//�`���[�g���A�����b�Z�[�W
	CTexture		 messageWindowImg;
	char*			 fBuffer;
	int				 fBufferOffset;			//���ݕ\���ł��Ă���ʒu
	char			 fLineBuffer[256] = "\0";		//��x�ɕ\������o�b�t�@
	int				 mShowDelay;
public:
	CSceneTutorial();
	~CSceneTutorial();
	bool Load()override;
	bool TextLoad();
	void Initialize() override;
	void Update() override;
	void MessageUpdate();
	void Render() override;
	void RenderDebug() override;
	void Release() override;


};

