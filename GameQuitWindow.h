#pragma once
#include "PopUpWindowBase.h"
class CGameQuitWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonYesTexture;
	CTexture	buttonNoTexture;
	CTexture	finishTextTexture;

	const int			buttonYesPosX = 500;
	float				buttonYesScale = 1.0f;
	const int			buttonNoPosX = 1025;
	float				buttonNoScale = 1.0f;
	const int			buttonPosY = 700;
	const int			finishTextPosX = 500;
	const int			finishTextPosY = 350;
public:
	CGameQuitWindow();
	~CGameQuitWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect(int i);
	bool ChangeEndFlg() { !endFlg; return endFlg; }
};

