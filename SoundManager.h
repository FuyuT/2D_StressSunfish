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

	SOUND_EVENT_SUMMER,
	SOUND_EVENT_WINTER,
	SOUND_EVENT_OTHERS,
	SOUND_BUTTON_SELECT,
	SOUND_BUTTON_OK,
	SOUND_BUTTON_CANCEL,
	SOUND_BUTTON_PUSH,
	SOUND_RESULT,

	SOUND_COUNT,
}SOUNDTYPE;

enum tag_Sound_NO
{
	SOUND_BGM,
	SOUND_SE,
};

class CSoundManager
{
private:
	//���C��BGM
	float		 volumeBGM;
	CSoundBuffer titleBGM;
	CSoundBuffer menuBGM;
	CSoundBuffer collectionBGM;
	CSoundBuffer gameBGM;

	//���ʉ�
	float		 volumeSE;
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
	CSoundBuffer eventWinterSE;		//�~�C�x���g
	CSoundBuffer eventSummerSE;		//�ăC�x���g
	CSoundBuffer eventOtherSE;		//���̑��C�x���g
	CSoundBuffer buttonSelectSE;	//�{�^���I����
	CSoundBuffer buttonCancelSE;	//�������{�^������������
	CSoundBuffer buttonOKSE;		//�͂��{�^������������
	CSoundBuffer buttonPushSE;		//��L�ȊO�̃{�^������������
	CSoundBuffer resultSE;			//���U���g�|�b�v�A�b�v�\�����鎞��SE	


	bool muteBGM;
	bool muteSE;

	//���ݗ����Ă��鉹�y�̎擾�p�ϐ�
	int nowSound;
public:
	CSoundManager(bool muteBGM,bool muteSE);
	~CSoundManager();
	bool Load();
	void SetLoop();	//BGM�̂�Loop�ɐݒ��
	void Play(SOUNDTYPE sound);
	void Stop(SOUNDTYPE sound); //todo:���̒�~
	void AllStop();
	void Release();

	//����
	//0.0�`1.0�ŕύX
	void  SetVolumeBGM(float volume) { volumeBGM = volume; }
	void  SetVolumeSE(float volume)  { volumeSE = volume; }
	float GetVolumeBGM()			 { return volumeBGM; }
	float GetVolumeSE()				 { return volumeSE; }
	void  ChangeVolume(int soundNo);

	//�~���[�g
	void SetMute(int soundNo);
	void CancelMute(int soundNo) {
		switch (soundNo)
		{
		case SOUND_BGM:
			muteBGM = false;
		break;
		case SOUND_SE:
			muteSE = false;
			break;
		default:
			break;
		}
	}
	bool GetMuteBGM() { return muteBGM; }
	bool GetMuteSE() { return muteSE; }
	int	GetNowSound() { return nowSound; }

	//�f�[�^�֘A
	void LoadSoundData();
	void SaveSoundData();

};