#pragma once
#include "Mof.h"
class CUtility
{
private:
	CUtility() = delete;
	~CUtility() = delete;
public:
	static bool PosEditDataLoad(const char* filename, int& imageTotalNo, int& useImageTotalNo, CTexture*& imageArray, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY);
};

