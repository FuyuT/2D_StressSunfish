#pragma once
#include "Mof.h"

class CTimer
{
private:
	bool		UpdateFlg;
	float       TotalTime;
	float		StartTime;
	float		NowTime;
public:
	CTimer();
	~CTimer();
	//測る時間のセット
	void SetTotalTime(double TotalTime) { NowTime=TotalTime; }
	void StartTimer() { UpdateFlg = true; }
	void StopTimer() { UpdateFlg = false; }
	//計測
	void Update();
	void Render(int xpos,int ypos);

	bool GetUpdateFlg() { return UpdateFlg; }
	float GetNowtime() { return NowTime; }
};