#pragma once
#include "SceneBase.h"

enum tag_BUTTON_NO
{
	BUTTON_RETURN,
	BUTTON_MUTE_BGM,
	BUTTON_MUTE_SE,
};

class CSceneConfig :public CSceneBase
{
private:
	CTexture	buttonTexture;
	const int	buttonPosX = 800;
	const int	buttonPosY = 800;
	bool		gamePlayFlg = false;

	CTexture	muteTexBGM;
	Vector2     muteTexPosBGM;
	CTexture	muteTexSE;
	Vector2     muteTexPosSE;

public:
	CSceneConfig();
	~CSceneConfig();

	bool Load() override;
	void Initialize() override;

	void Update() override;

	void Render() override;

	void Release() override;

	//セッター
	void SetGamePlayFlg() { gamePlayFlg = true; }
	//ゲッター
	bool GetGamePlayFlg() { return gamePlayFlg; }
	CRectangle GetRect(int buttonNo) {
		switch (buttonNo)
		{
		case BUTTON_RETURN:
			return CRectangle(buttonPosX, buttonPosY,
				buttonPosX + buttonTexture.GetWidth(), buttonPosY + buttonTexture.GetHeight());
		case BUTTON_MUTE_BGM:
			return CRectangle(muteTexPosBGM.x, muteTexPosBGM.y,
				muteTexPosBGM.x + muteTexBGM.GetWidth(), muteTexPosBGM.y + muteTexBGM.GetHeight());
		case BUTTON_MUTE_SE:
			return CRectangle(muteTexPosSE.x, muteTexPosSE.y,
				muteTexPosSE.x + muteTexSE.GetWidth(), muteTexPosSE.y + muteTexSE.GetHeight());
		default:

			break;
		}
	};
};

