#include "stdafx.h"
#include "Messo.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CMesso::CMesso(void)
{
	m_tItem.m_eType = ITEM_MESSO;
	m_iMesso_XIndex = 0;
	m_iMesso_YIndex = 0;
}

CMesso::CMesso(TCHAR * pName)
{
	m_tItem.m_eType = ITEM_MESSO;
	lstrcpy(m_tItem.m_szName, pName);
	m_iMesso_XIndex = 0;
	m_iMesso_YIndex = 0;
}

CMesso::~CMesso(void)
{
	Release();
}

void CMesso::SetMesso_Data(int _iStr, int _iDex, int _iInt, int _iLuk, int _iHp, int _iMp, int _iPrice, DWORD _dwOption)
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

void CMesso::Initalize(void)
{
	m_tInfo.fcx = 32.f;
	m_tInfo.fcy = 32.f;
}

int CMesso::Update(void)
{
	return 0;
}

void CMesso::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx), int(m_tInfo.fy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(m_tItem.m_szName)->GetMemDC(),
		int(m_iMesso_XIndex * m_tInfo.fcx), int(m_iMesso_YIndex * m_tInfo.fcy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CMesso::Release(void)
{
}
