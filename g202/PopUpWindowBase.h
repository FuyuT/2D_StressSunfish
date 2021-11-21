#pragma once
#include	"Mof.h"
#include "SceneTrophyCollection.h"

constexpr int popUpPosX = 200;
constexpr int popUpPosY = 50;

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
	bool endFlg = false;
	short	nextPopUp;
	//メモ書き取れてません　申し訳ない
	int     buttonResult;
	int		dethResult;
	//新規入手フラグ
	bool	newGetDethFlg;
	bool	newGetTrophyFlg;
	int		numberOfTrophy[3];
	int		distance;
public:
	CPopUpWindowBase() {}
	virtual ~CPopUpWindowBase() {}
	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Render() {}
	virtual void Release() {}
	//ゲッター
	int	  GetButtonResult() { return buttonResult; }
	short GetNextPopUp() { return nextPopUp; }
	//
	void  SetButtonResult(int setButtonResult) { buttonResult = setButtonResult; }
	void  SetDethResult(int setDethResult) { dethResult = setDethResult; }
	void  SetNewGetDeth(bool setNewGetDethFlg) { newGetDethFlg = setNewGetDethFlg; }
	void  SetNewGetTrophy(bool setNewGetTrophyFlg) {newGetTrophyFlg = setNewGetTrophyFlg ; }
	//トロフィーポップアップ用　3個まで保存して取得できるようにする。
	void SetNumberOfTrophy(int *trophy) {
		for (int i = 0; i < 3; i++)
		{
			numberOfTrophy[i] =trophy[i];
		}
	}
	void SetDistance(int i) { distance = i; };
	bool IsEnd() { return endFlg; }

};

