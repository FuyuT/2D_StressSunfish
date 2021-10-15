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

	int			buttonContinuePosX = 850;
	int			buttonContinuePosY = 500;
	int			buttonMenuPosX = 850;
	int			buttonMenuPosY = 600;
	int			buttonTitlePosX = 850;
	int			buttonTitlePosY = 700;

public:
	CContinueWindow();
	~CContinueWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect(int i);
};

