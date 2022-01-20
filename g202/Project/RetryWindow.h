#pragma once
#include "PopUpWindowBase.h"
class CRetryWindow : public CPopUpWindowBase
{
private:
	CTexture	textTexture;
	CTexture	popUpTexture;
	CTexture	buttonYesTexture;
	CTexture	buttonNoTexture;

	const int			textPosX = 590;
	const int			textPosY = 325;
	const int			buttonYesPosX = 500;
	const int			buttonPosY = 600;
	float				buttonYesScale = 1.0f;
	const int			buttonNoPosX = 1025;
	float				buttonNoScale = 1.0f;
public:
	CRetryWindow();
	~CRetryWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	void MouseCollision(int posX, int posY) override;
	CRectangle GetRect(int i);
	bool ChangeEndFlg() { !endFlg; return endFlg; }
};

