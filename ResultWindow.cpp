#include "ResultWindow.h"
#include <stdio.h>

CResultWindow::CResultWindow()
{

}
CResultWindow::~CResultWindow()
{
	Release();
}

void CResultWindow::Initialize()
{
	popUpTexture.Load("Pop_upラフ2.png");
	buttonNextTexture.Load("ButtonNext.png");
	resultTexture.Load("PopUpResult.png");
	newGetTexture.Load("NEW.png");
	if (numberOfTrophy[0] != TROPHY_NULL)
	{
		switch (numberOfTrophy[0])
		{
		case TROPHY_RIVER:
			trophyTexture.Load("1_川級.png");
			//説明文読み込み
			break;
		case  TROPHY_WATERFALL:
			trophyTexture.Load("2_滝級.png");
			//説明文読み込み
			break;
		case TROPHY_LAKE:
			trophyTexture.Load("3_湖級.png");
			//説明文読み込み
			break;
		case TROPHY_DAM:
			trophyTexture.Load("4_ダム級.png");
			//説明文読み込み
			break;
		case TROPHY_SEWER:
			trophyTexture.Load("5_下水道級.png");
			//説明文読み込み
			break;
		case TROPHY_INDIANOCEAN:
			trophyTexture.Load("6_インド洋級.png");
			//説明文読み込み
			break;
		case TROPHY_AMAZONROVER:
			trophyTexture.Load("7_アマゾン川級.png");
			//説明文読み込み
			break;
		case TROPHY_OCEAN:
			trophyTexture.Load("8_海級.png");
			//説明文読み込み
			break;
		case TROPHY_SEAOFJAPAN:
			trophyTexture.Load("9_日本海級.png");
			//説明文読み込み
			break;
		case TROPHY_AROUNDTHEGLOBE:
			trophyTexture.Load("10_地球一周級.png");
			//説明文読み込み
			break;
		case TROPHY_ZEROMOTIVATION:
			trophyTexture.Load("S1_やる気ゼロ級.png");
			//説明文読み込み
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture.Load("S5_富士山級.png");
			//説明文読み込み
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture.Load("S4_大阪マラソン級.png");
			//説明文読み込み
			break;
		case TROPHY_BIWALAKE:
			trophyTexture.Load("S2_琵琶湖級.png");
			//説明文読み込み
			break;
		case TROPHY_JACKPOD:
			trophyTexture.Load("S3_ジャックポット級.png");
			//説明文読み込み
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture.Load("S6_才能魔級.png");
			//説明文読み込み
			break;
		}
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		switch (numberOfTrophy[1])
		{
		case TROPHY_ZEROMOTIVATION:
			trophyTexture2.Load("S1_やる気ゼロ級.png");
			//説明文読み込み
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture2.Load("S5_富士山級.png");
			//説明文読み込み
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture2.Load("S4_大阪マラソン級.png");
			//説明文読み込み
			break;
		case TROPHY_BIWALAKE:
			trophyTexture2.Load("S2_琵琶湖級.png");
			//説明文読み込み
			break;
		case TROPHY_JACKPOD:
			trophyTexture2.Load("S3_ジャックポット級.png");
			//説明文読み込み
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture2.Load("S6_才能魔級.png");
			//説明文読み込み
			break;
		}
	}
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		switch (numberOfTrophy[2])
		{
		case TROPHY_ZEROMOTIVATION:
			trophyTexture3.Load("S1_やる気ゼロ級.png");
			//説明文読み込み
			break;
		case TROPHY_MOUNTFJI:
			trophyTexture3.Load("S5_富士山級.png");
			//説明文読み込み
			break;
		case TROPHY_OSAKAMARATHON:
			trophyTexture3.Load("S4_大阪マラソン級.png");
			//説明文読み込み
			break;
		case TROPHY_BIWALAKE:
			trophyTexture3.Load("S2_琵琶湖級.png");
			//説明文読み込み
			break;
		case TROPHY_JACKPOD:
			trophyTexture3.Load("S3_ジャックポット級.png");
			//説明文読み込み
			break;
		case TROPHY_TALENTEDDEMON:
			trophyTexture3.Load("S6_才能魔級.png");
			//説明文読み込み
			break;
		}
	}

	buttonSelect = 0;
	font.Create(64, "MS　明朝");
	distanceFont.Create(172, "MS　明朝");
	endFlg = false;
}
void CResultWindow::Update()
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
		if (g_pInput->IsKeyPush(MOFKEY_DOWN) || g_pInput->IsKeyPush(MOFKEY_UP) || g_pInput->IsKeyPush(MOFKEY_RIGHT) || g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			keyModeFlg = true;
			buttonSelect = 1;
		}
		buttonNextScale = scaleMini;
	}
	else if (buttonSelect == 1)
	{
		buttonNextScale = scaleController.ScaleControll(buttonNextScale, scaleMax, scaleMini, scaleSpeed);

		if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && !keyModeFlg || g_pInput->IsKeyPush(MOFKEY_SPACE))
		{
			Release();
			endFlg = true;
			nextPopUp = POPUPNO_CONTINUE;
		}
	}

}
void CResultWindow::Render()
{
	popUpTexture.Render(popUpPosX, popUpPosY);
	resultTexture.Render(resultTextPosX, resultTextPosY);
	scaleController.ScaleRender(&buttonNextTexture,buttonNextPosX,buttonNextPosY,buttonNextScale);

	if (numberOfTrophy[0] != TROPHY_NULL)
	{
		if (numberOfTrophy[0] == TROPHY_RIVER)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "川級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_WATERFALL)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "滝級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_LAKE)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "湖級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_DAM)
		{
			font.RenderString(820, 750, MOF_XRGB(0, 0, 0), "ダム級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_SEWER)
		{
			font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "下水道級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_INDIANOCEAN)
		{
			font.RenderString(880, 750, MOF_XRGB(0, 0, 0), "インド洋級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_AMAZONROVER)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "アマゾン川級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_OCEAN)
		{
			font.RenderString(850, 750, MOF_XRGB(0, 0, 0), "海級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_SEAOFJAPAN)
		{
			font.RenderString(890, 750, MOF_XRGB(0, 0, 0), "日本海級");
			//説明文描画
		}
		if (numberOfTrophy[0] == TROPHY_AROUNDTHEGLOBE)
		{
			font.RenderString(870, 750, MOF_XRGB(0, 0, 0), "地球一周級");
			//説明文描画
		}
	}
	//トロフィー描画
	if (numberOfTrophy[2] != TROPHY_NULL)
	{
		trophyTexture3.Render(trophyTexturePosX - 150, trophyTexturePosY);
	}
	if (numberOfTrophy[1] != TROPHY_NULL)
	{
		trophyTexture2.Render(trophyTexturePosX - 100, trophyTexturePosY);
	}
	trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
	//新規ゲットの場合newを描画
	if (newGetTrophyFlg)
	{
		newGetTexture.Render(trophyTexturePosX - 50, trophyTexturePosY + trophyTexture.GetHeight() + 10);
	}

	//m描画
	if (distance < 1000000)
	{
		sprintf_s(meter,10, "%dm", distance);
	}
	else
	{
		sprintf_s(meter, 10 ,"%dm", 99999);
	}
	CRectangle rec;
	CRectangle drec;
	CGraphicsUtilities::CalculateStringRect(0, 0, meter, rec);
	float cx = popUpTexture.GetWidth() * 0.5f;
	float cy = popUpTexture.GetHeight() * 0.5f;
	float w = rec.GetWidth();
	float h = rec.GetHeight();
	rec.Top = cy - h * 0.5f;
	rec.Bottom = rec.Top + h;
	rec.Left = cx - w * 0.5f;
	rec.Right = rec.Left + w;
	distanceFont.RenderString(cx - rec.GetWidth() * 0.5f, rec.Top -50, MOF_XRGB(0, 0, 0), meter);
}
void CResultWindow::Release()
{
	newGetTexture.Release();
	distanceFont.Release();
	resultTexture.Release();
	font.Release();
	trophyTexture.Release();
	trophyTexture2.Release();
	trophyTexture3.Release();
	popUpTexture.Release();
	buttonNextTexture.Release();
}