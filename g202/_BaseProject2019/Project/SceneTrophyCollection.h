#pragma once
#include "SceneBase.h"

class CSceneTrophyCollection : public CSceneBase
{
private:
	CTexture	buttonTexture;
	int			buttonPosX = 800;
	int			buttonPosY = 800;
public:
	CSceneTrophyCollection();
	~CSceneTrophyCollection();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonPosX, buttonPosY, buttonPosX + buttonTexture.GetWidth(), buttonPosY + buttonTexture.GetHeight());
	};
	};

