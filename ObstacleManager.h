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
};

////データポインタ
//char* gFileBuffer = NULL;
//
////コマンドの定義
//enum tag_SCRIPTCOMMAND {
//	CMD_SETEASY,
//	CMD_SETNORMAL,
//	CMD_SETHARD,
//
//	CMD_COUNT,
//};
//
//const char* gScriptCommand[] = {
//	"seteasy",
//	"setnormal",
//	"sethard",
//
//	"",
//};
//
////コマンドを格納する構造体の基礎
////タイプのみを持ち、継承先の各構造体でコマンドごとのパラメーターを追加する
//typedef struct tag_COMMAND {
//	int					Type;
//}COMMAND;
//
////easyコマンドのための構造体
//typedef struct tag_SETEASYCOMMAND : public COMMAND {
//	int obstacleInterval;
//	int turtleRate;
//	int garbageRate;
//	int waterFlowRate;
//	int bubbleRate;
//	int shoalSardineRate;
//	int swordFishRate;
//	int schoolTunaRate;
//	int foodInterval;
//	int rottenInterval;
//	char name[256];
//
//	// コンストラクタ
//	tag_SETEASYCOMMAND() {
//		Type = CMD_SETEASY;
//		obstacleInterval = 0;
//		turtleRate = 0;
//		garbageRate = 0;
//		waterFlowRate = 0;
//		bubbleRate = 0;
//		shoalSardineRate = 0;
//		swordFishRate = 0;
//		schoolTunaRate = 0;
//		foodInterval = 0;
//		rottenInterval = 0;
//		memset(name, 0, 256);
//	}
//}SETEASYCOMMAND;
//
////normalコマンドのための構造体
//typedef struct tag_SETNORMALCOMMAND : public COMMAND {
//	int obstacleInterval;
//	int turtleRate;
//	int garbageRate;
//	int waterFlowRate;
//	int bubbleRate;
//	int shoalSardineRate;
//	int swordFishRate;
//	int schoolTunaRate;
//	int foodInterval;
//	int rottenInterval;
//	char name[256];
//
//	// コンストラクタ
//	tag_SETNORMALCOMMAND() {
//		Type = CMD_SETNORMAL;
//		obstacleInterval = 0;
//		turtleRate = 0;
//		garbageRate = 0;
//		waterFlowRate = 0;
//		bubbleRate = 0;
//		shoalSardineRate = 0;
//		swordFishRate = 0;
//		schoolTunaRate = 0;
//		foodInterval = 0;
//		rottenInterval = 0;
//		memset(name, 0, 256);
//	}
//}SETNORMALCOMMAND;
//
////hardコマンドのための構造体
//typedef struct tag_SETHARDCOMMAND : public COMMAND {
//	int obstacleInterval;
//	int turtleRate;
//	int garbageRate;
//	int waterFlowRate;
//	int bubbleRate;
//	int shoalSardineRate;
//	int swordFishRate;
//	int schoolTunaRate;
//	int foodInterval;
//	int rottenInterval;
//	char name[256];
//
//	// コンストラクタ
//	tag_SETHARDCOMMAND() {
//		Type = CMD_SETHARD;
//		obstacleInterval = 0;
//		turtleRate = 0;
//		garbageRate = 0;
//		waterFlowRate = 0;
//		bubbleRate = 0;
//		shoalSardineRate = 0;
//		swordFishRate = 0;
//		schoolTunaRate = 0;
//		foodInterval = 0;
//		rottenInterval = 0;
//		memset(name, 0, 256);
//	}
//}SETHARDCOMMAND;

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

	//int obstacleInterval = 0;
	//int turtleRate = 0;
	//int garbageRate = 0;
	//int waterFlowRate = 0;
	//int bubbleRate = 0;
	//int shoalSardineRate = 0;
	//int swordFishRate = 0;
	//int schoolTunaRate = 0;
	//int foodInterval = 0;
	//int rottenInterval = 0;

	////コマンドリスト
	//CDynamicArray< COMMAND* >		gCommandList;

	//// スプライトリスト
	//CDynamicArray< CSprite2D* >		gSpriteList;

	////現在実行しているコマンド番号
	//int								gCommandNo = 0;


public:
	CObstacleManager();
	~CObstacleManager();
	bool Load();
	void Initialize();
	void Update(int distance, int posx, float wx, float wy, int tutorialStep, int eventNum);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void PosYRandom(int obstacleType,int eventNum);
	void Overlap(int obstacle,int arrayNum);
	char* Trim(char* s);
	//bool LoadTextFile(char* pName);
	//void TextFileUpdate();

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

