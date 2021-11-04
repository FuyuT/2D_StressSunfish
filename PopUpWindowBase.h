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
	int		dethResult;
	//新規入手フラグ
	bool	newGetDethFlg;
	bool	newGetTrophyFlg;
public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//ゲッター
	int	  GetButtonResult() { return buttonResult; }
	void  SetButtonResult(int setButtonResult) { buttonResult = setButtonResult; }
	void  SetDethResult(int setDethResult) { dethResult = setDethResult; }
	void  SetNewGetDeth(bool setNewGetDethFlg) { newGetDethFlg = setNewGetDethFlg; }
	void  SetNewGetTrophy(bool setNewGetTrophyFlg) {newGetTrophyFlg = setNewGetTrophyFlg ; }
	short GetNextPopUp() { return nextPopUp; }
	bool IsEnd() { return endFlg; }

};

