#include "stdafx.h"
#include "Equip.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CEquip::CEquip(void)
{
	m_eUiType = UI_EQUIP;
}

CEquip::~CEquip(void)
{
	Release();
}

void CEquip::Initialize(void)
{
	m_tInfo.fx  = 173.f;
	m_tInfo.fy  = 0.f;
	m_tInfo.fcx = 237.f;
	m_tInfo.fcy = 332.f;

	m_eRenderType = RENDER_UI;
}

int CEquip::Update(void)
{
	return 0;
}

void CEquip::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Equipment")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CEquip::Release(void)
{
}
