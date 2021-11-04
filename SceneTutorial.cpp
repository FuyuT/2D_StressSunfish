#include "SceneTutorial.h"
CFont FontPopRumCute;
CFont f1;
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
	//fontÇÃçÏê¨
	FontPopRumCute.Create(64, "MSÅ@ÉSÉVÉbÉN");
	f1.Create(64, "MSÅ@ñæí©");
	//FontPopRumCute.Create(64, "	É|ÉvÇÁÇﬁÅôÉLÉÖÅ[Ég");
	
	return true;
}

bool CSceneTutorial::TextLoad()
{
	//ÉeÉLÉXÉgÉtÉ@ÉCÉãÇäJÇ≠
	FILE* fp = fopen("Text\\Tutorial.txt", "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ÉtÉ@ÉCÉãÇÃëSóeó Çí≤Ç◊ÇÈ
	fseek(fp, 0, SEEK_END);  //fpÇÃà íuÇÉtÉ@ÉCÉãÇÃèIí[Ç÷
	long fSize = ftell(fp);  //ÉtÉ@ÉCÉãÇÃì«Ç›èëÇ´à íuÇéÊìæÅAà íuÇ≈óeó ÇãÅÇﬂÇÈ
	fseek(fp, 0, SEEK_SET);  //fpÇÃà íuÇÉtÉ@ÉCÉãÇÃêÊì™Ç÷
	//ÉtÉ@ÉCÉãÇÃóeó ï∂ÇÃÉÅÉÇÉäÇmallocÇ≈ìÆìIÇ…ämï€
	fBuffer = (char*)malloc(fSize + 1);  //èIí[Ç…\0Çä‹ÇﬂÇÈÇΩÇﬂÅA+1
	//ÉoÉbÉtÉ@Ç…ÉtÉ@ÉCÉãÇëSÇƒì«Ç›çûÇﬁ
	fSize = fread(fBuffer, 1, fSize, fp);
	fBuffer[fSize] = '\0';
	//ÉtÉ@ÉCÉãÇï¬Ç∂ÇÈ
	fclose(fp);
	return true;
}

void CSceneTutorial::Initialize()
{
	stg.Initialize();
	pl.Initialize();
	ui.Initialize();
	fBufferOffset = 0;
	mShowDelay = 0;
	
}

void CSceneTutorial::Update()
{
	stg.Update(pl);
	pl.Update();
	ui.Update();
	MessageUpdate();
}

void CSceneTutorial::MessageUpdate()
{
	//ï∂éöóÒÇÃèIí[Ç‹Ç≈ÇÃä‘é¿çs
	if (fBuffer[fBufferOffset] != '\0')
	{
		int nl = strlen(fLineBuffer);
		//â¸çsÇÃèÍçáÅAï\é¶ï∂éöóÒÇâ¸çsÇ∑ÇÈ
		if (fBuffer[fBufferOffset] == '\n')
		{
			//çsä‘Ç™ó~ÇµÇ¢ÇÃÇ≈2âÒâ¸çsÇµÇƒÇ¢ÇÈ
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl++] = '\n';
			fLineBuffer[nl] = '\0';
			fBufferOffset++;
		}
		else
		{
			//àÍíËéûä‘Ç≤Ç∆Ç…àÍï∂éöÇ∏Ç¬fLineBufferÇ…Ç¢ÇÍÇƒÇ¢Ç≠
			mShowDelay++;
			if (mShowDelay >= 5)
			{
				mShowDelay = 0;
				//ëSäpï∂éöîªíË
				if (IsDBCSLeadByte(fBuffer[fBufferOffset]))
				{
					//ëSäpï∂éöÇÃèÍçáÇQÉoÉCÉgï™Ç≈àÍï∂éöÇ…Ç»ÇÈ
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
				//îºäpÇÃèÍçá
				else
				{
					fLineBuffer[nl++] = fBuffer[fBufferOffset++];
					fLineBuffer[nl] = '\0';
				}
			}
		}
	}
	//ï∂éöóÒÇ™èIóπÇµÇΩÇÁÅAENTERÇ≈éüÇÃê‡ñæÇ÷
	else
	{
		if (g_pInput->IsKeyPush(MOFKEY_RETURN))
		{
		}
	}
}

void CSceneTutorial::Render()
{
	stg.Render();
	ui.Render(pl.GetParasite(), pl.GetHungry(), pl.GetBodyTemp(), pl.GetTemperature());
	pl.Render(stg.GetScrollX(), stg.GetScrollY());
	messageWindowImg.Render(MESSAGE_WINDOW_POS_X, MESSAGE_WINDOW_POS_Y);
	//char* test = "É`ÉÖÅ[ÉgÉäÉAÉãÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQ\n\nTutorialÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQ\n\nÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQÅQ";
	//CGraphicsUtilities::RenderString(FIRST_LETTER_POS_X,FIRST_LETTER_POS_Y,"%s",test);
	CGraphicsUtilities::RenderString(400, 750, fLineBuffer);
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
