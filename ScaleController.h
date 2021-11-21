#pragma once
class ScaleController
{
private:
	bool scaleFlg = true;

public:
	ScaleController();
	~ScaleController();
	float ScaleControll(float scale ,float max ,float mini , float speed);
};

