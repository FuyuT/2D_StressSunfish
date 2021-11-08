#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Ui.h"
#include "ObstacleManager.h"
#include "Stage.h"
#include "Timer.h"

#define	 MESSAGE_WINDOW_POS_X 210
#define	 MESSAGE_WINDOW_POS_Y 650
#define  FIRST_MESSAGE_POS_X  400
#define  FIRST_MESSAGE_POS_Y  750
#define  MESSAGE_ARRAY_BYTE   500	//���b�Z�[�W�̕�������ύX������������A������ύX����
#define  MESSAGE_DELAY_FRAME  5		//���t���[�����ƂɈꕶ����\�����邩

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

	//�t�H���g
	LPMofChar fontAdd = "Test\\PopRumCute.otf";
	CFont FontPopRumCute;
	
	//�`���[�g���A�����b�Z�[�W
	CTexture		 messageWindowImg;
	char*			 fBuffer;
	int				 fBufferOffset;	  //���ݕ\���ł��Ă���ʒu

	//��x�ɕ\������o�b�t�@ �S�p��(MESSAGE_ARRAY_BYTE/2)�����܂ŕ\���\(�����R�[�hShift_JIS�̏ꍇ)
	char			 fLineBuffer[MESSAGE_ARRAY_BYTE] = "\0";
	int				 mShowDelay;
	bool			 messageEndFlg;
public:
	CSceneTutorial();
	~CSceneTutorial();
	bool TextLoad();
	void FontLoad();
	void MessageUpdate();
	void MessageRender();
	bool Load()override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;


};

