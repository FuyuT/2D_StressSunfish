#pragma once

#include "Mof.h"
#include "Enemy.h"
#include "time.h"

//�ړ����x
#define		PLAYER_SPEED		0.6f
//�ő呬�x
#define		PLAYER_MAXSPEED		10.0f
//�G�T�T�m�͈�
#define		FEED_SEARCHRANGE	60.0f
//�d��
#define		GRAVITY				1.0f
//�W�����v��
#define		JUMP_POWER_X		8.0f
#define		JUMP_POWER_Y		30.0f
//�C��
#define		SEA_LEVEL			780
//�C��
#define		UNDER_SEA			2160


//�X�e�[�^�X( ��� �Ɋւ���萔)

//�G�T��H�ׂ��Ƃ��ɓ����閞���x
#define		FEED_SATIETYLEVEL	3
//�󕠂ɂȂ鑬�x
#define		HUNGRY_SPEED		150
//����
#define		FULL_STOMACH		10
//�񐶒��̑����鑬�x
#define		PARASITE_SPEED		30
//�ő�񐶒����e��
#define		PARASITE_LIMIT		100
//�̉����㉺���鑬�x
#define		TEMPERATURE_SPEED	30
//�̉����E�l
#define		TEMPERATURE_LIMIT	100


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
	//�W�����v���s���O��Y���W
	float		beforeJumpingPosY;
	//�W�����v���Ă��邩��\���t���O
	bool		jumpFlg;
	//�����Ă��邩��\���t���O
	bool		deadFlg;
	//�A�N�V�����\�ł��邩�\���t���O
	bool		jumpPossibleFlg;
	bool		eatPossibleFlg;

	//�g��񂩂�
	//�X�e�[�^�X( ��� �Ɋւ���ϐ�)
	//�̉�
	int			temperature;
	int			temperatureTime;
	//��
	int			hungry;
	int			hungryTime;
	//�񐶒�
	int			parasite;
	int			parasiteTime;

public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove();
	//�m���Ŏ���
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
	void Eat();
	//�W�����v
	void Jump();
	void Update();
	void Render(float wx,float wy);
	void RenderDebug();
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
			posX,
			posY,
			posX + texture.GetWidth(),
			posY + texture.GetHeight()
		);
	}

	//�G�T���H�ׂ���͈͂ɂ��邩�𔻒f���邽�߂̓����蔻��
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX - FEED_SEARCHRANGE,
			posY - FEED_SEARCHRANGE,
			posX + texture.GetWidth() + FEED_SEARCHRANGE,
			posY + texture.GetHeight() + FEED_SEARCHRANGE
		);
	}

	void Collision(Enemy& ene);

	bool IsDead()
	{
		return deadFlg;
	}
};

