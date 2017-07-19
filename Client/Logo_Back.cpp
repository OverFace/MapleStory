#include "stdafx.h"
#include "Logo_Back.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CLogo_Back::CLogo_Back(void)
{
}

CLogo_Back::~CLogo_Back(void)
{
	Release();
}

void CLogo_Back::Initialize(void)
{
	m_tInfo.fcx = 1024;
	m_tInfo.fcy = 720;

	m_eRenderType = RENDER_BACKGROUND;	
}

int CLogo_Back::Update(void)
{
	return 0;
}

void CLogo_Back::Render(HDC _dc)
{
	TransparentBlt(_dc,
		0,
		0,
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Logo")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),
		RGB(255, 255, 255));
}

void CLogo_Back::Release(void)
{
}
