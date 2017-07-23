#include "stdafx.h"
#include "Status.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStatus::CStatus(void)
{
	m_eUiType = UI_STATUS;
}

CStatus::~CStatus(void)
{
	Release();
}

void CStatus::Initialize(void)
{
	m_tInfo.fcx = 1024.f;
	m_tInfo.fcy = 720.f;

	m_eRenderType = RENDER_UI;
}

int CStatus::Update(void)
{
	return 0;
}

void CStatus::Render(HDC _dc)
{
	TransparentBlt(_dc,
		g_fScrollX, g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Status")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(237, 34, 206));
}

void CStatus::Release(void)
{
}
