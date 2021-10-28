#include "SceneTutorial.h"
CFont FontPopRumCute;

CSceneTutorial::CSceneTutorial()
{
}

CSceneTutorial::~CSceneTutorial()
{
}

bool CSceneTutorial::Load()
{
	if (!stg.Load())return false;
	if (!ui.Load())return false;
	if (!pl.Load())return false;
	if (!obs.Load())return false;
	if (!messageWindowImg.Load("MessageWindow.png"))return false;
	if (!TextLoad())return false;
	//font‚Ìì¬
	//FontPopRumCute.Create(64, "MS –¾’©");
	FontPopRumCute.Create(64, "	ƒ|ƒv‚ç‚Ş™ƒLƒ…[ƒg");

	return true;
}

bool CSceneTutorial::TextLoad()
{
	//ƒeƒLƒXƒgƒtƒ@ƒCƒ‹‚ğŠJ‚­
	FILE* fp = fopen("Text\\Tutorial.txt", "rt");
	if (fp == NULL)return false;
	//ƒtƒ@ƒCƒ‹‚Ì‘S—e—Ê‚ğ’²‚×‚é
	fseek(fp, 0, SEEK_END);  //fp‚ÌˆÊ’u‚ğƒtƒ@ƒCƒ‹‚ÌI’[‚Ö
	long fSize = ftell(fp);  //ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‘‚«ˆÊ’u‚ğæ“¾AˆÊ’u‚Å—e—Ê‚ğ‹‚ß‚é
	fseek(fp, 0, SEEK_SET);  //fp‚ÌˆÊ’u‚ğƒtƒ@ƒCƒ‹‚Ìæ“ª‚Ö
	//ƒtƒ@ƒCƒ‹‚Ì—e—Ê•¶‚Ìƒƒ‚ƒŠ‚ğmalloc‚Å“®“I‚ÉŠm•Û
	fBuffer = NULL;
	fBuffer = (char*)malloc(fSize + 1);  //I’[‚É\0‚ğŠÜ‚ß‚é‚½‚ßA+1
	//ƒoƒbƒtƒ@‚Éƒtƒ@ƒCƒ‹‚ğ‘S‚Ä“Ç‚İ‚Ş
	fSize = fread(fBuffer, 1, fSize, fp);
	fBuffer[fSize] = '\0';
	//ƒtƒ@ƒCƒ‹‚ğ•Â‚¶‚é
	fclose(fp);
	return true;
}

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
	pl.Update();
	ui.Update();
}

void CSceneTutorial::Render()
{
	stg.Render();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetBodyTemp(), pl.GetTemperature());
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	//char* test = "ƒ`ƒ…[ƒgƒŠƒAƒ‹QQQQQQQQQQQQQQQQQQQQQQQ\n\nTutorialQQQQQQQQQQQQQQQQQQQQQQ\n\nQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ";
	//CGraphicsUtilities::RenderString(FIRST_LETTER_POS_X,FIRST_LETTER_POS_Y,"%s",test);
	FontPopRumCute.RenderString(100, 100,"‚Ä‚·‚Æ");
	Mof::LPString a = FontPopRumCute.GetName();
}

void CSceneTutorial::RenderDebug()
{
	pl.RenderDebug(stg.GetScrollX(), stg.GetScrollY());
}

void CSceneTutorial::Release()
{
	stg.Release();
	ui.Release();
	pl.Release();
	messageWindowImg.Release();
	free(fBuffer);
}
