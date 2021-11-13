#pragma once
#include "Mof.h"
//サウンド列挙
typedef enum tag_SOUNDTYPE{
	SOUND_COUNT,
}SOUNDTYPE;

class CSoundManager
{
private:
	//メインBGM
	CSoundBuffer mainBGM;

	//効果音
	CSoundBuffer jumpSE;			//ジャンプ
	CSoundBuffer eatSE;				//食事
	CSoundBuffer parasiteStickSE;	//寄生虫ひっつき
	CSoundBuffer waterLandingSE;    //着水
	CSoundBuffer waterFlowSE;		//水流
	CSoundBuffer bubbleSE;			//泡
	CSoundBuffer warningSE;			//警告

	CSoundBuffer buttonSE;			//ボタン

public:
	void Load();
	void Play(SOUNDTYPE sound);
	void SetPitch(SOUNDTYPE sound, float pit);
	void Release();

	void Stop() { mainBGM.Stop(); }
	
	void SetMainBGM(CSoundBuffer& main, bool loop) { mainBGM = main; mainBGM.SetLoop(loop); }
};

