#pragma once
#include "Mof.h"
//サウンド列挙
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
	//メインBGM
	CSoundBuffer titleBGM;
	CSoundBuffer menuBGM;
	CSoundBuffer collectionBGM;
	CSoundBuffer gameBGM;

	//効果音
	CSoundBuffer sceneChangeSE;
	CSoundBuffer buttonSE;			//ボタン
	CSoundBuffer alertSE;			//警告
	CSoundBuffer jumpStartSE;		//ジャンプした時の水
	CSoundBuffer jumpingSE;			//ジャンプ
	CSoundBuffer waterLandingSE;	//着水音
	CSoundBuffer eatSE;				//食事
	CSoundBuffer waterFlowSE;		//水流
	CSoundBuffer parasiteStickSE;	//寄生虫ひっつき
	CSoundBuffer collisionSE;		//衝突
	CSoundBuffer bubbleCollisionSE;	//泡用衝突音

public:
	bool Load();

	void SetLoop();	//BGMのみLoopに設定可
	void Play(SOUNDTYPE sound);
	void Stop(SOUNDTYPE sound); //todo:音の停止
	void AllStop();

	//音量は0.0～1.0で変更
	void SetVolumeBGM(float volume);
	void SetVolumeSE(float volume);

	void Release();
};