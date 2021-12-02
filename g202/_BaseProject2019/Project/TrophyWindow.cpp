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
	buttonSelect = 0;
	font.Create(64, "MS　明朝");
	endFlg = false;
}
void CTrophyWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		keyModeFlg = false;
		buttonSelect = 1;
	}
	else
	{
		if (!keyModeFlg)
			buttonSelect = 0;
	}

	if (buttonSelect == 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_DOWN) || g_pInput->IsKeyPush(MOFKEY_UP))
		{
			keyModeFlg = true;
			buttonSelect = 1;
		}
		buttonBackScale = scaleMini;
	}
	else if (buttonSelect == 1)
	{
		buttonBackScale = scaleController.ScaleControll(buttonBackScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
		}
	}
}
void CTrophyWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	trophyTexture.Render(trophyTexturePosX,trophyTexturePosY);
	if (buttonResult == TROPHY_RIVER)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "川級");
		//説明文描画
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "滝級");
		//説明文描画
	}
	if (buttonResult == TROPHY_LAKE)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "湖級");
		//説明文描画
	}
	if (buttonResult == TROPHY_DAM)
	{
		font.RenderString(820, 250, MOF_XRGB(0, 0, 0), "ダム級");
		//説明文描画
	}
	if (buttonResult == TROPHY_SEWER)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "下水道級");
		//説明文描画
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		font.RenderString(780, 250, MOF_XRGB(0, 0, 0), "インド洋級");
		//説明文描画
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "アマゾン川級");
		//説明文描画
	}
	if (buttonResult == TROPHY_OCEAN)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "海級");
		//説明文描画
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "日本海級");
		//説明文描画
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		font.RenderString(770, 250, MOF_XRGB(0, 0, 0), "地球一周級");
		//説明文描画
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		font.RenderString(745, 250, MOF_XRGB(0, 0, 0), "やる気ゼロ級");
		//説明文描画
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "富士山級");
		//説明文描画
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		font.RenderString(730, 250, MOF_XRGB(0, 0, 0), "大阪マラソン級");
		//説明文描画
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "琵琶湖級");
		//説明文描画
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		font.RenderString(700, 250, MOF_XRGB(0, 0, 0), "ジャックポット級");
		//説明文描画
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		font.RenderString(765, 250, MOF_XRGB(0, 0, 0), "才能魔級");
		//説明文描画
	}

	scaleController.ScaleRender(&buttonBackTexture,buttonBackPosX,buttonBackPosY,buttonBackScale);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	trophyTexture.Release();
	buttonBackTexture.Release();
}