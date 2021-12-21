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
	//�t�H���g
	font.Load(fontAdd, fontName);
	font.Create(156, fontName);

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
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "�싉");
		//�������`��
		font.RenderStringScale(415,675, 0.6f ,MOF_XRGB(0, 0, 0), "�삯�o���̍ŏ��ɂ��炦��g���t�B�[");
		font.RenderStringScale(615, 775, 0.6f, MOF_XRGB(0, 0, 0), "����݂̋������j������");
	}
	if (buttonResult == TROPHY_WATERFALL)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "�ꋉ");
		//�������`��
		font.RenderStringScale(545, 675, 0.6f, MOF_XRGB(0, 0, 0), "�܂��܂����l�O�̃g���t�B�[");
		font.RenderStringScale(615, 775, 0.6f, MOF_XRGB(0, 0, 0), "����݂̋������j������");
	}
	if (buttonResult == TROPHY_LAKE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "�΋�");
		//�������`��
				//�������`��
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "���������撣���Ă���g���t�B�[");
		font.RenderStringScale(610, 775, 0.6f, MOF_XRGB(0, 0, 0), "�Ε��݂̋����j������");
	}
	if (buttonResult == TROPHY_DAM)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(750, 225, MOF_XRGB(0, 0, 0), "�_����");
		//�������`��
		font.RenderStringScale(550, 675, 0.6f, MOF_XRGB(0, 0, 0), "��ʐl���x���̃g���t�B�[");
		font.RenderStringScale(550, 775, 0.6f, MOF_XRGB(0, 0, 0), "�_�����݂̋������j������");
	}
	if (buttonResult == TROPHY_SEWER)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(700, 220, MOF_XRGB(0, 0, 0), "��������");
		//�������`��
		font.RenderStringScale(640, 675, 0.6f, MOF_XRGB(0, 0, 0), "��l�O�̃g���t�B�[");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "���������݂̋������j������");
	}
	if (buttonResult == TROPHY_INDIANOCEAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(630, 225, MOF_XRGB(0, 0, 0), "�C���h�m��");
		//�������`��
		font.RenderStringScale(340, 675, 0.6f, MOF_XRGB(0, 0, 0), "������Ƃ�肱�݂�����S�l�̃g���t�B�[");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "�C���h�m���݂̋������j������");
	}
	if (buttonResult == TROPHY_AMAZONROVER)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(590, 250, MOF_XRGB(0, 0, 0), "�A�}�]���싉");
		//�������`��
		font.RenderStringScale(340, 675, 0.6f, MOF_XRGB(0, 0, 0), "������肱��ł���Q�[�}�[�̃g���t�B�[");
		font.RenderStringScale(500, 775, 0.6f, MOF_XRGB(0, 0, 0), "�A�}�]������݂̋������j������");
	}
	if (buttonResult == TROPHY_OCEAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(800, 225, MOF_XRGB(0, 0, 0), "�C��");
		//�������`��
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "��肱��ł���B�l�̃g���t�B�[");
		font.RenderStringScale(600, 775, 0.6f, MOF_XRGB(0, 0, 0), "�C���݂̋������j������");
	}
	if (buttonResult == TROPHY_SEAOFJAPAN)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "���{�C��");
		//�������`��
		font.RenderStringScale(465, 675, 0.6f, MOF_XRGB(0, 0, 0), "��肱�݉߂��Ȓ��l�̃g���t�B�[");
		font.RenderStringScale(525, 775, 0.6f, MOF_XRGB(0, 0, 0), "���{�C���݂̋������j������");
	}
	if (buttonResult == TROPHY_AROUNDTHEGLOBE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(635, 225, MOF_XRGB(0, 0, 0), "�n�������");
		//�������`��
		font.RenderStringScale(340, 675, 0.55, MOF_XRGB(0, 0, 0), "���͂�V�˂̍˂��������킹��l�̃g���t�B�[");
		font.RenderStringScale(560, 775, 0.55f, MOF_XRGB(0, 0, 0), "�n��������݂̋������j������");
	}
	if (buttonResult == TROPHY_ZEROMOTIVATION)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString( 590, 225, MOF_XRGB(0, 0, 0), "���C�[����");
		//�������`��
		font.RenderStringScale(445, 675, 0.6f, MOF_XRGB(0, 0, 0), "���C�������Ȃ��l�̃g���t�B�[");
		font.RenderStringScale(630, 775, 0.6f, MOF_XRGB(0, 0, 0), "...���C����܂��H");
	}
	if (buttonResult == TROPHY_MOUNTFJI)
	{
		scaleController.ScaleRender(&trophyTexture,trophyTexturePosX, trophyTexturePosY - 130,1.7f);
		//trophyTexture.RenderScale(trophyTexturePosX, trophyTexturePosY -75,1.5f);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "�x�m�R��");
		//�������`��
		font.RenderStringScale(360, 675, 0.55f, MOF_XRGB(0, 0, 0), "�x�m�R���݂̋������j�������ʂȃg���t�B�[");
		font.RenderStringScale(520, 775, 0.55f, MOF_XRGB(0, 0, 0), "����ŕx�m�R��o�R���������R���I");
	}
	if (buttonResult == TROPHY_OSAKAMARATHON)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(535, 225, MOF_XRGB(0, 0, 0), "���}���\����");
		//�������`��
		font.RenderStringScale(330, 675, 0.5f, MOF_XRGB(0, 0, 0), "���}���\�����݂̋������j�������ʂȃg���t�B�[");
		font.RenderStringScale(510, 775, 0.5f, MOF_XRGB(0, 0, 0), "���͗���Ŋ�����ڎw���Ă݂悤�I");
	}
	if (buttonResult == TROPHY_BIWALAKE)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "���i�΋�");
		//�������`��
		font.RenderStringScale(355, 675, 0.55f, MOF_XRGB(0, 0, 0), "���i�Ε��݂̋������j�������ʂȃg���t�B�[");
		font.RenderStringScale(530, 775, 0.55f, MOF_XRGB(0, 0, 0), "�ؔ��i�΂��ĈӊO�Ɖ����炵��");
	}
	if (buttonResult == TROPHY_JACKPOD)
	{
		trophyTexture.Render(trophyTexturePosX, trophyTexturePosY);
		font.RenderString(500, 225, MOF_XRGB(0, 0, 0), "�W���b�N�|�b�g��");
		//�������`��
		font.RenderStringScale(640, 675, 0.6f, MOF_XRGB(0, 0, 0), "�W���b�N�|�b�g�I�I");
		font.RenderStringScale(610, 775, 0.6f, MOF_XRGB(0, 0, 0), "777�I�I�哖����I�I");
	}
	if (buttonResult == TROPHY_TALENTEDDEMON)
	{
		trophyTexture.Render(trophyTexturePosX+30, trophyTexturePosY);
		font.RenderString(690, 225, MOF_XRGB(0, 0, 0), "�˔\����");
		//�������`��
		font.RenderStringScale(440, 675, 0.6f, MOF_XRGB(0, 0, 0), "�˔\�����݂̋������j�������ʂȏ�");
		font.RenderStringScale(540, 775, 0.6f, MOF_XRGB(0, 0, 0), "������肱�݂����ĂĂ�΂�");
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
