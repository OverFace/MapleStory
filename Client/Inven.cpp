#include "stdafx.h"
#include "Inven.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CInven::CInven(void)
{
	m_eUiType = UI_INVEN;
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
}

int CInven::Update(void)
{
	return 0;
}

void CInven::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			g_fScrollX, g_fScrollY,
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
