#pragma once
#include "SceneBase.h"
#include "BackObjectKelp.h"
#include "BackObjectRedKelp.h"
#include "BackObjectGreenKelp.h"

class CSceneTitle : public CSceneBase
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
	//背景のオブジェクト
	struct BackObject
	{
		CTexture tex;
		int objectTotalNo;
		Vector2* pos;
	};
	BackObject kelp;
	CBackObjectKelp*	objectKelp;
	BackObject redKelp;
	CBackObjectRedKelp*	objectRedKelp;
	BackObject greenKelp;
	CBackObjectGreenKelp* objectGreenKelp;

	//アニメーション
	CSpriteMotionController motion;


	CTexture			titleLogoTex;
	CTexture			gamePrayButtonTexture;
	CTexture			gameFinishButtonTexture;
	const int			gamePrayButtonPosX = 950;
	const int			gamePlayButtonPosY = 600;
	float				gamePlayButtonScale = 1.0f;
	bool				gamePlayButtonFlg;
	const int			gameFinishButtonPosX = 950;
	const int			gameFinishButtonPosY = 800;
	float				gameFinishButtonScale = 1.0f;
	bool				gameFinishButtonFlg;


public:
	CSceneTitle();
	~CSceneTitle();

	void PlayBGM() override;
	bool Load() override;
	void Initialize() override;
	void Update() override;
	void SoundUpdate() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect(int i);
};

