#pragma once
#include "Mof.h"
class CUtility
{
private:
	CUtility() = delete;
	~CUtility() = delete;
public:
	static bool GetEditObjectData(const char* filename, CTexture& tex, int& posTotalNo, Vector2*& pos);
	static bool EditDataPosInitialize(const char* filename, int& imageTotalNo, int& useImageTotalNo, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY);
};

