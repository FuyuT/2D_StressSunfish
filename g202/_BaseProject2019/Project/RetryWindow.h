#pragma once
#include "PopUpWindowBase.h"
class CRetryWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonYesTexture;
	CTexture	buttonNoTexture;

	int			buttonYesPosX = 500;
	int			buttonYesPosY = 600;
	int			buttonNoPosX = 1000;
	int			buttonNoPosY = 600;
public:
	CRetryWindow();
	~CRetryWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
	bool ChangeEndFlg() { !endFlg; return endFlg; }
};

