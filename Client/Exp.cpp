#include "stdafx.h"
#include "Exp.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CExp::CExp(void)
{
	m_tItem.m_eType = ITEM_EXP;
}

CExp::CExp(TCHAR * pName)
{
	m_tItem.m_eType = ITEM_EXP;
	lstrcpy(m_tItem.m_szName, pName);
}

CExp::~CExp(void)
{
	Release();
}

void CExp::SetExp_Data(int _iStr, int _iDex, int _iInt, int _iLuk, int _iHp, int _iMp, int _iPrice, DWORD _dwOption)
{
	m_tItem.m_iStr = _iStr;
	m_tItem.m_iDex = _iDex;
	m_tItem.m_iInt = _iInt;
	m_tItem.m_iLuk = _iLuk;
	m_tItem.m_iHp = _iHp;
	m_tItem.m_iMp = _iMp;
	m_tItem.m_iPrice = _iPrice;
	m_tItem.m_dwOption = _dwOption;
}

void CExp::Initalize(void)
{
	m_tInfo.fcx = 32.f;
	m_tInfo.fcy = 32.f;
}

int CExp::Update(void)
{
	return 0;
}

void CExp::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx), int(m_tInfo.fy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(m_tItem.m_szName)->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CExp::Release(void)
{
}

