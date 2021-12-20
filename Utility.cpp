#include "Utility.h"

bool CUtility::PosEditDataLoad(const char* filename, int& imageTotalNo, int& useImageTotalNo, CTexture*& imageArray, int*& sameImageTotalNo, float**& imagePosX, float**& imagePosY)
{
	FILE* fp = fopen(filename, "rt");
	if (fp == NULL)return false;

	//�t�@�C���̗e�ʊm�F
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//�������m�ہ@�o�b�t�@�ɓǂݍ���
	char* pBuffer = (char*)malloc(fSize + 1);
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';

	//�f�[�^�ǂݍ���

    //�摜
    //�摜�̑���
    imageTotalNo = atoi(strtok(pBuffer, ","));
    imageArray = new CTexture[imageTotalNo];
    useImageTotalNo = atoi(strtok(NULL, ","));
    //�ǂݍ��ރf�[�^�̑���
    sameImageTotalNo = new int[imageTotalNo];
    imagePosX = new float* [useImageTotalNo];
    imagePosY = new float* [useImageTotalNo];
    for (int n = 0; n < useImageTotalNo; n++)
    {
        imagePosX[n] = new float[useImageTotalNo];
        imagePosY[n] = new float[useImageTotalNo];
    }
    //�f�[�^�擾
    for (int imageNo = 0; imageNo < imageTotalNo; imageNo++)
    {
        //�����摜�̎g�p��
        sameImageTotalNo[imageNo] = atoi(strtok(NULL, ","));
        char* temp = strtok(NULL, ",");
        //�摜
        if (!imageArray[imageNo].Load(temp))return false;
        //�ʒu
        for (int sameTexNo = 0; sameTexNo < sameImageTotalNo[imageNo]; sameTexNo++)
        {
            //�`�摜�́A�f�[�^�`�Ԗ�
            imagePosX[imageNo][sameTexNo] = atof(strtok(NULL, ","));
            imagePosY[imageNo][sameTexNo] = atof(strtok(NULL, ","));
        }
    }

    //�t�@�C�������
    fclose(fp);
    free(pBuffer);
    return true;
}
