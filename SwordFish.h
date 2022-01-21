#pragma once
#include "ObstacleBase.h"

class CSwordFish :
    public CObstacleBase
{
	private:
		#define  SWORDFISH_RECT_TOP_ADJ 100
		#define  SWORDFISH_RECT_LEFT_ADJ 0
		#define  SWORDFISH_RECT_RIGHT_ADJ 446
		#define  SWORDFISH_RECT_BUTTOM_ADJ 200
		CTexture keikokuTexture;

		//アニメーション
		CSpriteMotionController motion;
		CSpriteMotionController keikokumotion;
	public:
		CSwordFish();
		~CSwordFish();
		bool Load()override;
		void Initialize()override;
		void Update(float wx, float wy)override;
		void Render(float wx, float wy)override;
		void RenderDebug(float wx, float wy)override;
		void Release()override;
		CRectangle GetRect() {
			return CRectangle(pos.x + SWORDFISH_RECT_LEFT_ADJ, pos.y + SWORDFISH_RECT_TOP_ADJ,
				pos.x + SWORDFISH_RECT_RIGHT_ADJ, pos.y + SWORDFISH_RECT_BUTTOM_ADJ);
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

