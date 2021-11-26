#pragma once
#include "Mof.h"
#include "timer.h"
#include "Blinking.h"
#include "ObstacleManager.h"
#include "Turtle.h"

class CUi
{
private:
	int bodyTemp = 10;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	int hungerRegion = 40;

	double distance = 0;

	//マンボウの顔の枠
	CTexture stressMeter;

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

	//トロフィー
	CTexture	waterFallIconTexture;	//滝級
	CTexture	lakeIconTexture;		//湖級
	CTexture	damIconTexture;			//ダム級
	CTexture	sewerIconTexture;		//下水道級
	CTexture	indianOceanIconTexture;	//インド洋級
	CTexture	amazonRiverIconTexture;	//アマゾン川級
	CTexture	oceanIconTexture;		//海級
	CTexture	seaOf​​JapanIconTexture;	//日本海級
	CTexture	aroundTheGlobeIconTexture;	//地球一周級


	//点滅
	CBlinking cautionB;
	CBlinking cautionHotB;
	CBlinking cautionColdB;

	CFont font;
	CFont trophyFont;

	CObstacleManager obs;
	CTurtle turtle;
public:
	bool Load();
	void Initialize();
	void Update();
	void Render(int parasiteNum,int hungry,float tempRegionNum,
	int distanceNum,bool jumpFlg,bool eatFlg, bool tutorialFlg);
	void Release();
};

