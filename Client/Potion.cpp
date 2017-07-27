#include "stdafx.h"
#include "Potion.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CPotion::CPotion(void)
{
	m_tItem.m_eType = ITEM_END;
	m_iPotion_XFrame = 0;
}

CPotion::CPotion(TCHAR * pName, eItemType _eType)
{
	m_tItem.m_eType = _eType;
	lstrcpy(m_tItem.m_szName, pName);
	m_iPotion_XFrame = 0;
}

CPotion::~CPotion(void)
{
	Release();
}

void CPotion::SetPotion_Data(int _iStr, int _iDex, int _iInt, int _iLuk, int _iHp, int _iMp, int _iPrice, DWORD _dwOption)
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

void CPotion::Initalize(void)
{
	m_tInfo.fcx = 32.f;
	m_tInfo.fcy = 32.f;
}

int CPotion::Update(void)
{
	return 0;
}

void CPotion::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx), int(m_tInfo.fy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(m_tItem.m_szName)->GetMemDC(),
		int(m_iPotion_XFrame * m_tInfo.fcx), 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CPotion::Release(void)
{
}
