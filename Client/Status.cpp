#include "stdafx.h"
#include "Status.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "ObjMgr.h"

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
	m_tInfo.fx = 0.f;
	m_tInfo.fy = 0.f;
	m_tInfo.fcx = 1024.f;
	m_tInfo.fcy = 720.f;

	m_eRenderType = RENDER_UI;
}

int CStatus::Update(void)
{
	m_tInfo.fx = g_fScrollX;
	m_tInfo.fy = g_fScrollY;

	return 0;
}

void CStatus::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Status")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(237, 34, 206));
}

void CStatus::Release(void)
{
}
