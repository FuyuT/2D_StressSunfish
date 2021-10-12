#include "SceneGame.h"
#include "Timer.h"
#include "ContinueWindow.h"
#include "ResultWindow.h"
#include "CauseOfDeathWindow.h"
#define	PLAYER_SPEED 10
CTimer tempTimer;
CTimer hungerTimer;
CTimer parasiteTimer;

CPopUpWindowBase* nowPopUpGame = NULL;

CSceneGame::CSceneGame():
scrollValueX(0),
scrollValueY(0)
{
}

CSceneGame::~CSceneGame()
{
}

void CSceneGame::Initialize()
{
	//stressGauge.Load("gauge.png");
	backGroundTexture.Load("SeaTexture.png");
	playerTexture.Load("Player.png");

	stressMeter.Load("sutoresume--ta-.png");

	tempNormal.Load("nicochyan5.png");
	tempHot.Load("nicochyan6.png");
	tempCold.Load("nicochyan4.png");

	tempMeter.Load("temperatureMeter.png");
	tempMeterFrame.Load("temperatureMeterFrame.png");

	hungerGauge.Load("stomach2.png");
	hungerGaugeFrame.Load("stomach.png");

	parasite1.Load("kiseitilyuu.png");
	parasite2.Load("kiseitilyuu2.png");
	parasite3.Load("kiseitilyuu3.png");
	parasite4.Load("kiseitilyuu4.png");
	parasite5.Load("kiseitilyuu5.png");

	//�^�C�}�[
	tempTimer.SetTotalTime(2);
	hungerTimer.SetTotalTime(3);
	parasiteTimer.SetTotalTime(15);

	nowPopUpGame = new CCauseOfDeathWindow;
	nowPopUpGame->Initialize();
}

void CSceneGame::Update()
{
	//��ʑJ��
	if (g_pInput->IsKeyPush(MOFKEY_1))
	{
		endFlg = true;
		nextScene = SCENENO_TITLE;
	}

	//�^�C�}�[
	tempTimer.Update();
	hungerTimer.Update();
	parasiteTimer.Update();
	//�X�N���[��
	CRectangle prec = GetRect();
	//�X�N���[����
	float sw = g_pGraphics->GetTargetWidth();
	float sh = g_pGraphics->GetTargetHeight();
	//�X�e�[�W�̕��l���̋��E��
	float hsw = sw * 0.4f;
	float hsh = sh * 0.4f;
	//�X�e�[�W�S�̂̕� �Ƃ肠�����摜�̕���
	float stgw = backGroundTexture.GetWidth();
	float stgh = backGroundTexture.GetHeight();
	//��
	if (prec.Left - scrollValueX < hsw)
	{
		//���E��hsw���i�񂾒l���AscrolValue�ɓ����
		scrollValueX -= hsw - (prec.Left - scrollValueX);
		if (scrollValueX <= 0)
		{
			scrollValueX = 0;
		}
	}
	//�E
	if (prec.Right - scrollValueX > sw - hsw)
	{
		scrollValueX += (prec.Right - scrollValueX) - (sw - hsw);
		if (scrollValueX >= stgw - sw)
		{
			scrollValueX = stgw - sw;
		}
	}
	//��
	if (prec.Top - scrollValueY < hsh)
	{
		scrollValueY -= hsh - (prec.Top - scrollValueY);
		if (scrollValueY <= 0)
		{
			scrollValueY = 0;
		}
	}
	//��
	if (prec.Bottom - scrollValueY > sh - hsh)
	{
		scrollValueY += (prec.Bottom - scrollValueY) - (sh - hsh);
		if (scrollValueY >= stgh - sh)
		{
			scrollValueY = stgh - sh;
		}
	}
	
	//�ړ�
	//�������i���Ȃ��Ɖ�������̂�
	moveSpeed.x = 0; moveSpeed.y = 0;
	if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		moveSpeed.x += PLAYER_SPEED;
		distancePlayer += 10.0f;
	}
	else if(g_pInput->IsKeyHold(MOFKEY_A))
	{
		moveSpeed.x -= PLAYER_SPEED;
	}
	if (g_pInput->IsKeyHold(MOFKEY_W))
	{
		moveSpeed.y -= PLAYER_SPEED;
	}
	else if (g_pInput->IsKeyHold(MOFKEY_S))
	{
		moveSpeed.y += PLAYER_SPEED;
	}
	//�ړ�����
	//���E
	if (prec.Left < 0)
	{
		playerX = 0;
	}
	else if (prec.Right > stgw)
	{
		playerX = stgw - playerTexture.GetWidth();
	}
	//�㉺

	
	//���ۂɈړ�
	playerX += moveSpeed.x;
	playerY += moveSpeed.y;


	//else if (prec.Right > backGroundTexture.GetWidth())
	//{
	//	playerX = stgw - playerTexture.GetWidth();
	//}



	//�̉��ω�
	//�̉����~
	if (playerY >= backGroundTexture.GetHeight() - 330)
	{		
		//�^�C�}�[�Z�b�g
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp > -30)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
			}
			tempTimer.SetTotalTime(1);
		}
	}
	//�̉��㏸
	else if (playerY <= backGroundTexture.GetHeight() - 1200)
	{	
		//�^�C�}�[�Z�b�g
		tempTimer.StartTimer();
		if (tempTimer.GetNowtime() <= 0)
		{
			if (bodyTemp < 50)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
			}
			tempTimer.SetTotalTime(1);
		}
	}
	//�̉������̒l�ɖ߂�
	else
	{
		if (bodyTemp > 10)
		{	
			//�^�C�}�[�Z�b�g
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp -= 1;
				tempRegion += 4.1;
				tempTimer.SetTotalTime(2);
			}
		}
		else if (bodyTemp < 10)
		{	
			//�^�C�}�[�Z�b�g
			tempTimer.StartTimer();
			if (tempTimer.GetNowtime() <= 0)
			{
				bodyTemp += 1;
				tempRegion -= 4.1;
				tempTimer.SetTotalTime(2);
			}
		}
	}

	//�񐶒�
	if (parasiteFlg < 5)
	{
		//�^�C�}�[�Z�b�g
		parasiteTimer.StartTimer();
		if (parasiteTimer.GetNowtime() <= 0)
		{
			parasiteFlg += 1;
			parasiteTimer.SetTotalTime(15);
		}

	}

	//�󕠃Q�[�W
	//�^�C�}�[�Z�b�g
	hungerTimer.StartTimer();
	if (hungerTimer.GetNowtime() <= 0)
	{
		if (hungerRegion < 160)
		{
			hungerRegion += 3;
		}		
		hungerTimer.SetTotalTime(3);
	}

	//�Ƃ肠����F1�Ń|�b�v�A�b�v���o��悤��
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		PopUpController();
	}
}

void CSceneGame::Render()
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	backGroundTexture.Render(-scrollValueX, -scrollValueY);
	playerTexture.Render(playerX - scrollValueX, playerY - scrollValueY);
	//CGraphicsUtilities::RenderString(100, 300, "game���");
	CGraphicsUtilities::RenderString(10, 10, "%d m",distancePlayer);

	stressMeter.Render(1600, 0);
	
	//�̉�UI�`��
	if (bodyTemp >=40)
	{
		tempHot.Render(1600, 0);
	}
	else if (bodyTemp <= -20)
	{
		tempCold.Render(1600, 0);
	}
	else
	{
		tempNormal.Render(1600, 0);
	}

	//���x�vUI�`��
	tempMeterFrame.Render(1550,200);
	CRectangle rec1(0, tempRegion, 500, 500);
	tempMeter.Render(1550, 200 + tempRegion,rec1);

	//�񐶒�UI�̕`��
	switch (parasiteFlg)
	{
	case 1:
		parasite1.Render(1600, 0);
		break;
	case 2:
		parasite2.Render(1600, 0);
		break;
	case 3:
		parasite3.Render(1600, 0);
		break;
	case 4:
		parasite4.Render(1600, 0);
		break;
	case 5:
		parasite5.Render(1600, 0);
		break;
	}

	//�󕠃Q�[�WUI�`��
	CRectangle rec2(0, 0, 330, 200);
	hungerGaugeFrame.Render(1400, 0,rec2);
	CRectangle rec3(0,hungerRegion, 330, 200);
	hungerGauge.Render(1400,hungerRegion,rec3);

	//�|�b�v�A�b�v�`��
	if (popUpFlg)
	{
		nowPopUpGame->Render();
	}

	//�f�o�b�O�p
	CGraphicsUtilities::RenderString(10, 50,MOF_COLOR_BLACK, "���x  %d", bodyTemp);
	tempTimer.Render(10, 70);
	hungerTimer.Render(10, 90);
	parasiteTimer.Render(10, 110);
}

void CSceneGame::Release()
{
	backGroundTexture.Release();
	playerTexture.Release();

	stressMeter.Release();

	tempNormal.Release();
	tempHot.Release();
	tempCold.Release();

	tempMeter.Release();
	tempMeterFrame.Release();

	hungerGauge.Release();
	hungerGaugeFrame.Release();

	parasite1.Release();
	parasite2.Release();
	parasite3.Release();
	parasite4.Release();
	parasite5.Release();

	nowPopUpGame->Release();
	if (nowPopUpGame)
	{
		delete nowPopUpGame;
		nowPopUpGame = NULL;
	}
}

void CSceneGame::PopUpController()
{
	nowPopUpGame->Update();
	if (nowPopUpGame->IsEnd())
	{
		//���̃|�b�v�A�b�v�̎擾
		short nextPopUp = nowPopUpGame->GetNextPopUp();
		//�Â��|�b�v�A�b�v�̏���
		delete nowPopUpGame;
		//���̃|�b�v�A�b�v�ԍ��ɉ����ă|�b�v�A�b�v��������
		switch (nextPopUp)
		{
		case POPUPNO_CAUSEOFDEATH:
			nowPopUpGame = new CCauseOfDeathWindow;
			break;
		case POPUPNO_RESULT:
			nowPopUpGame = new CResultWindow;
			break;
		case POPUPNO_CONTINUE:
			nowPopUpGame = new CContinueWindow;
			break;
		case NULL:
			nowPopUpGame = new CCauseOfDeathWindow;
			popUpFlg = false;
		}
		nowPopUpGame->Initialize();
	}
}