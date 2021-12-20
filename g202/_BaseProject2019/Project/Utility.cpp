#include "Utility.h"

bool CUtility::PosEditDataLoad(const char* filename, int& imageTotalNo, int& useImageTotalNo, CTexture*& imageArray, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY)
{
	FILE* fp = fopen(filename, "rt");
	if (fp == NULL)return false;

	//ファイルの容量確認
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//メモリ確保　バッファに読み込み
	char* pBuffer = (char*)malloc(fSize + 1);
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';

	//データ読み込み

    //画像
    //画像の総数
    imageTotalNo = atoi(strtok(pBuffer, ","));
    imageArray = new CTexture[imageTotalNo];
    useImageTotalNo = atoi(strtok(NULL, ","));
    //読み込むデータの総数
    sameImageTotalNo = new int[imageTotalNo];
    imagePosX = new float* [useImageTotalNo];
    imagePosY = new float* [useImageTotalNo];
    for (int n = 0; n < useImageTotalNo; n++)
    {
        imagePosX[n] = new float[useImageTotalNo];
        imagePosY[n] = new float[useImageTotalNo];
    }
    //データ取得
    for (int imageNo = 0; imageNo < imageTotalNo; imageNo++)
    {
        //同じ画像の使用回数
        sameImageTotalNo[imageNo] = atoi(strtok(NULL, ","));
        char* temp = strtok(NULL, ",");
        //画像
        if (!imageArray[imageNo].Load(temp))return false;
        //位置
        for (int sameTexNo = 0; sameTexNo < sameImageTotalNo[imageNo]; sameTexNo++)
        {
            //～画像の、データ～番目
            imagePosX[imageNo][sameTexNo] = atof(strtok(NULL, ","));
            imagePosY[imageNo][sameTexNo] = atof(strtok(NULL, ","));
        }
    }

    //ファイルを閉じる
    fclose(fp);
    free(pBuffer);
    return true;
}
