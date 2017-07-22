#include "stdafx.h"
#include "Store.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStore::CStore(void)
{
	m_eUiType = UI_STORE;
}

CStore::~CStore(void)
{
	Release();
}

void CStore::Initialize(void)
{
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 300.f;
	m_tInfo.fcx = 508.f;
	m_tInfo.fcy = 505.f;

	m_eRenderType = RENDER_UI;
}

int CStore::Update(void)
{
	return 0;
}

void CStore::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Store")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CStore::Release(void)
{
}
