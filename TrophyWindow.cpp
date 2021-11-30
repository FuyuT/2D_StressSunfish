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
	popUpTexture.Load("Pop_up���t2.png");
	buttonBackTexture.Load("ButtonBack.png");

	if (buttonResult == TROPHY_RIVER)
	{
		trophyTexture.Load("1_�싉.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		trophyTexture.Load("2_�ꋉ.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_LAKE)
	{
		trophyTexture.Load("3_�΋�.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_DAM)
	{
		trophyTexture.Load("4_�_����.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_SEWER)
	{
		trophyTexture.Load("5_��������.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		trophyTexture.Load("6_�C���h�m��.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		trophyTexture.Load("7_�A�}�]���싉.png");
		//�������ǂݍ���
	}	
	if (buttonResult == TROPHY_OCEAN)
	{
		trophyTexture.Load("8_�C��.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Load("9_���{�C��.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		trophyTexture.Load("10_�n�������.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		trophyTexture.Load("S1_���C�[����.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		trophyTexture.Load("S5_�x�m�R��.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		trophyTexture.Load("S4_���}���\����.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		trophyTexture.Load("S2_���i�΋�.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		trophyTexture.Load("S3_�W���b�N�|�b�g��.png");
		//�������ǂݍ���
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		trophyTexture.Load("S6_�˔\����.png");
		//�������ǂݍ���
	}
	buttonSelect = 0;
	font.Create(64, "MS�@����");
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
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�싉");
		//�������`��
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�ꋉ");
		//�������`��
	}
	if (buttonResult == TROPHY_LAKE)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�΋�");
		//�������`��
	}
	if (buttonResult == TROPHY_DAM)
	{
		font.RenderString(820, 250, MOF_XRGB(0, 0, 0), "�_����");
		//�������`��
	}
	if (buttonResult == TROPHY_SEWER)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "��������");
		//�������`��
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		font.RenderString(780, 250, MOF_XRGB(0, 0, 0), "�C���h�m��");
		//�������`��
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		font.RenderString(750, 250, MOF_XRGB(0, 0, 0), "�A�}�]���싉");
		//�������`��
	}
	if (buttonResult == TROPHY_OCEAN)
	{
		font.RenderString(850, 250, MOF_XRGB(0, 0, 0), "�C��");
		//�������`��
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "���{�C��");
		//�������`��
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		font.RenderString(770, 250, MOF_XRGB(0, 0, 0), "�n�������");
		//�������`��
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		font.RenderString(745, 250, MOF_XRGB(0, 0, 0), "���C�[����");
		//�������`��
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "�x�m�R��");
		//�������`��
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		font.RenderString(730, 250, MOF_XRGB(0, 0, 0), "���}���\����");
		//�������`��
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		font.RenderString(790, 250, MOF_XRGB(0, 0, 0), "���i�΋�");
		//�������`��
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		font.RenderString(700, 250, MOF_XRGB(0, 0, 0), "�W���b�N�|�b�g��");
		//�������`��
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		font.RenderString(765, 250, MOF_XRGB(0, 0, 0), "�˔\����");
		//�������`��
	}

	scaleController.ScaleRender(&buttonBackTexture,buttonBackPosX,buttonBackPosY,buttonBackScale);
}
void CTrophyWindow::Release()
{
	popUpTexture.Release();
	trophyTexture.Release();
	buttonBackTexture.Release();
}