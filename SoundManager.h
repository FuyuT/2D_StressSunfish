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
	//メインBGM
	float		 volumeBGM;
	CSoundBuffer titleBGM;
	CSoundBuffer menuBGM;
	CSoundBuffer collectionBGM;
	CSoundBuffer gameBGM;

	//効果音
	float		 volumeSE;
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
	CSoundBuffer eventWinterSE;		//冬イベント
	CSoundBuffer eventSummerSE;		//夏イベント
	CSoundBuffer eventOtherSE;		//その他イベント
	CSoundBuffer buttonSelectSE;	//ボタン選択時
	CSoundBuffer buttonCancelSE;	//いいえボタンを押した時
	CSoundBuffer buttonOKSE;		//はいボタンを押した時
	CSoundBuffer buttonPushSE;		//上記以外のボタンを押した時
	CSoundBuffer resultSE;			//リザルトポップアップ表示する時のSE	


	bool muteBGM;
	bool muteSE;

	//現在流している音楽の取得用変数
	int nowSound;
public:
	CSoundManager(bool muteBGM,bool muteSE);
	~CSoundManager();
	bool Load();
	void SetLoop();	//BGMのみLoopに設定可
	void Play(SOUNDTYPE sound);
	void Stop(SOUNDTYPE sound); //todo:音の停止
	void AllStop();
	void Release();

	//音量
	//0.0～1.0で変更
	void  SetVolumeBGM(float volume) { volumeBGM = volume; }
	void  SetVolumeSE(float volume)  { volumeSE = volume; }
	float GetVolumeBGM()			 { return volumeBGM; }
	float GetVolumeSE()				 { return volumeSE; }
	void  ChangeVolume(int soundNo);

	//ミュート
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

	//データ関連
	void LoadSoundData();
	void SaveSoundData();

};