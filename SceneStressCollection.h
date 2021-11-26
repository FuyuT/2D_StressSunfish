#pragma once
#include "SceneBase.h"
#include "player.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//�����p�A�C�R���e�N�X�`���ƕ\���t���O�錾
	CTexture	hyperthermiaTexture;	//�̉��㏸
	bool		hyperthermiaFlg = false;
	float		hyperthermiaScale = 1.0f;
	CTexture	lowerBodyTemperatureTexture;		//�̉��ቺ
	bool		lowerBodyTemperatureFlg = false;
	float		lowerBodyTemperatureScale = 1.0f;
	CTexture	starvationTexture;					//�쎀
	bool		starvationFlg = false;
	float		starvationScale = 1.0f;
	CTexture	cloggedThroatexture;				//�a���A�Ɏh����
	bool		cloggedThroatFlg = false;
	float		cloggedThroatScale = 1.0f;
	CTexture	obesityTexture;						//�얞
	bool		obesityFlg = false;
	float		obesityScale = 1.0f;
	CTexture	impactTexture;						//��Q���ƏՓ�
	bool		impactFlg = false;
	float		impactScale = 1.0f;
	CTexture	parasiteIconTexture;					//�񐶒�
	bool		parasiteFlg = false;
	float		parasiteScale = 1.0f;
	CTexture	jumpTexture;						//�W�����v
	bool		jumpFlg = false;
	float		jumpScale = 1.0f;
	CTexture	bubbleTexture;						//�A
	bool		bubbleFlg = false;
	float		bubbleScale = 1.0f;
	CTexture	turtleTexture;						//�E�~�K��
	bool		turtleFlg = false;
	float		turtleScalse = 1.0;
	CTexture	waterFlowTexture;					//����
	bool		waterFlowFlg = false;
	float		waterFlowScale = 1.0f;

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
	float				menuButtonScale = 1.0f;
	const int			rightButtonPosX = 950;
	const int			leftButtonPosX = 850;
	const int			leftAndRightButtonPosY = 800;


public:
	CSceneStressCollection();
	~CSceneStressCollection();
	void PlayBGM() override;
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

