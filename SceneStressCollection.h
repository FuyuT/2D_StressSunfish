#pragma once
#include "SceneBase.h"
#include "player.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//死因用アイコンテクスチャと表示フラグ宣言
	CTexture	increasedBodyTemperatureIconTexture;	//体温上昇
	bool		increasedBodyTemperatureFlg = false;
	CTexture	lowerBodyTemperatureIconTexture;		//体温低下
	bool		lowerBodyTemperatureFlg = false;
	CTexture	starvationIconTexture;					//餓死
	bool		starvationFlg = false;
	CTexture	cloggedThroatIconTexture;				//餌が喉に刺さる
	bool		cloggedThroatFlg = false;
	CTexture	obesityIconTexture;						//肥満
	bool		obesityFlg = false;
	CTexture	impactIconTexture;						//障害物と衝突
	bool		impactFlg = false;
	CTexture	parasiteIconTexture;					//寄生虫
	bool		parasiteFlg = false;
	CTexture	jumpIconTexture;						//ジャンプ
	bool		jumpFlg = false;
	CTexture	bubbleIconTexture;						//泡
	bool		bubbleFlg = false;
	CTexture	turtleIconTexture;						//ウミガメ
	bool		turtleFlg = false;
	CTexture	waterFlowIconTexture;					//水流
	bool		waterFlowFlg = false;

	//1ページ目、2ページ目上段のX座標
	const int			iconFirstRowPosX = 350;
	const  int			iconSecondRowPosX = 850;
	const int			iconThirdRowPosX = 1350;
	//2ページ目下段のX座標
	const int			icon2PageFirstRowPosX = 600;
	const int			icon2pageSecondRowPosX = 1100;
		//一行目のY座標
	const int			iconOneLinePosY = 200;
	//二行目のY座標
	const int			iconTwoLinePosY = 500;

	//ページ数
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	const int			menuButtonPosX = 1150;
	const int			menuButtonPosY = 775;
	const int			rightButtonPosX = 950;
	const int			leftButtonPosX = 850;
	const int			leftAndRightButtonPosY = 800;


public:
	CSceneStressCollection();
	~CSceneStressCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle ButtonGetRect(int i);
	CRectangle GetRect( int i);

	//ゲームシーンでフラグを変えるための関数
	bool GetStress(int i);

	//表示フラグの保存、読み込み関数
	void SaveStressFlg();
	void LoadStressFlg();



};

