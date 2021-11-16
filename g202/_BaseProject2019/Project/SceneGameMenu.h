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

	const int buttonPosX = 400;
	const int gamePlayButtonPosY = 400;
	const int configButtonPosY=500;
	const int torophyButtonPosY=600;
	const int stressButtonPosY=700;
	const int tutorialButtonPosY=800;
	const int titleButtonPosX=1200;
	const int titleButtonPosY=800;

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

