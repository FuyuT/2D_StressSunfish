#pragma once
#include "SceneBase.h"

class CSceneConfig :public CSceneBase
{
private:
	CTexture	buttonTexture;
	int			buttonPosX = 800;
	int			buttonPosY = 800;
public:
	CSceneConfig();
	~CSceneConfig();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonPosX, buttonPosY, buttonPosX + buttonTexture.GetWidth(), buttonPosY + buttonTexture.GetHeight());
	};
};

