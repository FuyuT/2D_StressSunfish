#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase
{
private:
	CTexture	buttonTexture;
	int			buttonPosX = 800;
	int			buttonPosY = 800;
public:
	CSceneTitle();
	~CSceneTitle();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;

	CRectangle GetRect() {
		return CRectangle(buttonPosX, buttonPosY, buttonPosX + buttonTexture.GetWidth(), buttonPosY + buttonTexture.GetHeight());
	};
};

