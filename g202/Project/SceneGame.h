#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "ObstacleManager.h"
#include "Ui.h"
#include "Stage.h"
#include "HeaderDefine.h"
#include "SceneConfig.h"
#include "SceneTrophyCollection.h"
#include "SceneStressCollection.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#include "PoseWindow.h"
#include "BackToTitleWindow.h"
#include "RetryWindow.h"
#include "SceneBase.h"

#define	PLAYER_SPEED 10


class CSceneGame : public CSceneBase
{
private:
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;
	CSceneTrophyCollection trophy;
	CSceneStressCollection caseOfDeth;
	CPopUpWindowBase* nowPopUpGame = NULL;

	//GameApp�őJ�ڂ���Ɛݒ��ʂ���Q�[���V�[���ɖ߂����ۂɃQ�[���V�[��������������邽�߁A
	//�����Ő錾���A�Q�[���V�[���̏ォ��ݒ��ʂ�\������悤�ɂ���B
	CSceneConfig sceneConfig;

	CPlayer pl;
	Stage stg;
	CObstacleManager cObstacle;
	CUi ui;

	int playerX = 100;
	int playerY = 100;

	int distancePlayer = 0;

	Vector2 moveSpeed;
	/*CTexture backGroundTexture;*/
	CTexture playerTexture;

	/*float scrollValueX;
	float scrollValueY;*/

	//��Q��
	int posX;
	int posY;
	CTexture seaTurtleTexture;
	bool deadFlag;

	//�ݒ��ʃt���O
	bool configFlg = false;
	//�|�[�Y��ʃt���O
	bool poseFlg;
	//�V�K����t���O
	bool newGetTrophy;
	bool newGetDeth;
	//�g���t�B�[�p�z��
	int	numberOfTrophy[3];
	
	//�C�x���g
	CRandom eventRandom;
	int		eventNum;
	CTimer	eventTimer;
	//�J�n�t���O
	bool startFlg;

	//SE�t���O
	bool seFlg;
	bool alertFlg;
	bool goFlg;
	bool popUpGuardFlg;
	bool hungryFlg;

	//�w�i�̃I�u�W�F�N�g
	struct BackObject
	{
		CTexture tex;
		int objectTotalNo;
		Vector2* pos;
	};
	BackObject kelp;


public:
	CSceneGame();
	~CSceneGame();
	void PlayBGM() override;
	bool Load()override;
	void Initialize() override;
	void EventUpdate();
	void Update() override;
	void Render() override;
	void RenderDebug() override;
	void Release() override;
	void SEUpdate();

	CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};
		/*
	//�ǉ�
	float GetScrollX()
	{
		return scrollValueX;
	};
	float GetScrollY()
	{
		return scrollValueY;
	}
	*/
	/*CRectangle GetRect() {
		return CRectangle(playerX, playerY, playerX + playerTexture.GetWidth() , playerY + playerTexture.GetHeight());
	};*/

	/*CRectangle GetRect()
	{
		return CRectangle(
			ePosX,
			ePosY,
			ePosX + 100,
			ePosY + 100
		);
	}
	int GetType()
	{
		return 0;
	}*/


	void PopUpController();
	void CaseOfDethController();
	void TrophyController();
};

