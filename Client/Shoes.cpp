#include "stdafx.h"
#include "Shoes.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CShoes::CShoes(void)
{
	m_tItem.m_eType = ITEM_SHOES;
}

CShoes::CShoes(TCHAR * pName)
{
	m_tItem.m_eType = ITEM_SHOES;
	lstrcpy(m_tItem.m_szName, pName);
}

CShoes::~CShoes(void)
{
	Release();
}

void CShoes::SetShoes_Data(int _iStr, int _iDex, int _iInt, int _iLuk, int _iHp, int _iMp, int _iPrice, DWORD _dwOption)
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

void CShoes::Initialize(void)
{
	m_tInfo.fcx = 32.f;
	m_tInfo.fcy = 32.f;
}

int CShoes::Update(void)
{
	return 0;
}

void CShoes::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx), int(m_tInfo.fy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(m_tItem.m_szName)->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CShoes::Release(void)
{
}
