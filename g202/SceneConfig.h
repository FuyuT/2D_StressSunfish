#pragma once
#include "SceneBase.h"

class CSceneConfig :public CSceneBase
{
private:
	CTexture	buttonTexture;
	const int			buttonPosX = 800;
	const int			buttonPosY = 800;
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
	//セッター
	void SetGamePlayFlg() { gamePlayFlg = true; }
	//ゲッター
	bool GetGamePlayFlg() { return gamePlayFlg; }
};

