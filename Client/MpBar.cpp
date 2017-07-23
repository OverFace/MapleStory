#include "stdafx.h"
#include "MpBar.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CMpBar::CMpBar(void)
{
	m_eUiType = UI_STATUS;
}

CMpBar::~CMpBar(void)
{
	Release();
}

void CMpBar::Initialize(void)
{
	m_tInfo.fx = 422.f;
	m_tInfo.fy = 688.f;
	m_tInfo.fcx = 141.f;
	m_tInfo.fcy = 14.f;

	m_eRenderType = RENDER_UI;
}

int CMpBar::Update(void)
{
	return 0;
}

void CMpBar::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Mp_Bar")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CMpBar::Release(void)
{
}
