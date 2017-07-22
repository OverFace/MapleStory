#include "stdafx.h"
#include "ExpBar.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CExpBar::CExpBar(void)
{
	m_eUiType = UI_STATUS;
}

CExpBar::~CExpBar(void)
{
	Release();
}

void CExpBar::Initialize(void)
{
	m_tInfo.fx = 252.f;
	m_tInfo.fy = 705.f;
	m_tInfo.fcx = 311.f;
	m_tInfo.fcy = 12.f;

	m_eRenderType = RENDER_UI;
}

int CExpBar::Update(void)
{
	return 0;
}

void CExpBar::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Exp_Bar")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CExpBar::Release(void)
{
}
