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
	bool		popUpFlg = false;
public:
	//�f�X�g���N�^��virtual�ɂ��Ȃ��ƃ|�����[�t�B�Y�����g�p���Ă���ꍇ�A�q�N���X�̃f�X�g���N�^���������Ȃ��̂�virtual��t���Ă���
	CSceneBase() {}
	virtual ~CSceneBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//�Q�b�^�[
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
};

