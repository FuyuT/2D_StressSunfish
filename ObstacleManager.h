#pragma once
#include "FoodFish.h"
#include "FoodShrimp.h"
#include "FoodCrab.h"
#include "Garbage.h"
#include "Bubble.h"
#include "Turtle.h"
#include "WaterFlow.h"
#include "RottenFish.h"
#include "RottenCrab.h"
#include "RottenShrimp.h"
#include "ShoalSardine.h"
#include "SwordFish.h"
#include "SchoolTuna.h"
#include "HeaderDefine.h"

#define		SHOW_LIMIT	13


//当たり判定の判別のため追加
enum obstacle {
	Turtle,
	Garbage,
	WaterFlow,
	Bubble,
	FoodFish,
	FoodShrimp,
	FoodCrab,
	RottenFish,
	RottenCrab,
	RottenShrimp,
	ShoalSardine,
	SwordFish,
	SchoolTuna,
};

enum obstacleType {
	Obstacle,
	Food,
	Rotten,
	SummerFood,
	WinterFood,
};

class CObstacleManager
{
private:
	CFoodFish   cFish[3];
	CFoodShrimp cShrimp[3];
	CFoodCrab   cCrab[3];
	CGarbage	cGarbage[3];
	CBubble		cBubble[3];
	CRottenFish  cRottenFish[3];
	CRottenCrab cRottenCrab[3];
	CRottenShrimp cRottenShrimp[3];
	CTurtle     cTurtle[5];
	CWaterFlow  cWaterFlow;
	CShoalSardine cShoalSardine[2];
	CSwordFish cSwordFish[2];
	CSchoolTuna cSchoolTuna[2];

	CRandom obstacleRandom;
	CRandom createRandom;
	CRandom posYRandom;
	CRandom garbageNoRandom;
	int random;
	int obstacleNum;
	int foodRandom;
	int rottenRandom;
	int posY;
	int posYNum;
	int lastTimePosY;

	bool createFlg;
	bool eventFoodCreateFlg;

	bool obstacleFlg;
	bool foodFlg;
	bool rottenFlg;

	char* gFileBuffer = NULL;

	int gBufferOffset = 0;

	char gLineBuffer[256];

public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(int distance, int posx, float wx, float wy, int tutorialStep, int eventNum);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void PosYRandom(int obstacleType);
	void Overlap(int obstacle,int arrayNum);
    bool TextLoad();


		bool ObstaclePercentage(int percent)
	{
		//確率によってtrueを返す
		if (createRandom.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}

	//当たり判定の判別のため追加
	CRectangle GetRect(int type, int num)
	{
		switch (type)
		{
		case Turtle:
			return cTurtle[num].GetRect();
			break;
		case ShoalSardine:
			return cShoalSardine[num].GetRect();
			break;
		case Garbage:
			return cGarbage[num].GetRect();
			break;
		case WaterFlow:
			return cWaterFlow.GetRect();
			break;
		case Bubble:
			return cBubble[num].GetRect();
			break;
		case FoodFish:
			return cFish[num].GetRect();
			break;
		case FoodShrimp:
			return cShrimp[num].GetRect();
			break;
		case FoodCrab:
			return cCrab[num].GetRect();
			break;
		case RottenFish:
			return cRottenFish[num].GetRect();
			break;
		case RottenCrab:
			return cRottenCrab[num].GetRect();
			break;
		case RottenShrimp:
			return cRottenShrimp[num].GetRect();
			break;
		case SwordFish:
			return cSwordFish[num].GetRect();
			break;
		case SchoolTuna:
			return cSchoolTuna[num].GetRect();
			break;
		}
	}

	//player側から非表示にするため追加
	void SetShow(bool flg, int type, int num)
	{
		switch (type)
		{
		case FoodFish:
			cFish[num].SetShow(flg);
			break;
		case FoodShrimp:
			cShrimp[num].SetShow(flg);
			break;
		case FoodCrab:
			cCrab[num].SetShow(flg);
			break;
		case RottenFish:
			cRottenFish[num].SetShow(flg);
			break;
		case RottenCrab:
			cRottenCrab[num].SetShow(flg);
			break;
		case RottenShrimp:
			cRottenShrimp[num].SetShow(flg);
			break;
		}
	}

	//player側から「画面内に存在するか」を確認するため追加
	bool GetShow(int type, int num)
	{
		switch (type)
		{
		case Turtle:
			return cTurtle[num].GetShow();
			break;
		case ShoalSardine:
			return cShoalSardine[num].GetShow();
			break;
		case Garbage:
			return cGarbage[num].GetShow();
			break;
		case WaterFlow:
			return cWaterFlow.GetShow();
			break;
		case Bubble:
			return cBubble[num].GetShow();
			break;
		case FoodFish:
			return cFish[num].GetShow();
			break;
		case FoodShrimp:
			return cShrimp[num].GetShow();
			break;
		case FoodCrab:
			return cCrab[num].GetShow();
			break;
		case RottenFish:
			return cRottenFish[num].GetShow();
			break;
		case RottenCrab:
			return cRottenCrab[num].GetShow();
			break;
		case RottenShrimp:
			return cRottenShrimp[num].GetShow();
			break;
		case SwordFish:
			return cSwordFish[num].GetShow();
			break;
		case SchoolTuna:
			return cSchoolTuna[num].GetShow();
			break;
		}
	}
};

