#pragma once
#include "SceneBase.h"

class CSceneGameMenu : public CSceneBase
{
private:
	bool flgTutorial = false;
	CTexture textTexture;
	CTexture gamePlayButtonTexture;
	CTexture configButtonTexture;
	CTexture torophyButtonTexture;
	CTexture stressButtonTexture;
	CTexture tutorialButtonTexture;
	CTexture titleButtonTexture;

	const int buttonPosX = 125;
	const int gamePlayButtonPosY = 250;
	const int configButtonPosY= 400;
	const int torophyButtonPosY= 550;
	const int stressButtonPosY= 700;
	const int tutorialButtonPosY= 850;
	const int titleButtonPosX=1200;
	const int titleButtonPosY=800;
	const int textPosX = 100;
	const int textPosY = 40;

public:
	CSceneGameMenu();
	~CSceneGameMenu();
	void PlayBGM() override;
	void Initialize() override;
	void Update() override;
	void SoundUpdate() override;
	void Render() override;
	void Release() override;

	//ÉQÉbÉ^Å[
	bool GetTutorialFlg(){ return flgTutorial; }

	CRectangle GetRect(int i);
};

