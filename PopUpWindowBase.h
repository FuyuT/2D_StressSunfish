#pragma once
#include	"Mof.h"

//シーンの列挙
enum tag_POPUPNO {
	POPUPNO_QUIT,
	POPUPNO_CAUSEOFDEATH,
	POPUPNO_CONTINUE,
	POPUPNO_BACKTOTITLE,
	POPUPNO_POSE,
	POPUPNO_RESULT,
	POPUPNO_RETRY,
	POPUPNO_TROPHY,
};

class CPopUpWindowBase
{
protected:
	int popUpPosX = 200;
	int popUpPosY = 50;
	bool endFlg = false;
	short	nextPopUp;
	//メモ書き取れてません　申し訳ない
	int     buttonResult;
public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//ゲッター
	int	  GetButtonResult() { return buttonResult; }
	void  SetButtonResult(int buttonResult) { this->buttonResult = buttonResult; }
	short GetNextPopUp() { return nextPopUp; }
	bool IsEnd() { return endFlg; }

};

