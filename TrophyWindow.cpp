#include "TrophyWindow.h"
#include "SceneTrophyCollection.h"

CTrophyWindow::CTrophyWindow()
{

}
CTrophyWindow::~CTrophyWindow()
{

}

void CTrophyWindow::Initialize()
{
	popUpTexture.Load("Pop_upt2.png");
	buttonBackTexture.Load("ButtonBack.png");

	if (buttonResult == TROPHY_RIVER)
	{
		trophyTexture.Load("1_ì.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		trophyTexture.Load("2_ê.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_LAKE)
	{
		trophyTexture.Load("3_Î.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_DAM)
	{
		trophyTexture.Load("4__.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_SEWER)
	{
		trophyTexture.Load("5_º¹.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		trophyTexture.Load("6_Chm.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		trophyTexture.Load("7_A}]ì.png");
		//à¾¶ÇÝÝ
	}	
	if (buttonResult == TROPHY_OCEAN)
	{
		trophyTexture.Load("8_C.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Load("9_ú{C.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		trophyTexture.Load("10_nêü.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		trophyTexture.Load("S1_âéC[.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		trophyTexture.Load("S5_xmR.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		trophyTexture.Load("S4_åã}\.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		trophyTexture.Load("S2_úiÎ.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		trophyTexture.Load("S3_WbN|bg.png");
		//à¾¶ÇÝÝ
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		trophyTexture.Load("S6_Ë\.png");
		//à¾¶ÇÝÝ
	}

	font.Create(64, "MS@¾©");
	endFlg = false;
}
void CTrophyWindow::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);

	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY))
	{
		Release();
		endFlg = true;
	}
}
void CTrophyWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	trophyTexture.Render(trophyTexturePosX,trophyTexturePosY);
	if (buttonResult == TROPHY_RIVER)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "ì");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "ê");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_LAKE)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "Î");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_DAM)
	{
		font.RenderString(820, 250, MOF_XRGB(0, 0, 0), "_");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_SEWER)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "º¹");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		font.RenderString(780, 250, MOF_XRGB(0, 0, 0), "Chm");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "A}]ì");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_OCEAN)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "C");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "ú{C");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		font.RenderString(770, 250, MOF_XRGB(0, 0, 0), "nêü");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		font.RenderString(745, 250, MOF_XRGB(0, 0, 0), "âéC[");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "xmR");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		font.RenderString(730, 250, MOF_XRGB(0, 0, 0), "åã}\");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "úiÎ");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		font.RenderString(700, 250, MOF_XRGB(0, 0, 0), "WbN|bg");
		//à¾¶`æ
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		font.RenderString(765, 250, MOF_XRGB(0, 0, 0), "Ë\");
		//à¾¶`æ
	}

	buttonBackTexture.Render(buttonBackPosX, buttonBackPosY);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	trophyTexture.Release();
	buttonBackTexture.Release();
}