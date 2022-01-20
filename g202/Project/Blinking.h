#pragma once
#include "Mof.h"
#include "Timer.h"

class CBlinking
{
private:
	//点滅する回数
	int count;
	//点滅する速さ
	int speed;

	float alpha;
	int effectCount;
	int countCheck;

	bool fadeIn;
	bool fadeOut;

	bool start;

public:
	CBlinking();
	~CBlinking();
	void Initialize();
	void Update();

	//点滅する回数の指定(フェードイン、フェードアウトがセットで1回)
	void SetBlinkingCount(int blinkingCount) { count = blinkingCount; }
	//点滅する速さの指定(指定した数字の半分の速さでフェードインし、半分の速さでフェードアウトする)
	void SetBlinkingSpeed(int blinkingSpeed) { speed = blinkingSpeed; }
	//trueを入れると点滅しながら表示される
	void SetInStart(bool startFlg) { start = startFlg; }
	//点滅した回数を返す(0からカウント)
	int GetCount() { return countCheck; }
	//現在の状態を返す
	bool GetFadeIn() { return fadeIn; }
	bool GetFadeOut() { return fadeIn; }

	float GetAlpha() { return alpha; }
};

