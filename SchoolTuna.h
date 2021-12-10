#pragma once
#include "ObstacleBase.h"
#define  SCHOOLTUNA_RECT_TOP_ADJ 100
#define  SCHOOLTUNA_RECT_LEFT_ADJ 0
#define  SCHOOLTUNA_RECT_RIGHT_ADJ 450
#define  SCHOOLTUNA_RECT_BUTTOM_ADJ 350

class CSchoolTuna : public CObstacleBase
{
private:
	CTexture keikokuTexture;

	//アニメーション
	CSpriteMotionController motion;
	CSpriteMotionController keikokumotion;
public:
	CSchoolTuna();
	~CSchoolTuna();
	bool Load()override;
	void Initialize()override;
	void Update(float wx, float wy)override;
	void Render(float wx, float wy)override;
	void RenderDebug(float wx, float wy)override;
	void Release()override;
	CRectangle GetRect() {
		return CRectangle(pos.x + SCHOOLTUNA_RECT_LEFT_ADJ, pos.y + SCHOOLTUNA_RECT_TOP_ADJ,
			pos.x + SCHOOLTUNA_RECT_RIGHT_ADJ, pos.y + SCHOOLTUNA_RECT_BUTTOM_ADJ);
	}
	void SetShow(bool flg)
	{
		showFlg = flg;
	}
	bool GetShow()
	{
		return showFlg;
	}
	void SetPosx(int posx)
	{
		pos.x = posx;
	}
	void SetPosy(int posy)
	{
		pos.y = posy;
	}
};

