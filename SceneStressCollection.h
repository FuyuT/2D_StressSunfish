#pragma once
#include "SceneBase.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//�����p�A�C�R���e�N�X�`���ƕ\���t���O�錾
	CTexture	increasedBodyTemperatureIconTexture;	//�̉��㏸
	bool		increasedBodyTemperatureFlg = false;
	CTexture	lowerBodyTemperatureIconTexture;		//�̉��ቺ
	bool		lowerBodyTemperatureFlg = false;
	CTexture	starvationIconTexture;					//�쎀
	bool		starvationIconFlg = false;
	CTexture	cloggedThroatIconTexture;				//�a���A�Ɏh����
	bool		cloggedThroatIconFlg = false;
	CTexture	obesityIconTexture;						//�얞
	bool		obesityIconFlg = false;
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

	//��s�ڂ�Y���W
	int			iconOneLinePosY;
	//��s�ڂ�Y���W
	int			iconTwoLinePosY;

	CTexture	menuButtonTexture;
	int			menuButtonPosX = 800;
	int			menuButtonPosY = 800;
public:
	CSceneStressCollection();
	~CSceneStressCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	};
};

