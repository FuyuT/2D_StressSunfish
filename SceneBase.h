#pragma once
#include	"Mof.h"
#include	"SoundManager.h"
#include	"ScaleController.h"
#include "ResourceFont.h"

//�V�[���̗�
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
	//�t�H���g
	CResourceFont font;
	LPMofChar fontAdd = "Text\\PopRumCute.otf";
	LPMofChar fontName = "�|�v��ށ��L���[�g";

	ScaleController scaleController;
	bool		endFlg = false;
	short		nextScene;
	bool		popUpFlg = false;
	CTexture    backGroundTex;
	CSoundManager* cSound;
	//�X�P�[���p�萔
	const float		scaleSpeed = 0.002f;
	const float		scaleMax = 1.05f;
	const float		scaleMini = 1.0f;
	//�{�^���I��p�ϐ�
	int				buttonSelect;
	
public:
	//�f�X�g���N�^��virtual�ɂ��Ȃ��ƃ|�����[�t�B�Y�����g�p���Ă���ꍇ�A�q�N���X�̃f�X�g���N�^���������Ȃ��̂�virtual��t���Ă���
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
	//�Q�b�^�[�A�Z�b�^�[
	short GetNextScene() { return nextScene; }
	bool IsEnd() { return endFlg; }
	void SetSoundManager(CSoundManager& p) {cSound = &p; }
};

