#include "stdafx.h"
#include "BitMap.h"

CBitMap::CBitMap(void)
{
}

CBitMap::~CBitMap(void)
{
	Release();
}

CBitMap * CBitMap::LoadBmp(const TCHAR * pFileName)
{
	m_hDC   = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hDC);
	m_Bitmap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (!m_Bitmap)
	{
		MessageBox(g_hWnd, pFileName, L"Image Load Failed", MB_OK);
		return NULL;
	}

	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	ReleaseDC(g_hWnd, m_hDC);

	return this;
}

HDC CBitMap::GetMemDC(void)
{
	return m_MemDC;
}

void CBitMap::Release(void)
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(m_MemDC);
}
