#pragma once
#include "SceneBase.h"

class CSceneConfig :public CSceneBase
{
private:
	CTexture	buttonTexture;
	const int			buttonPosX = 800;
	const int			buttonPosY = 800;
	float				buttonScale = 1.0;
	bool        gamePlayFlg = false;
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
	//�Z�b�^�[
	void SetGamePlayFlg() { gamePlayFlg = true; }
	//�Q�b�^�[
	bool GetGamePlayFlg() { return gamePlayFlg; }
};

