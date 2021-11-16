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
	const int			buttonYesPosY = 600;
	const int			buttonNoPosX = 1025;
	const int			buttonNoPosY = 600;
public:
	CBackToTitleWindow();
	~CBackToTitleWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
	bool ChangeEndFlg() { !endFlg; return endFlg; }
};

