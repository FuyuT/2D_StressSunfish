#include "ResourceFont.h"

bool CResourceFont::Load(LPCMofChar pFileName, LPCMofChar pFontName)
{
	//ファイルを指定して、システムへフォントを追加する
	m_FileName = pFileName;
	//std::string.c_strは文字列をchar*型のポインタを返す
	//TEXTは後続の文字または文字列を対応する Unicode の文字または文字列に変換する
	AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);

	//フォント生成情報にフォントの名前を渡す
	m_FontName = pFontName;
	strcpy(m_FontInfo.lfFaceName, TEXT(m_FontName.c_str()));

	//すでにハンドルがある場合、削除する
	if (m_hResourceFontHandle != NULL)
	{
		DeleteObject(m_hResourceFontHandle);
	}
	//ハンドルを作成　（コンストラクタでフォント生成情報を定義してます）
	m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
	//ハンドルをCFontに渡してフォントを生成（成功したらtrueが返される）
	return CFont::Create((MofFont)m_hResourceFontHandle);
}

bool CResourceFont::Release()
{
	if (m_hResourceFontHandle != NULL)
	{
		DeleteObject(m_hResourceFontHandle);
	}
	RemoveFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
	return TRUE;
}
