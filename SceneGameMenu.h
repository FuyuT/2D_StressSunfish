#pragma once
#include "SceneBase.h"

class CSceneGameMenu : public CSceneBase
{
private:
	bool flgTutorial = false;
	CTexture gamePlayButtonTexture;
	CTexture configButtonTexture;
	CTexture torophyButtonTexture;
	CTexture stressButtonTexture;
	CTexture tutorialButtonTexture;
	CTexture titleButtonTexture;


	int gamePlayButtonPosX;
	int gamePlayButtonPosY;
	int configButtonPosX;
	int configButtonPosY;
	int torophyButtonPosX;
	int torophyButtonPosY;
	int stressButtonPosX;
	int stressButtonPosY;
	int tutorialButtonPosX;
	int tutorialButtonPosY;
	int titleButtonPosX;
	int titleButtonPosY;

public:
	CSceneGameMenu();
	~CSceneGameMenu();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	//ÉQÉbÉ^Å[
	bool GetTutorialFlg(){ return flgTutorial; }

	CRectangle GetRect(int i);
};

