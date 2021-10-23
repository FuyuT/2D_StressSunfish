#pragma once
#include "SceneBase.h"

//死因の列挙
enum tag_CASE {
	CASE_INCREASEDBODYTEMPERATURE,	//体温上昇
	CASE_LOWERBODYTEMPERATURE,		//体温低下
	CASE_STARVATION,				//餓死
	CASE_CLOGGEDTHROAT,				//餌が喉に刺さる
	CASE_OBESITY,					//肥満
	CASE_IMPACT,					//障害物と衝突
	CASE_PARASITE,					//寄生虫
	CASE_JUMP,						//ジャンプ
	CASE_BUBBLE,					//泡
	CASE_TURTLE,					//ウミガメ
	CASE_WATERFLOW,					//水流
};

class CSceneStressCollection : public CSceneBase
{
private:
	//死因用アイコンテクスチャと表示フラグ宣言
	CTexture	increasedBodyTemperatureIconTexture;	//体温上昇
	bool		increasedBodyTemperatureFlg = true;
	CTexture	lowerBodyTemperatureIconTexture;		//体温低下
	bool		lowerBodyTemperatureFlg = true;
	CTexture	starvationIconTexture;					//餓死
	bool		starvationFlg = true;
	CTexture	cloggedThroatIconTexture;				//餌が喉に刺さる
	bool		cloggedThroatFlg = true;
	CTexture	obesityIconTexture;						//肥満
	bool		obesityFlg = true;
	CTexture	impactIconTexture;						//障害物と衝突
	bool		impactFlg = true;
	CTexture	parasiteIconTexture;					//寄生虫
	bool		parasiteFlg = true;
	CTexture	jumpIconTexture;						//ジャンプ
	bool		jumpFlg = true;
	CTexture	bubbleIconTexture;						//泡
	bool		bubbleFlg = true;
	CTexture	turtleIconTexture;						//ウミガメ
	bool		turtleFlg = true;
	CTexture	waterFlowIconTexture;					//水流
	bool		waterFlowFlg = true;

	//1ページ目、2ページ目上段のX座標
	int			iconFirstRowPosX = 350;
	int			iconSecondRowPosX = 850;
	int			iconThirdRowPosX = 1350;
	//2ページ目下段のX座標
	int			icon2PageFirstRowPosX = 600;
	int			icon2pageSecondRowPosX = 1100;
		//一行目のY座標
	int			iconOneLinePosY = 200;
	//二行目のY座標
	int			iconTwoLinePosY = 500;

	//ページ数
	int			page;

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
	CRectangle ButtonGetRect() { return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight()); };
	CRectangle GetRect( int i);

	//ゲームシーンでフラグを変えるための関数
};

