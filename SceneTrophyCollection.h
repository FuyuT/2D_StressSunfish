#pragma once
#include "SceneBase.h"

//トロフィー列挙
enum tag_TROPHY {
	TROPHY_RIVER,				//川級
	TROPHY_WATERFALL,			//滝級
	TROPHY_LAKE,				//湖級
	TROPHY_DAM,				//ダム級
	TROPHY_SEWER,				//下水道級
	TROPHY_INDIANOCEAN,		//インド洋級

	TROPHY_AMAZONROVER,		//アマゾン川級
	TROPHY_OCEAN,				//海級
	TROPHY_SEAOFJAPAN,		//日本海級
	TROPHY_AROUNDTHEGLOBE,	//地球一周級
	TROPHY_ZEROMOTIVATION,	//やる気ゼロ級

	TROPHY_MOUNTFJI,			//富士山級
	TROPHY_OSAKAMARATHON,		//大阪マラソン級
	TROPHY_BIWALAKE,			//琵琶湖級
	TROPHY_JACKPOD,			//ジャックポット級
	TROPHY_TALENTEDDEMON,		//才能魔級
	TROPHY_NULL,
};

class CSceneTrophyCollection : public CSceneBase
{
private:

	//トロフィーテクスチャと表示フラグ宣言
	CTexture	riverIconTexture;		//川級
	bool		riverFlg = false;
	float		riverScale = 1.0f;
	CTexture	waterFallIconTexture;	//滝級
	bool		waterFallFlg = false;
	float		waterFallScale = 1.0f;
	CTexture	lakeIconTexture;		//湖級
	bool		lakeFlg = true;
	float		lakeScale = 1.0f;
	CTexture	damIconTexture;			//ダム級
	bool		damFlg = false;
	float		damScale = 1.0f;
	CTexture	sewerIconTexture;		//下水道級
	bool		sewerFlg = false;
	float		sewerScale = 1.0f;
	CTexture	indianOceanIconTexture;	//インド洋級
	bool		indianOceanFlg = false;
	float		indianOceanScale = 1.0f;
	CTexture	amazonRiverIconTexture;	//アマゾン川級
	bool		amazonRiverFlg = false;
	float		amazonRiverScale = 1.0f;
	CTexture	oceanIconTexture;		//海級
	bool		oceanFlg = false;
	float		oceanScale = 1.0f;
	CTexture	seaOf​​JapanIconTexture;	//日本海級
	bool		seaOf​​JapanFlg = false;
	float		seaOf​​JapanScale = 1.0f;
	CTexture	aroundTheGlobeIconTexture;	//地球一周級
	bool		aroundTheGlobeFlg = false;
	float		aroundTheGlobeScale = 1.0f;
	CTexture	zeroMotivationIconTexture;	//やる気ゼロ級
	bool		zeroMotivationFlg = false;
	float		zeroMotivationScale = 1.0f;
	CTexture	mountFujiIconTexture;	//富士山級
	bool		mountFujiFlg = false;
	float		mountFujiScale = 1.0f;
	CTexture	osakaMarathonIconTexture;	//大阪マラソン級
	bool		osakaMarathonFlg = false;
	float		osakaMarathonScale = 1.0f;
	CTexture	biwaLakeIconTexture;	//琵琶湖級
	bool		biwaLakeFlg = false;
	float		biwaLakeScale = 1.0f;
	CTexture	jackPodIconTexture;		//ジャックポット級
	bool		jackPodFlg = false;
	float		jackPodScale = 1.0f;
	CTexture	talentedDemonIconTexture;	//才能魔級
	bool		talentedDemonFlg = false;
	float		talentedDemonScale = 1.0f;

	//上段のX座標
	const int			iconFirstRowPosX = 350;
	const int			iconSecondRowPosX = 850;
	const int			iconThirdRowPosX = 1350;
	//2ページ目以降の下段のX座標
	const int			icon2PageFirstRowPosX = 570;
	const int			icon2pageSecondRowPosX = 1075;
	//一行目のY座標
	const int			iconOneLinePosY = 100;
	//二行目のY座標
	const int			iconTwoLinePosY = 500;

	//ページ数
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	CTexture	backGroundTexture1;
	CTexture	backGroundTexture2;
	//文字座標
	const int			textPosX = 20;
	const int			textPosY = 30;
	//ボタン座標
	const int			menuButtonPosX = 1150;
	const int			menuButtonPosY = 875;
	float				menuButtonScale = 1.0f;

	const int			rightButtonPosX = 990;
	const int			leftButtonPosX = 900;
	const int			leftAndRightButtonPosY = 900;

	//取得したトロフィーを三つ保存するための配列ポインタ
	int*			numberOfTrophy[3];

public:
	CSceneTrophyCollection();
	~CSceneTrophyCollection();

	void PlayBGM() override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle ButtonGetRect(int i);
	CRectangle GetRect(int i);
	

	//ゲームシーンでフラグを変えるための関数
	//未入手トロフィーならtrueを、取得済みトロフィーならfalseを返す。
	bool GetTrophy(int i);
	int* GetNumberOfTrophy() { return *numberOfTrophy; };

	//表示フラグの保存、読み込み関数
	void SaveTrophyFlg();
	void LoadTrophyFlg();
	
	};
