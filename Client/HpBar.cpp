#include "stdafx.h"
#include "HpBar.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CHpBar::CHpBar(void)
{
	m_eUiType = UI_STATUS;
}

CHpBar::~CHpBar(void)
{
	Release();
}

void CHpBar::Initialize(void)
{
	m_tInfo.fx = 252.f;
	m_tInfo.fy = 688.f;
	m_tInfo.fcx = 141.f;
	m_tInfo.fcy = 14.f;

	m_eRenderType = RENDER_UI;
}

int CHpBar::Update(void)
{
	m_tInfo.fx = 252.f + g_fScrollX;
	m_tInfo.fy = 688.f + g_fScrollY;

	return 0;
}

void CHpBar::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Hp_Bar")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CHpBar::Release(void)
{
}
