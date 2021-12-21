#pragma once
#include "SceneBase.h"
#include "player.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//死因用アイコンテクスチャと表示フラグ宣言
	CTexture	hyperthermiaTexture;				//体温上昇
	bool		hyperthermiaFlg = false;
	float		hyperthermiaScale = 1.0f;
	CTexture	lowerBodyTemperatureTexture;		//体温低下
	bool		lowerBodyTemperatureFlg = false;
	float		lowerBodyTemperatureScale = 1.0f;
	CTexture	starvationTexture;					//餓死
	bool		starvationFlg = false;
	float		starvationScale = 1.0f;
	CTexture	cloggedThroatexture;				//餌が喉に刺さる
	bool		cloggedThroatFlg = false;
	float		cloggedThroatScale = 1.0f;

	CTexture	obesityTexture;						//肥満
	bool		obesityFlg = false;
	float		obesityScale = 1.0f;
	CTexture	impactTexture;						//障害物と衝突
	bool		impactFlg = false;
	float		impactScale = 1.0f;
	CTexture	parasiteIconTexture;					//寄生虫
	bool		parasiteFlg = false;
	float		parasiteScale = 1.0f;
	CTexture	jumpTexture;						//ジャンプ
	bool		jumpFlg = false;
	float		jumpScale = 1.0f;

	CTexture	bubbleTexture;						//泡
	bool		bubbleFlg = false;
	float		bubbleScale = 1.0f;
	CTexture	turtleTexture;						//ウミガメ
	bool		turtleFlg = false;
	float		turtleScalse = 1.0;
	CTexture	waterFlowTexture;					//水流
	bool		waterFlowFlg = false;
	float		waterFlowScale = 1.0f;
	CTexture	shoalFishTexture;					//魚群
	bool		shoalFishFlg = true;
	float		shoalFishScale = 1.0f;

	//X座標
	const int			iconFirstRowPosX = 120;
	const int			iconSecondRowPosX = 1050;

	//Y座標
	const int			iconOneLinePosY = 130;
	const int			iconTwoLinePosY = 635;

	//ページ数
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

	//ゲームシーンでフラグを変えるための関数
	bool GetStress(int i);

	//表示フラグの保存、読み込み関数
	void SaveStressFlg();
	void LoadStressFlg();



};

