#pragma once
#include "Mof.h"
class Enemy
{
private:
	CTexture    seaTurtleTexture;
	CTexture*	texture;
	float		posX;
	float		posY;
	float		speedX;
	float		speedY;
	bool		show;
	int			type;
	CRectangle rect = CRectangle(0, 0, 10, 10);

	int ePosX;
	int ePosY;

public:
	Enemy();
	~Enemy();
	void Initialize();
	void Start(float px, float py, int t);
	void Update();
	void Render(float px, float py);
	void Release();

	void SetTexture(CTexture* pt) { texture = pt; }
	bool GetShow() { return show; }
	void UpdateType0() { type = 0; };
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
		return type;
	}

};

