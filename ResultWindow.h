#pragma once
#include "PopUpWindowBase.h"
class CResultWindow : public CPopUpWindowBase
{
private:
	CFont		font;
	CTexture	popUpTexture;
	CTexture	buttonNextTexture;

	int			buttonNextPosX = 1500;
	int			buttonNextPosY = 850;
public:
	CResultWindow();
	~CResultWindow();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Release() override;
	CRectangle GetRect() {
		return CRectangle(buttonNextPosX, buttonNextPosY, buttonNextPosX + buttonNextTexture.GetWidth(), buttonNextPosY + buttonNextTexture.GetHeight());
	};
};

