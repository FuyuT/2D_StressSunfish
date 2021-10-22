#pragma once
#include "SceneBase.h"

class CSceneStressCollection : public CSceneBase
{
private:
	//死因用アイコンテクスチャと表示フラグ宣言
	CTexture	increasedBodyTemperatureIconTexture;	//体温上昇
	bool		increasedBodyTemperatureFlg = false;
	CTexture	lowerBodyTemperatureIconTexture;		//体温低下
	bool		lowerBodyTemperatureFlg = false;
	CTexture	starvationIconTexture;					//餓死
	bool		starvationIconFlg = false;
	CTexture	cloggedThroatIconTexture;				//餌が喉に刺さる
	bool		cloggedThroatIconFlg = false;
	CTexture	obesityIconTexture;						//肥満
	bool		obesityIconFlg = false;
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

	//一行目のY座標
	int			iconOneLinePosY;
	//二行目のY座標
	int			iconTwoLinePosY;

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
	CRectangle GetRect() {
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	};
};

