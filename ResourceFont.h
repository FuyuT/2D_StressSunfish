#pragma once
#include "Mof.h"
class CResourceFont : public CFont
{
private:
	HFONT       m_hResourceFontHandle;  //! �t�@�C������ǂݍ��ރn���h��

	LOGFONT     m_FontInfo;             //! �t�H���g�������

	std::string m_FileName;             //! �o�^����t�@�C����
	std::string m_FontName;             //! �o�^����t�H���g��
public:
	CResourceFont()
		:CFont()
		, m_hResourceFontHandle(NULL)
	{
		//�����̕��킩��Ȃ��̂ň�U�����Ă�
		//m_FontInfo.lfHeight         = 16;
		//m_FontInfo.lfWidth          = 16;
		m_FontInfo.lfEscapement     = 0;
		m_FontInfo.lfOrientation    = 0;
		m_FontInfo.lfWeight         = FW_REGULAR;
		m_FontInfo.lfItalic         = FALSE;
		m_FontInfo.lfUnderline      = FALSE;
		m_FontInfo.lfStrikeOut      = FALSE;
		m_FontInfo.lfCharSet        = DEFAULT_CHARSET;
		m_FontInfo.lfOutPrecision   = OUT_DEFAULT_PRECIS;
		m_FontInfo.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
		m_FontInfo.lfQuality        = PROOF_QUALITY;
		m_FontInfo.lfPitchAndFamily = DEFAULT_PITCH;
	}
	~CResourceFont()
	{

	}
	bool Load(LPCMofChar pFileName,LPCMofChar pFontName);
	bool Release();
};

