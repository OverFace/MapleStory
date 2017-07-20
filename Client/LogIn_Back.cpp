#include "stdafx.h"
#include "LogIn_Back.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CLogin_Back::CLogin_Back(void)
{
}

CLogin_Back::~CLogin_Back(void)
{
	Release();
}

void CLogin_Back::Initialize(void)
{
	m_tInfo.fcx = 1024.f;
	m_tInfo.fcy = 720.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CLogin_Back::Update(void)
{
	return 0;
}

void CLogin_Back::Render(HDC _dc)
{
	TransparentBlt(_dc,
		g_fScrollX, g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Login")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CLogin_Back::Release(void)
{
}
