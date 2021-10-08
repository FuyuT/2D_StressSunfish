#pragma once
#include "Mof.h"
class Enemy
{
private:
	CTexture*	texture;
	float		posX;
	float		posY;
	float		speedX;
	float		speedY;
	bool		show;
	CRectangle rect = CRectangle(0, 0, 10, 10);
	int type = 0;

	int ePosX;
	int ePosY;
public:
	Enemy();
	~Enemy();
	void Initialize();
	void Start(float px, float py);
	void Update();
	void Render(float wx, float wy);
	void SetTexture(CTexture* pt) { texture = pt; }


	bool GetShow() { return show; }
	CRectangle GetRect()
	{
		return CRectangle(
			posX,
			posY,
			posX + 100,
			posY + 100
		);
	}
	void SetShow(bool flg)
	{
		show = flg;
	}
	int GetType()
	{
		return 0;
	}

};

