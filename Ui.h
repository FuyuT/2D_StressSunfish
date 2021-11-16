#pragma once
#include "Mof.h"
#include "timer.h"
#include "Blinking.h"
#include "Turtle.h"

class CUi
{
private:
	int bodyTemp = 10;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	int hungerRegion = 40;

	float distance = 0;

	//�}���{�E�̊�̘g
	CTexture stressMeter;

	//�}���{�E�̊�
	CTexture tempNormal;
	CTexture tempHot;
	CTexture tempCold;

	//���x�v
	CTexture tempMeter;
	CTexture tempMeterFrame;

	//�󕠃Q�[�W
	CTexture hungerGauge;
	CTexture hungerGaugeFrame;

	//�񐶒�
	CTexture parasite1;
	CTexture parasite2;
	CTexture parasite3;
	CTexture parasite4;
	CTexture parasite5;

	//�s���\UI
	CTexture jumpPoss;
	CTexture eatPoss;

	//����UI
	CTexture cautionUi;
	CTexture cautionHot;
	CTexture cautionCold;

	//�_��
	CBlinking cautionB;
	CBlinking cautionHotB;
	CBlinking cautionColdB;

	CFont font;

	CTurtle turtle;
public:
	bool Load();
	void Initialize();
	void Update();
	void Render(int parasiteNum,int hungry,float tempRegionNum,
		int distanceNum,bool jumpFlg,bool eatFlg);
	void Release();
};

