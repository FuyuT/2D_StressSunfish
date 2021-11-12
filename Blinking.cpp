#include "Blinking.h"

CBlinking::CBlinking() :
	count(0),
	speed(0),
	alpha(0),
	effectCount(0),
	countCheck(0),
	fadeIn(false),
	fadeOut(false)
{
}

CBlinking::~CBlinking()
{
}

void CBlinking::Update()
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
				return;
			}
			fadeIn = true;;
		}
	}
}
