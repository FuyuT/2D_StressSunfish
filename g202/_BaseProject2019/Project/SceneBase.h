#pragma once
#include	"Mof.h"

//シーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAMEMENU,
	SCENENO_GAME,
	SCENENO_CONFIG,
	SCENENO_STRESSCOLLECTION,
	SCENENO_TROPHY,
};

class CSceneBase
{
protected:
	bool		endFlg = false;
	short		nextScene;
	bool		popUpFlg = false;
public:
	//デストラクタをvirtualにしないとポリモーフィズムを使用している場合、子クラスのデストラクタが見つけられないのでvirtualを付けている
	CSceneBase() {}
	virtual ~CSceneBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//ゲッター
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
};

