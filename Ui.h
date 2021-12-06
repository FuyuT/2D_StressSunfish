#pragma once
#include "Mof.h"
#include "timer.h"
#include "Blinking.h"
#include "ObstacleManager.h"
#include "Turtle.h"

//トロフィーの距離
#define RIVER 1000
#define WATERFALL 2500
#define LAKE 5000
#define DAM 10000
#define SEWER 25000
#define INDIANOCEAN 50000
#define AMAZONRIVER 100000
#define OCEAN 200000
#define SEAOFJAPAN 300000

//アルファ値
#define MAX_ALPHA 255
#define TIN_ALPHA 70

enum EventMotion
{
	EVENTMOTION_SUMMER,
	EVENTMOTION_WINTER,
	EVENTMOTION_TURTLE,
	EVENTMOTION_SHOALSARDINE,
	EVENTMOTION_GARBAGE,

	EVENTMOTION_COUNT,
};

class CUi
{
private:
	int bodyTemp = 10;

	int parasiteCnt = 0;
	int parasiteFlg = 0;

	int hungerRegion = 40;

	double distance = 0;

	int jumpAlpha = 0;
	int eatAlpha = 0;

	float radyAlpha = 255;

	float radyScale = 1.5f;
	float radyPosx = 550;
	float radyPosy = 350;

	float goScale = 1.0f;
	float goPosx = 700;
	float goPosy = 370;

	int eventPosX = 1920;

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
	CTexture	riverIconTexture;		//川級
	CTexture	waterFallIconTexture;	//滝級
	CTexture	lakeIconTexture;		//湖級
	CTexture	damIconTexture;			//ダム級
	CTexture	sewerIconTexture;		//下水道級
	CTexture	indianOceanIconTexture;	//インド洋級
	CTexture	amazonRiverIconTexture;	//アマゾン川級
	CTexture	oceanIconTexture;		//海級
	CTexture	seaOf​​JapanIconTexture;	//日本海級
	CTexture	aroundTheGlobeIconTexture;	//地球一周級

	//スタート開始合図
	CTexture rady;
	CTexture go;

	//イベントアニメーション
	CTexture eventSummer;
	CTexture eventWinter;
	CTexture eventTurtle;
	CTexture eventShoalSardine;
	CTexture eventGarbage;

	//点滅
	CBlinking cautionB;
	CBlinking cautionHotB;
	CBlinking cautionColdB;

	CBlinking radyGoB;

	//フォント
	CFont font;
	CFont trophyFont;

	//アニメーション
	CSpriteMotionController motion;

	//タイマー
	CTimer eventTimer;

	CObstacleManager obs;
	CTurtle turtle;
public:
	bool Load();
	void Initialize();
	void Update(int eventNum);
	void Render(int parasiteNum,int hungry,float tempRegionNum,
	double distanceNum,bool jumpFlg,bool eatFlg, bool tutorialFlg,int eventNum);
	void Release();

	bool StartSign(bool pose);
};