#pragma once
#include "Mof.h"
//�T�E���h��
typedef enum tag_SOUNDTYPE {
	SOUND_TITLE_BGM,
	SOUND_MENU_BGM,
	SOUND_COLLECTION_BGM,
	SOUND_GAME_BGM,
	SOUND_SCENE_CHANGE,
	SOUND_BUTTON,
	SOUND_ALERT,
	SOUND_JUMP_START,
	SOUND_JUMPING,
	SOUND_WATER_LANDING,
	SOUND_EAT,
	SOUND_WATERFLOW,
	SOUND_PARASITE_STICK,
	SOUND_COLLISION,
	SOUND_BUBBLE,
	SOUND_BUBBLE_COLLISION,

	SOUND_COUNT,
}SOUNDTYPE;

class CSoundManager
{
private:
	//���C��BGM
	CSoundBuffer titleBGM;
	CSoundBuffer menuBGM;
	CSoundBuffer collectionBGM;
	CSoundBuffer gameBGM;

	//���ʉ�
	CSoundBuffer sceneChangeSE;
	CSoundBuffer buttonSE;			//�{�^��
	CSoundBuffer alertSE;			//�x��
	CSoundBuffer jumpStartSE;		//�W�����v�������̐�
	CSoundBuffer jumpingSE;			//�W�����v
	CSoundBuffer waterLandingSE;	//������
	CSoundBuffer eatSE;				//�H��
	CSoundBuffer waterFlowSE;		//����
	CSoundBuffer parasiteStickSE;	//�񐶒��Ђ���
	CSoundBuffer collisionSE;		//�Փ�
	CSoundBuffer bubbleCollisionSE;	//�A�p�Փˉ�

public:
	bool Load();

	void SetLoop();	//BGM�̂�Loop�ɐݒ��
	void Play(SOUNDTYPE sound);
	void Stop(SOUNDTYPE sound); //todo:���̒�~
	void AllStop();

	//���ʂ�0.0�`1.0�ŕύX
	void SetVolumeBGM(float volume);
	void SetVolumeSE(float volume);

	void Release();
};