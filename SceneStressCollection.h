#pragma once
#include "SceneBase.h"
#include "player.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//�����p�A�C�R���e�N�X�`���ƕ\���t���O�錾
	CTexture	increasedBodyTemperatureIconTexture;	//�̉��㏸
	bool		increasedBodyTemperatureFlg = false;
	CTexture	lowerBodyTemperatureIconTexture;		//�̉��ቺ
	bool		lowerBodyTemperatureFlg = false;
	CTexture	starvationIconTexture;					//�쎀
	bool		starvationFlg = false;
	CTexture	cloggedThroatIconTexture;				//�a���A�Ɏh����
	bool		cloggedThroatFlg = false;
	CTexture	obesityIconTexture;						//�얞
	bool		obesityFlg = false;
	CTexture	impactIconTexture;						//��Q���ƏՓ�
	bool		impactFlg = false;
	CTexture	parasiteIconTexture;					//�񐶒�
	bool		parasiteFlg = false;
	CTexture	jumpIconTexture;						//�W�����v
	bool		jumpFlg = false;
	CTexture	bubbleIconTexture;						//�A
	bool		bubbleFlg = false;
	CTexture	turtleIconTexture;						//�E�~�K��
	bool		turtleFlg = false;
	CTexture	waterFlowIconTexture;					//����
	bool		waterFlowFlg = false;

	//1�y�[�W�ځA2�y�[�W�ڏ�i��X���W
	const int			iconFirstRowPosX = 350;
	const  int			iconSecondRowPosX = 850;
	const int			iconThirdRowPosX = 1350;
	//2�y�[�W�ډ��i��X���W
	const int			icon2PageFirstRowPosX = 600;
	const int			icon2pageSecondRowPosX = 1100;
		//��s�ڂ�Y���W
	const int			iconOneLinePosY = 200;
	//��s�ڂ�Y���W
	const int			iconTwoLinePosY = 500;

	//�y�[�W��
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	const int			menuButtonPosX = 1150;
	const int			menuButtonPosY = 775;
	const int			rightButtonPosX = 950;
	const int			leftButtonPosX = 850;
	const int			leftAndRightButtonPosY = 800;


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
	bool GetStress(int i);

	//�\���t���O�̕ۑ��A�ǂݍ��݊֐�
	void SaveStressFlg();
	void LoadStressFlg();



};

