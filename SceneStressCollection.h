#pragma once
#include "SceneBase.h"
#include "player.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//�����p�A�C�R���e�N�X�`���ƕ\���t���O�錾
	CTexture	hyperthermiaTexture;				//�̉��㏸
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
	CTexture	shoalFishTexture;					//���Q
	bool		shoalFishFlg = true;
	float		shoalFishScale = 1.0f;

	//X���W
	const int			iconFirstRowPosX = 120;
	const int			iconSecondRowPosX = 1050;

	//Y���W
	const int			iconOneLinePosY = 130;
	const int			iconTwoLinePosY = 635;

	//�y�[�W��
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	const int			textPosX = 80;
	const int			textPosY = 10;
	const int			menuButtonPosX = 1250;
	const int			menuButtonPosY = 920;
	float				menuButtonScale = 0.9f;
	float				menuButtonScaleMax = 0.95f;
	float				menuButtonScaleMini = 0.9f;
	const int			rightButtonPosX = 1025;
	const int			leftButtonPosX = 850;
	const int			leftAndRightButtonPosY = 970;


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
	void MouseCollision(int posX, int posY) override;

	//�Q�[���V�[���Ńt���O��ς��邽�߂̊֐�
	bool GetStress(int i);

	//�\���t���O�̕ۑ��A�ǂݍ��݊֐�
	void SaveStressFlg();
	void LoadStressFlg();



};

