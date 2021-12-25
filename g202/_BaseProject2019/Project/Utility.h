#pragma once
#include "Mof.h"
class CUtility
{
private:
	CUtility() = delete;
	~CUtility() = delete;
public:
	static bool EditDataLoad(const char* filename, int& imageTotalNo, int& useImageTotalNo, CTexture*& imageArray, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY);
	static bool EditDataPosInitialize(const char* filename, int& imageTotalNo, int& useImageTotalNo, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY);
};

