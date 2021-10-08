#include "Timer.h"

CTimer::CTimer():
	UpdateFlg(false),
	TotalTime(0),
	StartTime(0),
	NowTime(0)
{
}

CTimer::~CTimer()
{
}

void CTimer::Update()
{
	if (UpdateFlg)
	{
		NowTime -= CUtilities::GetFrameSecond();
		if (NowTime < 0)
		{
			UpdateFlg = false;
		}
	}
}

void CTimer::Render(int xpos, int ypos)
{
	CGraphicsUtilities::RenderString(xpos, ypos, "Time:%3.0f", NowTime);
}
