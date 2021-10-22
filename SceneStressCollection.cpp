#include "SceneStressCollection.h"
#include "CheckCauseOfDeathWindow.h"

CPopUpWindowBase* nowPopUpStress = NULL;

CSceneStressCollection::CSceneStressCollection()
{

}
CSceneStressCollection::~CSceneStressCollection()
{
	Release();
}
void CSceneStressCollection::Initialize()
{
	backGroundTex.Load("Title.png");

	//�����e�N�X�`���ǂݍ���
	//�t���O���I���Ȃ�Ή�����e�N�X�`���A�t���O���I�t�Ȃ疢�擾�e�N�X�`����ǂݍ��ށB
	if(increasedBodyTemperatureFlg)
		increasedBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		increasedBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(lowerBodyTemperatureFlg)
		lowerBodyTemperatureIconTexture.Load("siin_aikon.png");
	else
		lowerBodyTemperatureIconTexture.Load("siin_aikon_Enpty.png");

	if(starvationIconFlg)
		starvationIconTexture.Load("siin_aikon.png");
	else
		starvationIconTexture.Load("siin_aikon_Enpty.png");

	if(cloggedThroatIconFlg)
		cloggedThroatIconTexture.Load("siin_aikon.png");
	else
		cloggedThroatIconTexture.Load("siin_aikon_Enpty.png");

	if(obesityIconFlg)
		obesityIconTexture.Load("siin_aikon.png");
	else
		obesityIconTexture.Load("siin_aikon_Enpty.png");

	if(impactFlg)
		impactIconTexture.Load("siin_aikon.png");
	else
		impactIconTexture.Load("siin_aikon_Enpty.png");

	if(parasiteFlg)
		parasiteIconTexture.Load("siin_aikon.png");
	else
		parasiteIconTexture.Load("siin_aikon_Enpty.png");
	if(jumpFlg)
		jumpIconTexture.Load("siin_aikon.png");
	else
		jumpIconTexture.Load("siin_aikon_Enpty.png");

	if(bubbleFlg)
		bubbleIconTexture.Load("siin_aikon.png");
	else
		bubbleIconTexture.Load("siin_aikon_Enpty.png");

	if(turtleFlg)
		turtleIconTexture.Load("siin_aikon.png");
	else
		turtleIconTexture.Load("siin_aikon_Enpty.png");

	if(waterFlowFlg)
		waterFlowIconTexture.Load("siin_aikon.png");
	else
		waterFlowIconTexture.Load("siin_aikon_Enpty.png");

	menuButtonTexture.Load("ButtonMenu.png");
	popUpFlg = false;
	nowPopUpStress = new CCheckCauseOfDeathWindow;
	nowPopUpStress->Initialize();
}
void CSceneStressCollection::Update()
{
	float mousePosX, mousePosY;
	g_pInput->GetMousePos(mousePosX, mousePosY);
	if (g_pInput->IsMouseKeyPush(MOFMOUSE_LBUTTON) && GetRect().CollisionPoint(mousePosX, mousePosY) && !popUpFlg)
	{
		endFlg = true;
		nextScene = SCENENO_GAMEMENU;
		CSceneStressCollection::Release();
	}

	//�Ƃ肠����F1�Ń|�b�v�A�b�v���o��悤��
	if (g_pInput->IsKeyPush(MOFKEY_F1) && !popUpFlg)
	{
		popUpFlg = true;
	}
	if (popUpFlg)
	{
		nowPopUpStress->Initialize();
		nowPopUpStress->Update();
		if (nowPopUpStress->IsEnd())
		{
			popUpFlg = false;
		}
	}
}
void CSceneStressCollection::Render()
{
	backGroundTex.Render(0, 0);
	CGraphicsUtilities::RenderString(100, 300, "�X�g���X�W���");
	menuButtonTexture.Render(menuButtonPosX, menuButtonPosY);
	if (popUpFlg)
	{
		nowPopUpStress->Render();
	}
}
void CSceneStressCollection::Release()
{
	backGroundTex.Release();
	increasedBodyTemperatureIconTexture.Release();
	lowerBodyTemperatureIconTexture.Release();
	starvationIconTexture.Release();
	cloggedThroatIconTexture.Release();
	obesityIconTexture.Release();
	impactIconTexture.Release();
	parasiteIconTexture.Release();
	jumpIconTexture.Release();
	bubbleIconTexture.Release();
	turtleIconTexture.Release();
	waterFlowIconTexture.Release();

	menuButtonTexture.Release();
	nowPopUpStress->Release();
}