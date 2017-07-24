#include "stdafx.h"
#include "Inven.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"

CInven::CInven(void)
{
	m_eUiType = UI_INVEN;
	m_dwTime = 0;
}

CInven::~CInven(void)
{
	Release();
}

void CInven::Initialize(void)
{
	m_tInfo.fcx = 172.f;
	m_tInfo.fcy = 335.f;
	m_eRenderType = RENDER_UI;

	m_dwTime = GetTickCount();
}

int CInven::Update(void)
{
	//Position
	m_tInfo.fx = 0.f + g_fScrollX;
	m_tInfo.fy = 0.f + g_fScrollY;

	//Key Setting
	Inven_Key();

	return 0;
}

void CInven::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Inventory")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CInven::Release(void)
{
}

void CInven::Inven_Key(void)
{
	static bool bIsPress_Inven = false;
	if (GETS(CKeyMgr)->GetKeyDown('I') && bIsPress_Inven == false)
	{
		if (m_bVisible == true)
			m_bVisible = false;
		else
			m_bVisible = true;

		bIsPress_Inven = true;
	}

	if (m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if (bIsPress_Inven == true)
			bIsPress_Inven = false;
	}
}
