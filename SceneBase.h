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
	CTexture    backGroundTex;
public:
	//デストラクタをvirtualにしないとポリモーフィズムを使用している場合、子クラスのデストラクタが見つけられないのでvirtualを付けている
	CSceneBase() :
	endFlg(false),
	nextScene(0),
	popUpFlg(false),
	backGroundTex()
	{
	}
	virtual ~CSceneBase() {}
	virtual bool Load() { return true; }
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void RenderDebug() {}
	virtual void Release() {}
	//ゲッター
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
};

