#include "Blinking.h"

CBlinking::CBlinking() :
	count(0),
	speed(0),
	alpha(0),
	effectCount(0),
	countCheck(0),
	start(false),
	fadeIn(true),
	fadeOut(false)
{
}

CBlinking::~CBlinking()
{
}

void CBlinking::Initialize()
{
	start = false;
	fadeIn = true;
	fadeOut = false;
}

void CBlinking::Update()
{
	if (start)
	{
		if (fadeIn)
		{
			alpha = effectCount / (speed * 0.5f);
			effectCount++;

			if (effectCount >= speed * 0.5)
			{
				fadeIn = false;
				fadeOut = true;
			}
		}
		else if (fadeOut)
		{
			alpha = (1.0f - ((effectCount - (speed * 0.5f)) / (speed * 0.5f)));
			effectCount++;

			if (effectCount >= speed)
			{
				effectCount = 0;
				fadeOut = false;
				countCheck++;
				if (countCheck >= count)
				{
					alpha = 0.0f;
					countCheck = 0;
					return;
				}
				fadeIn = true;
			}
		}
	}
	else if(!start)
	{
		effectCount = 0;
		alpha = 0.0f;
		countCheck = 0;
		Initialize();
	}
}
