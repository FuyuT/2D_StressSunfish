#pragma once
#include "Mof.h"
//�T�E���h��
typedef enum tag_SOUNDTYPE{
	SOUND_COUNT,
}SOUNDTYPE;

class CSoundManager
{
private:
	//���C��BGM
	CSoundBuffer mainBGM;

	//���ʉ�
	CSoundBuffer jumpSE;			//�W�����v
	CSoundBuffer eatSE;				//�H��
	CSoundBuffer parasiteStickSE;	//�񐶒��Ђ���
	CSoundBuffer waterLandingSE;    //����
	CSoundBuffer waterFlowSE;		//����
	CSoundBuffer bubbleSE;			//�A
	CSoundBuffer warningSE;			//�x��

	CSoundBuffer buttonSE;			//�{�^��

public:
	void Load();
	void Play(SOUNDTYPE sound);
	void SetPitch(SOUNDTYPE sound, float pit);
	void Release();

	void Stop() { mainBGM.Stop(); }
	
	void SetMainBGM(CSoundBuffer& main, bool loop) { mainBGM = main; mainBGM.SetLoop(loop); }
};

