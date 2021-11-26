#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:
	CTexture	titleLogoTex;
	CTexture	gamePrayButtonTexture;
	CTexture	gameFinishButtonTexture;
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
	CRectangle GetRect(int i);
};

