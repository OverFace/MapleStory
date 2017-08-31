#include "stdafx.h"
#include "Glove.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CGlove::CGlove(void)
{
	m_tItem.m_eType = ITEM_GLOVES;
}

CGlove::CGlove(TCHAR * pName)
{
	m_tItem.m_eType = ITEM_GLOVES;
	lstrcpy(m_tItem.m_szName, pName);
}

CGlove::~CGlove(void)
{
	Release();
}

void CGlove::SetGlove_Data(int _iStr, int _iDex, int _iInt, int _iLuk, int _iHp, int _iMp, int _iPrice, int _iSalePrice, DWORD _dwOption)
{
	m_tItem.m_iStr = _iStr;
	m_tItem.m_iDex = _iDex;
	m_tItem.m_iInt = _iInt;
	m_tItem.m_iLuk = _iLuk;
	m_tItem.m_iHp = _iHp;
	m_tItem.m_iMp = _iMp;
	m_tItem.m_iPrice = _iPrice;
	m_tItem.m_iSalePrice = _iSalePrice;
	m_tItem.m_dwOption = _dwOption;
}

void CGlove::Initialize(void)
{
	m_tInfo.fcx = 32.f;
	m_tInfo.fcy = 32.f;

	m_eRenderType = RENDER_WORLDOBJ;
}

int CGlove::Update(void)
{
	CItem::Setting_ItemRect();
	return 0;
}

void CGlove::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx), int(m_tInfo.fy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(m_tItem.m_szName)->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CGlove::Release(void)
{
}
