#include "Enemy.h"

Enemy::Enemy() :
	texture(NULL),
	posX(0.0f),
	posY(0.0f),
	speedX(0.0f),
	speedY(0.0f),
	show(true),
	type(0){

}

Enemy::~Enemy() {
}

void Enemy::Initialize() {
	posX = 500;
	posY = 500;
	speedX = 0;
	speedY = 0;
	show = true;
	seaTurtleTexture.Load("ウミガメ ラフ.png");
	//texture->Load("ウミガメ ラフ.png");
}

void Enemy::Start(float px, float py,int t) {
	speedX = 1;
	speedY = 0;
	type = t;
	show = true;
}

void Enemy::Update() {
	if (!show) {
		return;
	}
	posX -= speedX;
	if (posX + seaTurtleTexture.GetWidth() <= 0) {
		show = false;
	}
}

void Enemy::Render(float px,float py) {
	if (!show) {
		return;
	}
	seaTurtleTexture.Render(posX - px, posY - py);
	CRectangle seaTurtleRect(posX - px, posY - py, posX + 500 - px, posY + 450 - scrollValueY);
    CGraphicsUtilities::RenderRect(seaTurtleRect, MOF_COLOR_BLACK);

}

void Enemy::Release()
{
	seaTurtleTexture.Release();
}
