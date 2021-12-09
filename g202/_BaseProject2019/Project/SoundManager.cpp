#include "SoundManager.h"

CSoundManager::CSoundManager(bool muteBGM, bool muteSE) :
	muteBGM(muteBGM),
	muteSE(muteSE)
{
}

CSoundManager::~CSoundManager()
{
}

bool CSoundManager::Load()
{
	LoadSoundData();
	
	if (!titleBGM.Load("Sound\\BGM_Title.mp3"))return false;
	if (!menuBGM.Load("Sound\\BGM_Menu.mp3"))return false;
	if (!collectionBGM.Load("Sound\\BGM_Collection.mp3"))return false;
	if (!gameBGM.Load("Sound\\BGM_Game.mp3"))return false;

	if (!sceneChangeSE.Load("Sound\\SE_SceneChange.mp3"))return false;
	if (!buttonSE.Load("Sound\\SE_Button.mp3"))return false;
	if (!alertSE.Load("Sound\\SE_Alert.mp3"))return false;
	if (!jumpStartSE.Load("Sound\\SE_JumpStart.mp3"))return false;
	if (!jumpingSE.Load("Sound\\SE_Jumping.mp3"))return false;
	if (!waterLandingSE.Load("Sound\\SE_WaterLanding.mp3"))return false;
	if (!eatSE.Load("Sound\\SE_Eat.mp3"))return false;
	if (!waterFlowSE.Load("Sound\\SE_WaterFlow.mp3"))return false;
	if (!collisionSE.Load("Sound\\SE_Collision.mp3"))return false;
	if (!bubbleCollisionSE.Load("Sound\\SE_BubbleCollision.mp3"))return false;
	SetLoop();

	return true;
}


void CSoundManager::SetLoop()
{
	titleBGM.SetLoop(true);
	menuBGM.SetLoop(true);
	collectionBGM.SetLoop(true);
	gameBGM.SetLoop(true);
}

void CSoundManager::Play(SOUNDTYPE sound)
{
	switch (sound)
	{
	case SOUND_TITLE_BGM:
		titleBGM.Play();
		break;
	case SOUND_MENU_BGM:
		menuBGM.Play();
		break;
	case SOUND_COLLECTION_BGM:
		collectionBGM.Play();
		break;
	case SOUND_GAME_BGM:
		gameBGM.Play();
		break;
	case SOUND_SCENE_CHANGE:
		sceneChangeSE.Play();
		break;
	case SOUND_BUTTON:
		buttonSE.Play();
		break;
	case SOUND_ALERT:
		alertSE.Play();
		break;
	case SOUND_JUMP_START:
		jumpStartSE.Play();
		break;
	case SOUND_JUMPING:
		jumpingSE.Play();
		break;
	case SOUND_WATER_LANDING:
		waterLandingSE.Play();
		break;
	case SOUND_EAT:
		eatSE.Play();
		break;
	case SOUND_WATERFLOW:
		waterFlowSE.Play();
		break;
	case SOUND_PARASITE_STICK:
		parasiteStickSE.Play();
		break;
	case SOUND_COLLISION:
		collisionSE.Play();
		break;
	case SOUND_BUBBLE_COLLISION:
		bubbleCollisionSE.Play();
		break;
	default:
		break;
	}
}

void CSoundManager::Stop(SOUNDTYPE sound)
{
	switch (sound)
	{
	case SOUND_TITLE_BGM:
		titleBGM.Stop();
		break;
	case SOUND_MENU_BGM:
		menuBGM.Stop();
		break;
	case SOUND_COLLECTION_BGM:
		collectionBGM.Stop();
		break;
	case SOUND_GAME_BGM:
		gameBGM.Stop();
		break;
	case SOUND_SCENE_CHANGE:
		sceneChangeSE.Stop();
		break;
	case SOUND_BUTTON:
		buttonSE.Stop();
		break;
	case SOUND_ALERT:
		alertSE.Stop();
		break;
	case SOUND_JUMP_START:
		jumpStartSE.Stop();
		break;
	case SOUND_JUMPING:
		jumpingSE.Stop();
		break;
	case SOUND_WATER_LANDING:
		waterLandingSE.Stop();
		break;
	case SOUND_EAT:
		eatSE.Stop();
		break;
	case SOUND_WATERFLOW:
		waterFlowSE.Stop();
		break;
	case SOUND_PARASITE_STICK:
		parasiteStickSE.Stop();
		break;
	case SOUND_COLLISION:
		collisionSE.Stop();
		break;
	case SOUND_BUBBLE_COLLISION:
		bubbleCollisionSE.Stop();
		break;
	default:
		break;
	}

}

void CSoundManager::AllStop()
{
	titleBGM.Stop();
	menuBGM.Stop();
	collectionBGM.Stop();
	gameBGM.Stop();
	sceneChangeSE.Stop();
	buttonSE.Stop();
	alertSE.Stop();
	jumpStartSE.Stop();
	jumpingSE.Stop();
	waterLandingSE.Stop();
	eatSE.Stop();
	waterFlowSE.Stop();
	parasiteStickSE.Stop();
	collisionSE.Stop();
	bubbleCollisionSE.Stop();
}


void CSoundManager::ChangeVolume(int soundNo)
{
	switch (soundNo)
	{
	case SOUND_BGM:
		titleBGM.SetVolume(volumeBGM);
		menuBGM.SetVolume(volumeBGM);
		collectionBGM.SetVolume(volumeBGM);
		gameBGM.SetVolume(volumeBGM);
		break;
	case SOUND_SE:
		sceneChangeSE.SetVolume(volumeSE);
		buttonSE.SetVolume(volumeSE);
		alertSE.SetVolume(volumeSE);
		jumpStartSE.SetVolume(volumeSE);
		jumpingSE.SetVolume(volumeSE);
		waterLandingSE.SetVolume(volumeSE);
		eatSE.SetVolume(volumeSE);
		waterFlowSE.SetVolume(volumeSE);
		parasiteStickSE.SetVolume(volumeSE);
		collisionSE.SetVolume(volumeSE);
		bubbleCollisionSE.SetVolume(volumeSE);
		break;
	default:
		break;
	}
	SaveSoundData();
}

void CSoundManager::SetMute(int soundNo)
{
	switch (soundNo)
	{
	case SOUND_BGM:
		muteBGM = true;
		titleBGM.SetVolume(0);
		menuBGM.SetVolume(0);
		collectionBGM.SetVolume(0);
		gameBGM.SetVolume(0);
		break;
	case SOUND_SE:
		muteSE = true;
		sceneChangeSE.SetVolume(0);
		buttonSE.SetVolume(0);
		alertSE.SetVolume(0);
		jumpStartSE.SetVolume(0);
		jumpingSE.SetVolume(0);
		waterLandingSE.SetVolume(0);
		eatSE.SetVolume(0);
		waterFlowSE.SetVolume(0);
		parasiteStickSE.SetVolume(0);
		collisionSE.SetVolume(0);
		bubbleCollisionSE.SetVolume(0);
		break;	
	default:
		break;
	}
}

void CSoundManager::LoadSoundData()
{
	FILE* fp = fopen("Volume.dat", "rb");
	//ファイルが無い時、音量を設定して新しく作る
	if (fp == nullptr)
	{
		muteBGM   = false;
		muteSE    = false;
		volumeBGM = 0.5;
		volumeSE  = 0.5;
		SaveSoundData();
		return;
	}
	//ファイルがある時は、前回のデータを読み込む
	if (fp)
	{
		fread(&muteBGM, sizeof(bool), 1, fp);
		fread(&muteSE, sizeof(bool), 1, fp);
		fread(&volumeBGM, sizeof(float), 1, fp);
		fread(&volumeSE, sizeof(float), 1, fp);
		fclose(fp);
	}
}

void CSoundManager::SaveSoundData()
{
	FILE* fp = fopen("Volume.dat", "wb");
	if (fp)
	{
		fwrite(&muteBGM, sizeof(bool), 1, fp);
		fwrite(&muteSE, sizeof(bool), 1, fp);
		fwrite(&volumeBGM, sizeof(float), 1, fp);
		fwrite(&volumeSE, sizeof(float), 1, fp);
		fclose(fp);
	}
}


void CSoundManager::Release()
{
	titleBGM.Release();
	menuBGM.Release();
	collectionBGM.Release();
	gameBGM.Release();
	sceneChangeSE.Release();
	buttonSE.Release();
	alertSE.Release();
	jumpStartSE.Release();
	jumpingSE.Release();
	waterLandingSE.Release();
	eatSE.Release();
	waterFlowSE.Release();
	parasiteStickSE.Release();
	collisionSE.Release();
	bubbleCollisionSE.Release();
}