#pragma once
#include "SceneBase.h"

//�����̗�
enum tag_CASE {
	CASE_INCREASEDBODYTEMPERATURE,	//�̉��㏸
	CASE_LOWERBODYTEMPERATURE,		//�̉��ቺ
	CASE_STARVATION,				//�쎀
	CASE_CLOGGEDTHROAT,				//�a���A�Ɏh����
	CASE_OBESITY,					//�얞
	CASE_IMPACT,					//��Q���ƏՓ�
	CASE_PARASITE,					//�񐶒�
	CASE_JUMP,						//�W�����v
	CASE_BUBBLE,					//�A
	CASE_TURTLE,					//�E�~�K��
	CASE_WATERFLOW,					//����
};

class CSceneStressCollection : public CSceneBase
{
private:
	//�����p�A�C�R���e�N�X�`���ƕ\���t���O�錾
	CTexture	increasedBodyTemperatureIconTexture;	//�̉��㏸
	bool		increasedBodyTemperatureFlg = true;
	CTexture	lowerBodyTemperatureIconTexture;		//�̉��ቺ
	bool		lowerBodyTemperatureFlg = true;
	CTexture	starvationIconTexture;					//�쎀
	bool		starvationFlg = true;
	CTexture	cloggedThroatIconTexture;				//�a���A�Ɏh����
	bool		cloggedThroatFlg = true;
	CTexture	obesityIconTexture;						//�얞
	bool		obesityFlg = true;
	CTexture	impactIconTexture;						//��Q���ƏՓ�
	bool		impactFlg = true;
	CTexture	parasiteIconTexture;					//�񐶒�
	bool		parasiteFlg = true;
	CTexture	jumpIconTexture;						//�W�����v
	bool		jumpFlg = true;
	CTexture	bubbleIconTexture;						//�A
	bool		bubbleFlg = true;
	CTexture	turtleIconTexture;						//�E�~�K��
	bool		turtleFlg = true;
	CTexture	waterFlowIconTexture;					//����
	bool		waterFlowFlg = true;

	//1�y�[�W�ځA2�y�[�W�ڏ�i��X���W
	int			iconFirstRowPosX = 350;
	int			iconSecondRowPosX = 850;
	int			iconThirdRowPosX = 1350;
	//2�y�[�W�ډ��i��X���W
	int			icon2PageFirstRowPosX = 600;
	int			icon2pageSecondRowPosX = 1100;
		//��s�ڂ�Y���W
	int			iconOneLinePosY = 200;
	//��s�ڂ�Y���W
	int			iconTwoLinePosY = 500;

	//�y�[�W��
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	int			menuButtonPosX = 1200;
	int			menuButtonPosY = 800;
	int			rightButtonPosX = 950;
	int			leftButtonPosX = 850;
	int			leftAndRightButtonPosY = 800;


public:
	CSceneStressCollection();
	~CSceneStressCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle ButtonGetRect(int i);
	CRectangle GetRect( int i);

	//�Q�[���V�[���Ńt���O��ς��邽�߂̊֐�
	void GetStress(int i);

	//�\���t���O�̕ۑ��A�ǂݍ��݊֐�
	void SaveStressFlg();
	void LoadStressFlg();
};

