#pragma once

#include "Mof.h"
#include "ObstacleManager.h"
#include "timer.h"
#include "time.h"

//�ړ����x	
#define		PLAYER_SPEED			0.6f
//�ő呬�x
#define		PLAYER_MAXSPEED			10.0f
//�G�T�T�m�͈�
#define		FEED_SEARCHRANGE		60.0f
//�����蔻��̕�����
#define		COLLISION_ADJUSTMENT	130.0f
//�d��
#define		GRAVITY					1.0f
//�W�����v��
#define		JUMP_POWER_X			8.0f
#define		JUMP_POWER_Y			30.0f

//�C��
#define		SEA_LEVEL				780
//�C��
#define		UNDER_SEA				2160


//�X�e�[�^�X( ��� �Ɋւ���萔)

//�G�T��H�ׂ��Ƃ��ɓ����閞���x
#define		FEED_SATIETYLEVEL		3
//����������(�󕠂ɂȂ�)���x
#define		HUNGRY_SPEED			300
//����
#define		FULL_STOMACH			10
//�񐶒��̑����鑬�x
#define		PARASITE_SPEED			10
//�ő�񐶒����e��
#define		PARASITE_LIMIT			300
//�̉����㉺���鑬�x
#define		TEMPERATURE_SPEED		40
//�̉����E�l
#define		TEMPERATURE_LIMIT		100
//�����ɂ��ړ����xup�̎�������
#define		STREAM					200 
//�̉��ϓ����
#define		TEMPERATURE_CHANGEZONE	500

enum CAUSE_OF_DEATH
{
	CAUSE_None,				//����ł��Ȃ�
	CAUSE_Hyperthermia,     //�M����(���x)			
	CAUSE_Frozen,			//����(���x)			
	CAUSE_Starvation,		//�쎀(�󕠓x�E�G�T)	
	CAUSE_ChokeOnShell,		//�A�܂�(�G�T)		
	CAUSE_Obesity,			//�얞(�G�T)			
	CAUSE_Obstacle,			//�Փ�(��Q��)			
	CAUSE_Jump,				//�W�����v				
	CAUSE_Parasite,			//�񐶒�				
	CAUSE_Bubble,			//�A					
	CAUSE_SeaTurtle			//�V���b�N��(�E�~�K��)	

};


class CPlayer
{
private:
	//�e�N�X�`��
	CTexture	texture;
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
	//�W�����v���Ă��邩��\���t���O
	bool		jumpFlg;
	//�����Ă��邩��\���t���O
	bool		deadFlg;
	//�A�N�V�����\�ł��邩�\���t���O
	bool		possibleToJumpFlg;
	bool		possibleToEatFlg;
	//����
	int			causeOfDeath;
	//���G(�A���œ�����Q���ɂԂ��葱���Ă��܂����߁A�Փˌ�͉�������܂Ŗ��G�ɂ���(�f�o�b�O�p))
	bool		hitFlg;


	//�g��񂩂�
	//�X�e�[�^�X( ��� �Ɋւ���ϐ�)
	//�̉�
	int			temperature;
	int			temperatureTime;
	int         bodyTemp;
	float       tempRegion;
	//��
	int			hungry;
	int			hungryTime;
	int         hungerRegion;
	//�񐶒�
	int			parasite;
	int			parasiteTime;
	//����
	int			streamTime;

	//UI
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;

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
	bool Eat();
	//�W�����v
	void Jump();
	void UpdateStatus();
	void Update();
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
			posX + COLLISION_ADJUSTMENT,
			posY + COLLISION_ADJUSTMENT,
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT,
			posY + texture.GetHeight() - COLLISION_ADJUSTMENT
		);
	}

	//�G�T���H�ׂ���͈͂ɂ��邩�𔻒f���邽�߂̓����蔻��
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT - FEED_SEARCHRANGE,
			posY + COLLISION_ADJUSTMENT - FEED_SEARCHRANGE,
			posX + texture.GetWidth() - COLLISION_ADJUSTMENT + FEED_SEARCHRANGE,
			posY + texture.GetHeight() - COLLISION_ADJUSTMENT + FEED_SEARCHRANGE
		);
	}

	void Collision(CObstacleManager& cObstacle);

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
	int GetHungry()
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
		//�����ʒu��20(�K��)������
		//X���W��20����1(�K��)��i�񂾋����Ƃ���
		return (posX - 200) / 20;
	}
	//�u�W�����v�v���\����Ԃ�
	bool GetJump()
	{
		return possibleToJumpFlg;
	}
	//�u�H�ׂ�v���\����Ԃ�
	bool GetEat()
	{
		return possibleToEatFlg;
	}

};

