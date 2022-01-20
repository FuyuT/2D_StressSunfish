#pragma once

#include "Mof.h"
#include "ObstacleManager.h"
#include "timer.h"
#include "time.h"
#include "HeaderDefine.h"
#include "SoundManager.h"

//初期位置 X
#define		STARTPOS_X				200
#define		STARTPOS_Y				900

//座標を進んだ距離に変換する割合
#define		TRANSLATE_DISTANCE		10

//移動速度	
#define		PLAYER_SPEED			0.6f
//重力
#define		GRAVITY					1.0f

//当たり判定の幅調整
#define		COLLISION_ADJUSTMENT_TOP	100.0f
#define		COLLISION_ADJUSTMENT_LEFT	110.0f
#define		COLLISION_ADJUSTMENT_RIGHT	150.0f
#define		COLLISION_ADJUSTMENT_BOTTOM	160.0f

//エサ探知範囲
#define		FEED_SEARCHRANGE		60.0f
//テクスチャの幅(仮)
#define		TEXTURE_SIZE			384

//ジャンプ力
#define		JUMP_POWER_X			9.0f
#define		JUMP_POWER_Y			30.0f
//ジャンプ後に潜る量
#define		WATER_LANDING_DEEP		50.0f
//海面からどこまでがジャンプ可能か
#define		JUMP_ZONE				40.0f

//海面
#define		SEA_LEVEL				780
//海底
#define		UNDER_SEA				2160

//お腹が空く度合い
#define		HUNGRYLEVEL				0.05f
//エサを食べたときに得られる満腹度
#define		FEED_SATIETYLEVEL		36.0f
//空腹地
#define		INIT_STOMACH			40;
//満腹
#define		FULL_STOMACH			0
//餓死
#define		STARVATION				100
//同じエサが一度に画面に出てくる最大数
#define FEED_MAXCOUNT 3

//寄生虫許容限界数
#define		PARASITE_LIMIT			5

//体温が変動する度合い(速さ)
#define		TEMPERATURE_LEVEL		0.07f
//標準体温
#define		STANDARD_TEMPERATURE	10
//体温限界値(熱中症)
#define		HYPERTHERMIA_LIMIT		0
//体温限界値(凍死)
#define		FROZEN_LIMIT			100
//体温変動区域
#define		TEMPERATURE_CHANGEZONE	500

//水流による最大加速度
#define		WATERFLOW_MAXSPEED		1.5f
//水流による加速度
#define		WATERFLOW_SPEED			0.02f

//水しぶき
#define		WAVE_POSY				530

//死因一覧
enum CAUSE_OF_DEATH
{
	CAUSE_None,				//死んでいない
	CAUSE_Hyperthermia,     //熱中症(温度)			
	CAUSE_Frozen,			//凍死(温度)			
	CAUSE_Starvation,		//餓死(空腹度・エサ)	
	CAUSE_ChokeOnShell,		//喉つまり(エサ)		
	CAUSE_Obesity,			//肥満(エサ)			
	CAUSE_Obstacle,			//衝突(障害物)		
	CAUSE_Parasite,			//寄生虫	
	CAUSE_Jump,				//ジャンプ								
	CAUSE_Bubble,			//泡					
	CAUSE_SeaTurtle,		//ショック死(ウミガメ)
	CAUSE_WaterFlow,		//急な加速(水流)
	CAUSE_ShoalFish,		//魚群衝突
};

//アニメーション種類
enum MOTION
{
	MOTION_STAND,
	MOTION_EAT,
	MOTION_JUMP,
	MOTION_DEATH,

	MOTION_COUNT,
};

enum Temperature
{
	Temp_Normal,
	Temp_Hot,
	Temp_Cold,
};

class CPlayer
{
private:
	//最大速度
	float		playerMaxSpeedX = 10.0f;
	float		playerMaxSpeedY = 10.0f;

	//テクスチャ
	CTexture	standTexture;
	CTexture	eatTexture;
	CTexture	jumpTexture;
	CTexture	deathTexture;

	CTexture	hotStandTexture;
	CTexture	hotEatTexture;
	CTexture	hotJumpTexture;
	CTexture	hotDeathTexture;

	CTexture	coldStandTexture;
	CTexture	coldEatTexture;
	CTexture	coldJumpTexture;
	CTexture	coldDeathTexture;

	CTexture	waveTexture;

	//確率
	CRandom		random;
	//座標
	float		posX;
	float		posY;
	//速度
	float		moveX;
	float		moveY;
	//速度の倍数
	float		moveSpeed;
	//ジャンプ
	bool		jumpFlg;
	bool		jumpDangerFlg;
	CTimer		jumpDangerTimer;
	//生きているかを表すフラグ
	bool		deadFlg;
	//アクション可能であるか表すフラグ
	bool		possibleToJumpFlg;
	bool		possibleToEatFlg[FEED_MAXCOUNT];
	//死因
	int			causeOfDeath;
	//無敵(連続で同じ障害物にぶつかり続けてしまうため、衝突後は解除されるまで無敵にする)
	bool		hitFlg;
	CTimer		hitTimer;

	//ステータス( 状態 に関する変数)
	//体温
	int         bodyTemp;
	float       tempRegion;
	Temperature	temperature;
	//空腹
	float       hungerRegion;
	//寄生虫
	int			parasite;
	//水流
	CTimer		waterFlowTimer;
	bool		waterFlowFlg;
	//アニメーション
	CSpriteMotionController	motion;

	CSpriteMotionController	outWaveMotion;
	CSpriteMotionController	inWaveMotion;

	//水しぶき
	int			jumpStartPosX;
	int			jumpEndPosX;

	//ブレーキ(テスト)
	CTimer		brakeTimer;

	//UI
	CTimer tempTimer;
	CTimer hungerTimer;
	CTimer parasiteTimer;

	//チュートリアル用
	bool	jumpTaskFlg;
	bool	eatTaskFlg;
	int		taskCompleteStep;
	CTimer	moveUpTaskTimer;
	CTimer	moveDownTaskTimer;

	//サウンド用
	CSoundManager* cSound;
public:
	CPlayer();
	~CPlayer();
	bool Load();
	void Initialize();
	void UpdateMove(int tutorialStep);
	//確率で死ぬ 100を割り切れる数のみ対応(1,2,4,5,10,20,25,50,100)
	bool DieInPercentage(int percent)
	{
		//確率によってtrueを返す
		if (random.Random(1, 100 / percent + 1) == 1)
		{
			return true;
		}
		return false;
	}
	//食べる
	//腐っていればtrueを、そうでなければfalseを入れる 喉つまりを起こすかどうかの判断に使う
	bool Eat(bool rottenFlg, bool unDeadFlg, int tutorialStep);
	//ジャンプ
	void Jump(bool unDeadFlg, int tutorialStep);
	void UpdateStatus(bool unDeadFlg,int tutorialStep, int eventNum);

	//Updateの引数について
	// 
	//unDeadFlg
	//true : 死ななくなる(チュートリアル用)
	//false: 死ぬようになる(通常プレイ用)
	// 
	//tutorialStep
	//0     : 上下移動のみ可能
	//1     : 上下移動に加え、「ジャンプ」、「食べる」が可能
	//3以上 : チュートリアルの終了、制限なくプレイ可能
	void Update(bool unDeadFlg,int tutorialStep,int eventNum);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release();

	//プレイヤーの座標を返す
	int GetPosX()
	{
		return (int)posX;
	};
	int GetPosY()
	{
		return (int)posY;
	};

	//プレイヤー自身の当たり判定を返す
	CRectangle GetRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT_LEFT,
			posY + COLLISION_ADJUSTMENT_TOP,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT,
			posY + TEXTURE_SIZE - COLLISION_ADJUSTMENT_BOTTOM
		);
	}

	//エサが食べられる範囲にあるかを判断するための当たり判定
	CRectangle GetSearchRect()
	{
		return CRectangle(
			posX + COLLISION_ADJUSTMENT_LEFT - FEED_SEARCHRANGE,
			posY + COLLISION_ADJUSTMENT_TOP - FEED_SEARCHRANGE,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT + FEED_SEARCHRANGE,
			posY + TEXTURE_SIZE - COLLISION_ADJUSTMENT_BOTTOM + FEED_SEARCHRANGE
		);
	}
	CRectangle GetEyeRect()
	{
		return CRectangle(
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_LEFT - 70,
			posY + COLLISION_ADJUSTMENT_TOP + 30,
			posX + TEXTURE_SIZE - COLLISION_ADJUSTMENT_RIGHT,
			posY + COLLISION_ADJUSTMENT_BOTTOM
		);
	}

	void Collision(CObstacleManager& cObstacle,int num,bool unDeadFlg, int tutorialStep);

	//死んでいればtrueを返す
	bool GetDead()
	{
		return deadFlg;
	}
	//体温を返す 100 ～ 0
	float	GetTemperature()
	{
		return tempRegion;
	}
	int     GetBodyTemp()
	{
		return bodyTemp;
	}
	//寄生虫の付着数を返す 0 ～ 6
	int GetParasite()
	{
		return parasite;
	}
	//空腹度を返す 100～0
	float GetHungry()
	{
		return hungerRegion;
	}
	//死因を返す
	int GetCauseOfDeath()
	{
		return causeOfDeath;
	}
	//進んだ距離(m数)を返す
	int GetDistance()
	{
		//X座標の20分の1(適当)を進んだ距離とする
		return ((posX - STARTPOS_X) / TRANSLATE_DISTANCE);
	}
	//「ジャンプ」が可能かを返す
	bool GetJump()
	{
		return possibleToJumpFlg;
	}
	//「食べる」が可能かを返す
	bool GetEat()
	{
		for (int i = 0; i < FEED_MAXCOUNT; i++)
		{
			//どれか一つでもtrueであれば
			if (possibleToEatFlg[i])
			{
				return true;
			}
		}
		return false;
	}

	//チュートリアル用関数
	bool GetMoveUpTask()
	{
		if(moveUpTaskTimer.GetNowtime() < 0)
			return true;
		return false;
	}
	bool GetMoveDownTask()
	{
		if(moveDownTaskTimer.GetNowtime() < 0)
			return true;
		return false;
	}
	bool GetJumpTask()
	{
		return jumpTaskFlg;
	}
	bool GetEatTask()
	{
		return eatTaskFlg;
	}
	int GetTaskCompleteStep()
	{
		return taskCompleteStep;
	}

	//サウンド用
	void SetSoundManager(CSoundManager& p) { cSound = &p; }
};

