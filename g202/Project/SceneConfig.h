#pragma once
#include "SceneBase.h"
#include "ResourceFont.h"

//現在のシーンの案内テクスチャ
constexpr int SCENE_TEXT_IMAGE_X = 100;
constexpr int SCENE_TEXT_IMAGE_Y = 40;


//サウンド
constexpr int	VOLUME_BAR_POS_X			  = 600;
constexpr int	BGM_BAR_POS_Y				  = 420;
constexpr int	SE_BAR_POS_Y				  = 670;

constexpr float VOLUME_CONTROL_BUTTON_MIN	  = 600;
constexpr float VOLUME_CONTROL_BUTTON_MAX     = 1575;
constexpr int	BGM_CONTROL_BUTTON_POS_Y	  = 400;
constexpr int	SE_CONTROL_BUTTON_POS_Y		  = 650;

//ミュート
constexpr int	MUTE_TEX_POS_X			      = 240;
constexpr int	BGM_MUTE_TEX_POS_Y			  = 300;
constexpr int	SE_MUTE_TEX_POS_Y			  = 550;

//貝のUI
constexpr int	CLOSE_OYSTER_POS_X			  = 500;
constexpr int	BGM_CLOSE_OYSTER_TOP_POS_Y	  = 270;
constexpr int	BGM_CLOSE_OYSTER_BOTTOM_POS_Y = 280;
constexpr int	SE_CLOSE_OYSTER_TOP_POS_Y	  = 520;
constexpr int	SE_CLOSE_OYSTER_BOTTOM_POS_Y  = 530;

constexpr int	OPEN_OYSTER_POS_X			  = 1500;
constexpr int	BGM_OPEN_OYSTER_POS_Y		  = 300;
constexpr int	SE_OPEN_OYSTER_POS_Y		  = 550;

constexpr float VOLUME_CONTROL_SPEED		  = 5.0f;

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
	CTexture	buttonReturnTexture;
	const int	buttonReturnPosX = 800;
	const int	buttonReturnPosY = 800;
	float		buttonReturnScale = 1.0f;
	const float	volumeButtonScaleMax = 1.2f;
	const float	volumeButtonScaleSpeed = 0.007f;
	bool		gamePlayFlg = false;
	//現在のシーンの案内テクスチャ
	CTexture	scaneTextImage;

	//サウンド関係
	//ボリュームバー
	CTexture	volumeBarTex;
	int			scrollBarLength;

	CTexture	volumeControlButton;
	Vector2		BGMControlButtonPos;
	Vector2		SEControlButtonPos;
	float		buttonBGMControlScale = 1.0f;
	float		buttonSEControlScale = 1.0f;
	bool		BGMControlFlg;
	bool		SEControlFlg;

	//ミュート
	CTexture	soundMuteTex;
	CTexture	soundNoMuteTex;
	float		buttonMuteBGMScale = 1.0f;
	float		buttonMuteSEScale = 1.0f;

	//UI
	CTexture	oysterCloseBottomTex;
	CTexture	oysterCloseTopTex;
	CTexture	oysterOpenTex;
	CTexture	SETextTex;
	CTexture	BGMTextTex;
	CTexture	muteTextTex;
	CTexture	spaceSelectTex;

public:
	CSceneConfig();
	~CSceneConfig();

	bool Load() override;
	void Initialize() override;

	void SelectButton();
	void ButtonUpdate();
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
			return CRectangle(buttonReturnPosX, buttonReturnPosY,
				buttonReturnPosX + buttonReturnTexture.GetWidth(), buttonReturnPosY + buttonReturnTexture.GetHeight());
		case BUTTON_MUTE_BGM:
			return CRectangle(MUTE_TEX_POS_X, BGM_MUTE_TEX_POS_Y,
				MUTE_TEX_POS_X + soundMuteTex.GetWidth(), BGM_MUTE_TEX_POS_Y + soundMuteTex.GetHeight());
		case BUTTON_MUTE_SE:
			return CRectangle(MUTE_TEX_POS_X, SE_MUTE_TEX_POS_Y,
				MUTE_TEX_POS_X + soundNoMuteTex.GetWidth(), SE_MUTE_TEX_POS_Y + soundNoMuteTex.GetHeight());
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

