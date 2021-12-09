#pragma once
#include "SceneBase.h"

//サウンド
constexpr int	VOLUME_BAR_POS_X			  = 600;
constexpr int	BGM_BAR_POS_Y				  = 420;
constexpr int	SE_BAR_POS_Y				  = 670;

constexpr float VOLUME_CONTROL_BUTTON_MIN	  = 600;
constexpr float VOLUME_CONTROL_BUTTON_MAX     = 1575;
constexpr int	BGM_CONTROL_BUTTON_POS_Y	  = 400;
constexpr int	SE_CONTROL_BUTTON_POS_Y		  = 650;

//ミュート
constexpr int	MUTE_TEX_POS_X			      = 200;
constexpr int	BGM_MUTE_TEX_POS_Y			  = 350;
constexpr int	SE_MUTE_TEX_POS_Y			  = 600;

//貝のUI
constexpr int	CLOSE_OYSTER_POS_X			  = 500;
constexpr int	BGM_CLOSE_OYSTER_TOP_POS_Y	  = 270;
constexpr int	BGM_CLOSE_OYSTER_BOTTOM_POS_Y = 280;
constexpr int	SE_CLOSE_OYSTER_TOP_POS_Y	  = 520;
constexpr int	SE_CLOSE_OYSTER_BOTTOM_POS_Y  = 530;

constexpr int	OPEN_OYSTER_POS_X			  = 1500;
constexpr int	BGM_OPEN_OYSTER_POS_Y		  = 300;
constexpr int	SE_OPEN_OYSTER_POS_Y		  = 550;



enum tag_BUTTON_NO
{
	BUTTON_RETURN,
	BUTTON_MUTE_BGM,
	BUTTON_MUTE_SE,
	BUTTON_BGM_CONTROL,
	BUTTON_SE_CONTROL,
};


class CSceneConfig :public CSceneBase
{
private:
	CTexture	buttonTexture;
	const int	buttonPosX = 800;
	const int	buttonPosY = 800;
	float		buttonScale = 1.0f;
	bool		gamePlayFlg = false;

	//サウンド関係
	CTexture	volumeBarTex;
	int			scrollBarLength;

	CTexture	volumeControlButton;
	Vector2		BGMControlButtonPos;
	Vector2		SEControlButtonPos;
	//ミュート
	CTexture	muteTexBGM;
	CTexture	muteTexSE;
	bool		muteBGM;
	bool		muteSE;
	//UI
	CTexture	oysterCloseBottomTex;
	CTexture	oysterCloseTopTex;
	CTexture	oysterOpenTex;

public:
	CSceneConfig();
	~CSceneConfig();

	bool Load() override;
	void Initialize() override;

	void SoundMute();
	//引数(対象の位置,対象のボタンの番号,選択フラグ,ボタンの半分の長さ)
	void DragButton(Vector2& pos, const int buttonNo, bool& scrollFlg, const int texHalfLength);
	//引数（対象の位置,対象のサウンド番号)
	void VolumeAdjustment(const Vector2 pos, const int soundNo);
	void SoundUpdate() override;
	void Update() override;

	void Render() override;

	void Release() override;

	//セッター
	void SetGamePlayFlg() { gamePlayFlg = true; }
	//ゲッター
	bool GetGamePlayFlg() { return gamePlayFlg; }

	CRectangle GetRect(int no) {
		switch (no)
		{
		case BUTTON_RETURN:
			return CRectangle(buttonPosX, buttonPosY,
				buttonPosX + buttonTexture.GetWidth(), buttonPosY + buttonTexture.GetHeight());
		case BUTTON_MUTE_BGM:
			return CRectangle(MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y,
				MUTE_TEX_POS_X + muteTexBGM.GetWidth(), BGM_MUTE_TEX_POS_Y + muteTexBGM.GetHeight());
		case BUTTON_MUTE_SE:
			return CRectangle(MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y,
				MUTE_TEX_POS_X + muteTexSE.GetWidth(), SE_MUTE_TEX_POS_Y + muteTexSE.GetHeight());
		case BUTTON_BGM_CONTROL:
			return CRectangle(BGMControlButtonPos.x, BGMControlButtonPos.y,
				BGMControlButtonPos.x + volumeControlButton.GetWidth(), BGMControlButtonPos.y + volumeControlButton.GetHeight());
		case BUTTON_SE_CONTROL:
			return CRectangle(SEControlButtonPos.x, SEControlButtonPos.y,
				SEControlButtonPos.x + volumeControlButton.GetWidth(), SEControlButtonPos.y + volumeControlButton.GetHeight());
		default:
			break;
		}
	};
};

