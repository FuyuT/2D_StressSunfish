#pragma once
#include "SceneBase.h"

class CSceneGameMenu : public CSceneBase
{
private:
	bool tutorialFlg = false;
	CTexture textTexture;
	CTexture gamePlayButtonTexture;
	CTexture configButtonTexture;
	CTexture trophyButtonTexture;
	CTexture stressButtonTexture;
	CTexture tutorialButtonTexture;
	CTexture titleButtonTexture;

	const int buttonPosX = 125;
	const int gamePlayButtonPosY = 250;
	float	gamePlayButtonScale = 1.0f;
	const int configButtonPosY= 400;
	float	configButtonScale = 1.0f;
	const int trophyButtonPosY= 550;
	float	trophyButtonScale = 1.0f;
	const int stressButtonPosY= 700;
	float	stressButtonScale = 1.0f;
	const int tutorialButtonPosY= 850;
	float	tutorialButtonScale = 1.0f;
	const int titleButtonPosX=1200;
	const int titleButtonPosY=850;
	float	titleButtonScale = 1.0f;
	const int textPosX = 100;
	const int textPosY = 40;

	//�O�I���{�^���ۑ��p
	int	beforButtonSelect;

public:
	CSceneGameMenu();
	~CSceneGameMenu();
	void PlayBGM() override;
	void Initialize() override;
	void Update() override;
	void SoundUpdate() override;
	void Render() override;
	void Release() override;


	CRectangle GetRect(int i);
	
};

