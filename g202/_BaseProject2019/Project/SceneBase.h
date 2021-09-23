#pragma once
#include	"Mof.h"

//シーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAME,
};

class CSceneBase
{
protected:
	bool		endFlg = false;
	short		nextScene;
	
public:
	
	virtual void Initialize() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Release() {};
	//ゲッター
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
};

