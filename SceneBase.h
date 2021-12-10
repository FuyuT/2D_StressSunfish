#pragma once
#include	"Mof.h"
#include	"SoundManager.h"
#include	"ScaleController.h"
#include "ResourceFont.h"

//シーンの列挙
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAMEMENU,
	SCENENO_GAME,
	SCENENO_CONFIG,
	SCENENO_STRESSCOLLECTION,
	SCENENO_TROPHY,
	SCENENO_TUTORIAL,
};


class CSceneBase
{
protected:
	//フォント
	CResourceFont font;
	LPMofChar fontAdd = "Text\\PopRumCute.otf";
	LPMofChar fontName = "ポプらむ☆キュート";

	ScaleController scaleController;
	bool		endFlg = false;
	short		nextScene;
	bool		popUpFlg = false;
	CTexture    backGroundTex;
	CSoundManager* cSound;
	//スケール用定数
	const float		scaleSpeed = 0.002f;
	const float		scaleMax = 1.05f;
	const float		scaleMini = 1.0f;
	//ボタン選択用変数
	int				buttonSelect;
	
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
	virtual void PlayBGM(){}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void SoundUpdate(){}
	virtual void Render() {}
	virtual void RenderDebug() {}
	virtual void Release() {}
	//ゲッター、セッター
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
	void SetSoundManager(CSoundManager& p) {cSound = &p; }
};

