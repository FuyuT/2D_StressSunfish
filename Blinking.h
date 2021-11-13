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

public:
	CBlinking();
	~CBlinking();
	void Update();

	//点滅する回数の指定(フェードイン、フェードアウトがセットで1回)
	void SetBlinkingCount(int blinkingCount) { count = blinkingCount; }
	//点滅する速さの指定(指定した数字の半分の速さでフェードインし、半分の速さでフェードアウトする)
	void SetBlinkingSpeed(int blinkingSpeed) { speed = blinkingSpeed; }
	//trueを入れると点滅しながら表示される
	void SetInStart(bool startFlg) { fadeIn = startFlg; }
	
	float GetAlpha() { return alpha; }
};

