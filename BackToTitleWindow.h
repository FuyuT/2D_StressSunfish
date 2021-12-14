#pragma once
#include "PopUpWindowBase.h"
class CBackToTitleWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	textTexture;
	CTexture	buttonYesTexture;
	CTexture	buttonNoTexture;

	const int			textPosX = 510;
	const int			textPosY = 325;
	const int			buttonYesPosX = 500;
	float				buttonYesScale = 1.0;
	const int			buttonNoPosX = 1025;
	float				buttonNoScale = 1.0f;
	const int			buttonPosY = 600;
public:
	CBackToTitleWindow();
	~CBackToTitleWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

