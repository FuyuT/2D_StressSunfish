#include "ResourceFont.h"

bool CResourceFont::Load(LPCMofChar pFileName, LPCMofChar pFontName)
{
	//�t�@�C�����w�肵�āA�V�X�e���փt�H���g��ǉ�����
	m_FileName = pFileName;
	//std::string.c_str�͕������char*�^�̃|�C���^��Ԃ�
	//TEXT�͌㑱�̕����܂��͕������Ή����� Unicode �̕����܂��͕�����ɕϊ�����
	AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);

	//�t�H���g�������Ƀt�H���g�̖��O��n��
	m_FontName = pFontName;
	strcpy(m_FontInfo.lfFaceName, TEXT(m_FontName.c_str()));

	//���łɃn���h��������ꍇ�A�폜����
	if (m_hResourceFontHandle != NULL)
	{
		DeleteObject(m_hResourceFontHandle);
	}
	//�n���h�����쐬�@�i�R���X�g���N�^�Ńt�H���g���������`���Ă܂��j
	m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
	//�n���h����CFont�ɓn���ăt�H���g�𐶐��i����������true���Ԃ����j
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
