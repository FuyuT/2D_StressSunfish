#pragma once

#include "Mof.h"
#include "ObstacleManager.h"
#include "timer.h"
#include "time.h"

//�����ʒu X
#define		STARTPOS_X				200

//���W��i�񂾋����ɕϊ����銄��
#define		TRANSLATE_DISTANCE		10

//�ړ����x	
#define		PLAYER_SPEED			0.6f
//�ő呬�x
#define		PLAYER_MAXSPEED			10.0f
//�d��
#define		GRAVITY					1.0f

//�����蔻��̕�����
#define		COLLISION_ADJUSTMENT_TOP	100.0f
#define		COLLISION_ADJUSTMENT_LEFT	110.0f
#define		COLLISION_ADJUSTMENT_RIGHT	150.0f
#define		COLLISION_ADJUSTMENT_BOTTOM	160.0f

//�G�T�T�m�͈�
#define		FEED_SEARCHRANGE		60.0f
//�e�N�X�`���̕�(��)
#define		TEXTURE_SIZE			384

//�W�����v��
#define		JUMP_POWER_X			9.0f
#define		JUMP_POWER_Y			30.0f
//�W�����v��ɐ����
#define		WATER_LANDING_DEEP		50.0f
//�C�ʂ���ǂ��܂ł��W�����v�\��
#define		JUMP_ZONE				40.0f

//�C��
#define		SEA_LEVEL				780
//�C��
#define		UNDER_SEA				2160

//�������󂭓x����
#define		HUNGRYLEVEL				0.05f
//�G�T��H�ׂ��Ƃ��ɓ����閞���x
#define		FEED_SATIETYLEVEL		36.0f
//����
#define		FULL_STOMACH			20
//�쎀
#define		STARVATION				85
//�����G�T����x�ɉ�ʂɏo�Ă���ő吔
#define FEED_MAXCOUNT 3

//�񐶒����e���E��
#define		PARASITE_LIMIT			5

//�̉����ϓ�����x����(����)
#define		TEMPERATURE_LEVEL		0.13f
//�W���̉�
#define		STANDARD_TEMPERATURE	10
//�̉����E�l(�M����)
#define		HYPERTHERMIA_LIMIT		0
//�̉����E�l(����)
#define		FROZEN_LIMIT			100
//�̉��ϓ����
#define		TEMPERATURE_CHANGEZONE	500

//�����ɂ��ő�����x
#define		WATERFLOW_MAXSPEED		1.5f
//�����ɂ������x
#define		WATERFLOW_SPEED			0.02f

//�����ꗗ
enum CAUSE_OF_DEATH
{
	CAUSE_None,				//����ł��Ȃ�
	CAUSE_Hyperthermia,     //�M����(���x)			
	CAUSE_Frozen,			//����(���x)			
	CAUSE_Starvation,		//�쎀(�󕠓x�E�G�T)	
	CAUSE_ChokeOnShell,		//�A�܂�(�G�T)		
	CAUSE_Obesity,			//�얞(�G�T)			
	CAUSE_Obstacle,			//�Փ�(��Q��)		
	CAUSE_Parasite,			//�񐶒�	
	CAUSE_Jump,				//�W�����v								
	CAUSE_Bubble,			//�A					
	CAUSE_SeaTurtle,		//�V���b�N��(�E�~�K��)
	CAUSE_WaterFlow,		//�}�ȉ���(����)

};

//�A�j���[�V�������
enum MOTION
{
	MOTION_STAND,
	MOTION_EAT,
	MOTION_JUMP,
	MOTION_DEATH,

	MOTION_COUNT,
};

class CPlayer
{
private:

	//�e�N�X�`��
	CTexture	standTexture;
	CTexture	eatTexture;
	CTexture	jumpTexture;
	CTexture	deathTexture;
	//�m��
	CRandom		random;
	//���W
	float		posX;
	float		posY;
	//���x
	float		moveX;
	float		moveY;
	//���x�̔{��
	float		moveSpeed;
	//�W�����v
	bool		jumpFlg;
	bool		jumpDangerFlg;
	CTimer		jumpDangerTimer;
	//�����Ă��邩��\���t���O
	bool		deadFlg;
	//�A�N�V�����\�ł��邩�\���t���O
	bool		possibleToJumpFlg;
	bool		possibleToEatFlg[FEED_MAXCOUNT];
	//����
	int			causeOfDeath;
	//���G(�A���œ�����Q���ɂԂ��葱���Ă��܂����߁A�Փˌ�͉��������܂Ŗ��G�ɂ���)
	bool		hitFlg;
	CTimer		hitTimer;

	//�X�e�[�^�X( ��� �Ɋւ���ϐ�)
	//�̉�
	int         bodyTemp;
	float       tempRegion;
	//��
	float       hungerRegion;
	//�񐶒�
	int			parasite;
	//����
	CTimer		waterFlowTimer;
	bool		waterFlowFlg;
	//�A�j���[�V����
	CSpriteMotionController	motion;

	//�u���[�L(�e�X�g)
	CTimer		brakeTimer;

	//UI
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;

	//�`���[�g���A���p
	bool	jumpTaskFlg;
	bool	eatTaskFlg;
	int		taskCompleteStep;
	CTimer	moveUpTaskTimer;
	CTimer	moveDownTaskTimer;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove();
	//�m���Ŏ��� 100������؂�鐔�̂ݑΉ�(1,2,4,5,10,20,25,50,100)
	bool DieInPercentage(int percent)
	{
		//�m���ɂ����true��Ԃ�
		if (random.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}
	//�H�ׂ�
	//�����Ă����true���A�����łȂ����false������ �A�܂���N�������ǂ����̔��f�Ɏg��
	bool Eat(bool rottenFlg, bool unDeadFlg, int tutorialStep);
	//�W�����v
	void Jump(bool unDeadFlg, int tutorialStep);
	void UpdateStatus(bool unDeadFlg,int tutorialStep);

	//Update�̈����ɂ���
	// 
	//unDeadFlg
	//true : ���ȂȂ��Ȃ�(�`���[�g���A���p)
	//false: ���ʂ悤�ɂȂ�(�ʏ�v���C�p)
	// 
	//tutorialStep
	//0     : �㉺�ړ��̂݉\
	//1     : �㉺�ړ��ɉ����A�u�W�����v�v�A�u�H�ׂ�v���\
	//3�ȏ� : �`���[�g���A���̏I���A�����Ȃ��v���C�\
	void Update(bool unDeadFlg,int tutorialStep);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release();

	//�v���C���[�̍��W��Ԃ�
	int GetPosX()
	{
		return (int)posX;
	};
	int GetPosY()
	{
		return (int)posY;
	};

	//�v���C���[���g�̓����蔻���Ԃ�
	CRectangle GetRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT_LEFT,
			posY + COLLISION_ADJUSTMENT_TOP,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT,
			posY + TEXTURE_SIZE - COLLISION_ADJUSTMENT_BOTTOM
		);
	}

	//�G�T���H�ׂ���͈͂ɂ��邩�𔻒f���邽�߂̓����蔻��
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT_LEFT - FEED_SEARCHRANGE,
			posY + COLLISION_ADJUSTMENT_TOP - FEED_SEARCHRANGE,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT + FEED_SEARCHRANGE,
			posY + TEXTURE_SIZE - COLLISION_ADJUSTMENT_BOTTOM + FEED_SEARCHRANGE
		);
	}
	CRectangle GetEyeRect()
	{
		return CRectangle(
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_LEFT - 70,
			posY + COLLISION_ADJUSTMENT_TOP + 30,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT,
			posY + COLLISION_ADJUSTMENT_BOTTOM
		);
	}

	void Collision(CObstacleManager& cObstacle,int num,bool unDeadFlg, int tutorialStep);

	//����ł����true��Ԃ�
	bool GetDead()
	{
		return deadFlg;
	}
	//�̉���Ԃ� 100 �` 0
	float	GetTemperature()
	{
		return tempRegion;
	}
	int     GetBodyTemp()
	{
		return bodyTemp;
	}
	//�񐶒��̕t������Ԃ� 0 �` 6
	int GetParasite()
	{
		return parasite;
	}
	//�󕠓x��Ԃ� 10�`0
	float GetHungry()
	{
		return hungerRegion;
	}
	//������Ԃ�
	int GetCauseOfDeath()
	{
		return causeOfDeath;
	}
	//�i�񂾋���(m��)��Ԃ�
	int GetDistance()
	{
		//X���W��20����1(�K��)��i�񂾋����Ƃ���
		return ((posX - STARTPOS_X) / TRANSLATE_DISTANCE);
	}
	//�u�W�����v�v���\����Ԃ�
	bool GetJump()
	{
		return possibleToJumpFlg;
	}
	//�u�H�ׂ�v���\����Ԃ�
	bool GetEat()
	{
		for (int i = 0; i < FEED_MAXCOUNT; i++)
		{
			//�ǂꂩ��ł�true�ł����
			if (possibleToEatFlg[i])
			{
				return true;
			}
		}
		return false;
	}

	//�`���[�g���A���p�֐�
	bool GetMoveUpTask()
	{
		if(moveUpTaskTimer.GetNowtime() < 0)
			return true;
		return false;
	}
	bool GetMoveDownTask()
	{
		if(moveDownTaskTimer.GetNowtime() < 0)
			return true;
		return false;
	}
	bool GetJumpTask()
	{
		return jumpTaskFlg;
	}
	bool GetEatTask()
	{
		return eatTaskFlg;
	}
	int GetTaskCompleteStep()
	{
		return taskCompleteStep;
	}
};

