#pragma once
#include "Mof.h"
#include "Timer.h"

class CBlinking
{
private:
	CTimer blinkingTimer;
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
};

