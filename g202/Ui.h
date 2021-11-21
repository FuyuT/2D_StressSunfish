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

	//マンボウの顔の枠
	CTexture stressMeter;

	//マンボウの顔
	CTexture tempNormal;
	CTexture tempHot;
	CTexture tempCold;

	//温度計
	CTexture tempMeter;
	CTexture tempMeterFrame;

	//空腹ゲージ
	CTexture hungerGauge;
	CTexture hungerGaugeFrame;

	//寄生虫
	CTexture parasite1;
	CTexture parasite2;
	CTexture parasite3;
	CTexture parasite4;
	CTexture parasite5;

	//行動可能UI
	CTexture jumpPoss;
	CTexture eatPoss;

	//注意UI
	CTexture cautionUi;
	CTexture cautionHot;
	CTexture cautionCold;

	//点滅
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

