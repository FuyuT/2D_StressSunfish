#pragma once
#include "SceneBase.h"
#include "BackObjectKelp.h"
#include "BackObjectRedKelp.h"
#include "BackObjectGreenKelp.h"
class CSceneGameMenu : public CSceneBase
{
private:
	//背景
	CTexture			backGround_0;
	CTexture			backGround_1;
	CTexture			backGround_2;
	CTexture			backGround_3;
	CTexture			backGround_4;
	CTexture			backGround_5;
	CTexture			backGround_6;
	CTexture			backGround_7;



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

	//前選択ボタン保存用
	int	beforButtonSelect;

	//背景のオブジェクト
	struct BackObject
	{
		CTexture tex;
		int objectTotalNo;
		Vector2* pos;
	};
	BackObject kelp;
	CBackObjectKelp* objectKelp;
	BackObject redKelp;
	CBackObjectRedKelp* objectRedKelp;
	BackObject greenKelp;
	CBackObjectGreenKelp* objectGreenKelp;


public:
	CSceneGameMenu();
	~CSceneGameMenu();
	void PlayBGM() override;
	void Initialize() override;
	void Update() override;
	void SoundUpdate() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;


	CRectangle GetRect(int i);
	
};

