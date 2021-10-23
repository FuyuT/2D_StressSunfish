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
};


class CSceneTrophyCollection : public CSceneBase
{
private:
	//トロフィーテクスチャと表示フラグ宣言
	CTexture	riverIconTexture;		//川級
	bool		riverFlg = true;
	CTexture	waterFallIconTexture;	//滝級
	bool		waterFallFlg = true;
	CTexture	lakeIconTexture;		//湖級
	bool		lakeFlg = true;
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
	bool		aroundTheGlobeFlg = false;
	CTexture	zeroMotivationIconTexture;	//やる気ゼロ級
	bool		zeroMotivationFlg = false;
	CTexture	mountFujiIconTexture;	//富士山級
	bool		mountFujiFlg = false;
	CTexture	osakaMarathonIconTexture;	//大阪マラソン級
	bool		osakaMarathonFlg = false;
	CTexture	biwaLakeIconTexture;	//琵琶湖級
	bool		biwaLakeFlg = false;
	CTexture	jackPodIconTexture;		//ジャックポット級
	bool		jackPodFlg = false;
	CTexture	talentedDemonIconTexture;	//才能魔級
	bool		talentedDemonFlg = false;

	//上段のX座標
	int			iconFirstRowPosX = 350;
	int			iconSecondRowPosX = 850;
	int			iconThirdRowPosX = 1350;
	//2ページ目以降の下段のX座標
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
	CSceneTrophyCollection();
	~CSceneTrophyCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle ButtonGetRect() {
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());};
	CRectangle GetRect(int i);

	};
