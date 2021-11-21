#pragma once
#include "PopUpWindowBase.h"
class CGameQuitWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonYesTexture;
	CTexture	buttonNoTexture;

	const int			buttonYesPosX = 500;
	const int			buttonYesPosY = 700;
	const int			buttonNoPosX = 1025;
	const int			buttonNoPosY = 700;
public:
	CGameQuitWindow();
	~CGameQuitWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
	bool ChangeEndFlg() { !endFlg; return endFlg; }
};

