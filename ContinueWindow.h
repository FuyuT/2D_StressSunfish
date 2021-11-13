#pragma once
#include "PopUpWindowBase.h"
class CContinueWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonContinueTexture;
	CTexture	buttonMenuTexture;
	CTexture	buttonTitleTexture;

	const int			buttonContinuePosX = 850;
	const int			buttonContinuePosY = 500;
	const int			buttonMenuPosX = 850;
	const int			buttonMenuPosY = 600;
	const int			buttonTitlePosX = 850;
	const int			buttonTitlePosY = 700;

public:
	CContinueWindow();
	~CContinueWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

