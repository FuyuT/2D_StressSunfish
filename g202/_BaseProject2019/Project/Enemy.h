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
	int type = 2;
public:
	Enemy();
	~Enemy();
	void Initialize();
	void Start(float px, float py);
	void Update();
	void Render();
	void SetTexture(CTexture* pt) { texture = pt; }
	bool GetShow() { return show; }
	CRectangle GetRect()
	{
		return rect;
	}
	int GetType()
	{
		return type;
	}

};

