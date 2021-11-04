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
	TROPHY_TOTAL_NO,
};

class CSceneTrophyCollection : public CSceneBase
{
private:

	//トロフィーテクスチャと表示フラグ宣言
	CTexture	riverIconTexture;		//川級
	bool		riverFlg = false;
	CTexture	waterFallIconTexture;	//滝級
	bool		waterFallFlg = false;
	CTexture	lakeIconTexture;		//湖級
	bool		lakeFlg = false;
	CTexture	damIconTexture;			//ダム級
	bool		damFlg = true;
	CTexture	sewerIconTexture;		//下水道級
	bool		sewerFlg = true;
	CTexture	indianOceanIconTexture;	//インド洋級
	bool		indianOceanFlg = true;
	CTexture	amazonRiverIconTexture;	//アマゾン川級
	bool		amazonRiverFlg = true;
	CTexture	oceanIconTexture;		//海級
	bool		oceanFlg = true;
	CTexture	seaOf​​JapanIconTexture;	//日本海級
	bool		seaOf​​JapanFlg = true;
	CTexture	aroundTheGlobeIconTexture;	//地球一周級
	bool		aroundTheGlobeFlg = true;
	CTexture	zeroMotivationIconTexture;	//やる気ゼロ級
	bool		zeroMotivationFlg = true;
	CTexture	mountFujiIconTexture;	//富士山級
	bool		mountFujiFlg = true;
	CTexture	osakaMarathonIconTexture;	//大阪マラソン級
	bool		osakaMarathonFlg = true;
	CTexture	biwaLakeIconTexture;	//琵琶湖級
	bool		biwaLakeFlg = true;
	CTexture	jackPodIconTexture;		//ジャックポット級
	bool		jackPodFlg = true;
	CTexture	talentedDemonIconTexture;	//才能魔級
	bool		talentedDemonFlg = true;

	//上段のX座標
	int			iconFirstRowPosX = 350;
	int			iconSecondRowPosX = 850;
	int			iconThirdRowPosX = 1350;
	//2ページ目以降の下段のX座標
	int			icon2PageFirstRowPosX = 600;
	int			icon2pageSecondRowPosX = 1100;
	//一行目のY座標
	int			iconOneLinePosY = 100;
	//二行目のY座標
	int			iconTwoLinePosY = 500;

	//ページ数
	int			page;

	CTexture	menuButtonTexture;
	CTexture	leftButtonTexture;
	CTexture	rightButtonTexture;
	int			menuButtonPosX = 1500;
	int			menuButtonPosY = 900;
	int			rightButtonPosX = 950;
	int			leftButtonPosX = 850;
	int			leftAndRightButtonPosY = 900;

public:
	CSceneTrophyCollection();
	~CSceneTrophyCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle ButtonGetRect(int i);
	CRectangle GetRect(int i);

	//ゲームシーンでフラグを変えるための関数
	//未入手ならtrueを、取得済みならfalseを返す。
	bool GetTrophy(int i);

	//表示フラグの保存、読み込み関数
	void SaveTrophyFlg();
	void LoadTrophyFlg();
	
	};
