#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:
	CTexture	gamePrayButtonTexture;
	CTexture	gameFinishButtonTexture;
	int			gamePrayButtonPosX;
	int			gamePrayButtonPosY;
	int			gameFinishButtonPosX;
	int			gameFinishButtonPosY;
public:
	CSceneTitle();
	~CSceneTitle();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

