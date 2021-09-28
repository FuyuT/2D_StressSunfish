#pragma once
#include	"Mof.h"

//�V�[���̗�
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
	
public:
	
	virtual void Initialize() {};
	virtual void Update(){};
	virtual void Render() {};
	virtual void Release() {};
	//�Q�b�^�[
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
};

