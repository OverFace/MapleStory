#include "stdafx.h"
#include "Stat.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStat::CStat(void)
{
	m_eUiType = UI_STAT;
}

CStat::~CStat(void)
{
	Release();
}

void CStat::Initialize(void)
{
	m_tInfo.fx = 509.f;
	m_tInfo.fy = 300.f;
	m_tInfo.fcx = 212.f;
	m_tInfo.fcy = 373.f;

	m_eRenderType = RENDER_UI;
}

int CStat::Update(void)
{
	return 0;
}

void CStat::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stat")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CStat::Release(void)
{
}
