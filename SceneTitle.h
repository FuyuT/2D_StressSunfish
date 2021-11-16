#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:
	CTexture	titleLogoTex;
	CTexture	gamePrayButtonTexture;
	CTexture	gameFinishButtonTexture;
	const int			gamePrayButtonPosX = 950;
	const int			gamePrayButtonPosY = 600;
	const int			gameFinishButtonPosX = 950;
	const int			gameFinishButtonPosY = 800;
public:
	CSceneTitle();
	~CSceneTitle();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

