#include "TrophyWindow.h"
#include "SceneTrophyCollection.h"

CTrophyWindow::CTrophyWindow()
{

}
CTrophyWindow::~CTrophyWindow()
{
	Release();
}

void CTrophyWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonBackTexture.Load("ButtonBack.png");
	//フォント
	font.Load(fontAdd, fontName);
	font.Create(156, fontName);

	if (buttonResult == TROPHY_RIVER)
	{
		trophyTexture.Load("1_川級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		trophyTexture.Load("2_滝級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_LAKE)
	{
		trophyTexture.Load("3_湖級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_DAM)
	{
		trophyTexture.Load("4_ダム級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_SEWER)
	{
		trophyTexture.Load("5_下水道級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		trophyTexture.Load("6_インド洋級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		trophyTexture.Load("7_アマゾン川級.png");
		//説明文読み込み
	}	
	if (buttonResult == TROPHY_OCEAN)
	{
		trophyTexture.Load("8_海級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Load("9_日本海級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		trophyTexture.Load("10_地球一周級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		trophyTexture.Load("S1_やる気ゼロ級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		trophyTexture.Load("S5_富士山級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		trophyTexture.Load("S4_大阪マラソン級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		trophyTexture.Load("S2_琵琶湖級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		trophyTexture.Load("S3_ジャックポット級.png");
		//説明文読み込み
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		trophyTexture.Load("S6_才能魔級.png");
		//説明文読み込み
	}
	buttonSelect = 1;
	endFlg = false;
}
void CTrophyWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect().CollisionPoint(mousePosX, mousePosY) && buttonSelect != 1)
	{
		cSound->Play(SOUND_BUTTON_SELECT);
		buttonSelect = 1;
	}
	

if (buttonSelect == 1)
	{
		buttonBackScale = scaleController.ScaleControll(buttonBackScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			cSound->Play(SOUND_BUTTON_PUSH);
			Release();
			endFlg = true;
		}
	}
}
void CTrophyWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	if (buttonResult == TROPHY_RIVER)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "川級");
		//説明文描画
		font.RenderStringScale(415,675, 0.6f ,MOF_XRGB(0, 0, 0), "駆け出しの最初にもらえるトロフィー");
		font.RenderStringScale(615, 775, 0.6f, MOF_XRGB(0, 0, 0), "川並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "滝級");
		//説明文描画
		font.RenderStringScale(545, 675, 0.6f, MOF_XRGB(0, 0, 0), "まだまだ半人前のトロフィー");
		font.RenderStringScale(615, 775, 0.6f, MOF_XRGB(0, 0, 0), "滝並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_LAKE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "湖級");
		//説明文描画
				//説明文描画
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "そこそこ頑張っているトロフィー");
		font.RenderStringScale(610, 775, 0.6f, MOF_XRGB(0, 0, 0), "湖並みの距離泳いだ証");
	}
	if (buttonResult == TROPHY_DAM)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(750, 225, MOF_XRGB(0, 0, 0), "ダム級");
		//説明文描画
		font.RenderStringScale(550, 675, 0.6f, MOF_XRGB(0, 0, 0), "一般人レベルのトロフィー");
		font.RenderStringScale(550, 775, 0.6f, MOF_XRGB(0, 0, 0), "ダム並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_SEWER)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(700, 220, MOF_XRGB(0, 0, 0), "下水道級");
		//説明文描画
		font.RenderStringScale(640, 675, 0.6f, MOF_XRGB(0, 0, 0), "一人前のトロフィー");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "下水道並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(630, 225, MOF_XRGB(0, 0, 0), "インド洋級");
		//説明文描画
		font.RenderStringScale(340, 675, 0.6f, MOF_XRGB(0, 0, 0), "ちょっとやりこみがある鉄人のトロフィー");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "インド洋並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(590, 250, MOF_XRGB(0, 0, 0), "アマゾン川級");
		//説明文描画
		font.RenderStringScale(340, 675, 0.6f, MOF_XRGB(0, 0, 0), "相当やりこんでいるゲーマーのトロフィー");
		font.RenderStringScale(500, 775, 0.6f, MOF_XRGB(0, 0, 0), "アマゾン川並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_OCEAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "海級");
		//説明文描画
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "やりこんでいる達人のトロフィー");
		font.RenderStringScale(600, 775, 0.6f, MOF_XRGB(0, 0, 0), "海並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "日本海級");
		//説明文描画
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "やりこみ過ぎな超人のトロフィー");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "日本海並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(635, 225, MOF_XRGB(0, 0, 0), "地球一周級");
		//説明文描画
		font.RenderStringScale(340, 675, 0.55, MOF_XRGB(0, 0, 0), "もはや天才の才を持ち合わせる人のトロフィー");
		font.RenderStringScale(560, 775, 0.55f, MOF_XRGB(0, 0, 0), "地球一周並みの距離を泳いだ証");
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString( 590, 225, MOF_XRGB(0, 0, 0), "やる気ゼロ級");
		//説明文描画
		font.RenderStringScale(445, 675, 0.6f, MOF_XRGB(0, 0, 0), "やる気が見られない人のトロフィー");
		font.RenderStringScale(630, 775, 0.6f, MOF_XRGB(0, 0, 0), "...やる気あります？");
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		scaleController.ScaleRender(&trophyTexture,trophyTexturePosX, trophyTexturePosY - 130,1.7f);
		//trophyTexture.RenderScale(trophyTexturePosX, trophyTexturePosY -75,1.5f);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "富士山級");
		//説明文描画
		font.RenderStringScale(360, 675, 0.55f, MOF_XRGB(0, 0, 0), "富士山並みの距離を泳いだ特別なトロフィー");
		font.RenderStringScale(520, 775, 0.55f, MOF_XRGB(0, 0, 0), "これで富士山を登山したも同然だ！");
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(535, 225, MOF_XRGB(0, 0, 0), "大阪マラソン級");
		//説明文描画
		font.RenderStringScale(330, 675, 0.5f, MOF_XRGB(0, 0, 0), "大阪マラソン並みの距離を泳いだ特別なトロフィー");
		font.RenderStringScale(510, 775, 0.5f, MOF_XRGB(0, 0, 0), "次は陸上で完走を目指してみよう！");
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "琵琶湖級");
		//説明文描画
		font.RenderStringScale(355, 675, 0.55f, MOF_XRGB(0, 0, 0), "琵琶湖並みの距離を泳いだ特別なトロフィー");
		font.RenderStringScale(530, 775, 0.55f, MOF_XRGB(0, 0, 0), "証琵琶湖って意外と汚いらしい");
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(500, 225, MOF_XRGB(0, 0, 0), "ジャックポット級");
		//説明文描画
		font.RenderStringScale(640, 675, 0.6f, MOF_XRGB(0, 0, 0), "ジャックポット！！");
		font.RenderStringScale(610, 775, 0.6f, MOF_XRGB(0, 0, 0), "777！！大当たり！！");
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		trophyTexture.Render(trophyTexturePosX+30, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "才能魔級");
		//説明文描画
		font.RenderStringScale(440, 675, 0.6f, MOF_XRGB(0, 0, 0), "才能魔並みの距離を泳いだ特別な証");
		font.RenderStringScale(540, 775, 0.6f, MOF_XRGB(0, 0, 0), "相当やりこみすぎててやばい");
	}
	scaleController.ScaleRender(&buttonBackTexture, buttonBackPosX, buttonBackPosY, buttonBackScale);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	trophyTexture.Release();
	buttonBackTexture.Release();
}

void CTrophyWindow::MouseCollision(int posX, int posY)
{
}
