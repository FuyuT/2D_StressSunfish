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
public:
	Enemy();
	~Enemy();
	void Initialize();
	void Start(float px, float py);
	void Update();
	void Render();
	void SetTexture(CTexture* pt) { texture = pt; }
	bool GetShow() { return show; }
};

