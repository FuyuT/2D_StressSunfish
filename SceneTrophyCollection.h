#pragma once
#include "SceneBase.h"

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
	bool		damFlg = false;
	CTexture	sewerIconTexture;		//下水道級
	bool		sewerFlg = false;
	CTexture	indianOceanIconTexture;	//インド洋級
	bool		indianOceanFlg = false;
	CTexture	amazonRiverIconTexture;	//アマゾン川級
	bool		amazonRiverFlg = false;
	CTexture	oceanIconTexture;		//海級
	bool		oceanFlg = false;
	CTexture	seaOf​​JapanIconTexture;	//日本海級
	bool		seaOf​​JapanFlg = false;
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
	CRectangle GetRect() {
		return CRectangle(menuButtonPosX, menuButtonPosY, menuButtonPosX + menuButtonTexture.GetWidth(), menuButtonPosY + menuButtonTexture.GetHeight());
	};
	};

