#pragma once
#include "Mof.h"

class CFade
{
private:
	enum FADE_MOTION
	{
		FADE_MOTION_OUT,
		FADE_MOTION_IN,

		FADE_MOTION_COUNT,
	};
	CTexture texture;
	CSpriteMotionController	motion;

	bool fadeOutEndFlg;
	bool startFlg;

public:
	CFade();
	~CFade();
	void Load();
	void Initialize();
	void Update();
	void Render();
	void Release();
	void FadeIn()
	{
		if (!startFlg)
		{
			motion.ChangeMotion(FADE_MOTION_IN, false);
			startFlg = true;
		}
	}
	void FadeOut()
	{
		motion.ChangeMotion(FADE_MOTION_OUT, false);
	}
	bool GetFadeOutEnd()
	{
		return fadeOutEndFlg;
	}
	bool GetFade()
	{
		if (!motion.IsEndMotion())
		{
			return true;
		}
		return false;
	}
};

