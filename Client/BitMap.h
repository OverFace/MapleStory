#pragma once

class CBitMap
{
public:
	CBitMap(void);
	~CBitMap(void);

private:
	HDC			m_hDC;
	HDC			m_MemDC;
	HBITMAP		m_Bitmap;
	HBITMAP		m_OldBitmap;

public:
	CBitMap*	LoadBmp(const TCHAR* pFileName);
	HDC			GetMemDC(void);

private:
	void		Release(void);
};