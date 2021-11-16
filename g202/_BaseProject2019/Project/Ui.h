#pragma once
#include "Mof.h"
#include "timer.h"
#include "Blinking.h"

class CUi
{
private:
	int bodyTemp = 10;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	int hungerRegion = 40;

	CTexture stressMeter;

	CTexture tempNormal;
	CTexture tempHot;
	CTexture tempCold;

	CTexture tempMeter;
	CTexture tempMeterFrame;

	CTexture hungerGauge;
	CTexture hungerGaugeFrame;

	CTexture parasite1;
	CTexture parasite2;
	CTexture parasite3;
	CTexture parasite4;
	CTexture parasite5;

	CTexture jumpPoss;
	CTexture eatPoss;

	CTexture cautionUi;

	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;

	CBlinking cautionB;

	CFont font;
public:
	bool Load();
	void Initialize();
	void Update();
	void Render(int parasiteNum,int hungry,float tempRegionNum, int distanceNum,bool jumpFlg,bool eatFlg);
	void Release();
};

