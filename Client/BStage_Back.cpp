#include "stdafx.h"
#include "BStage_Back.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CBstage_Back::CBstage_Back(void)
{
	m_bRender = false;
}

CBstage_Back::~CBstage_Back(void)
{
	Release();
}

void CBstage_Back::Initialize(void)
{
	m_tInfo.fcx = 1980.f;
	m_tInfo.fcy = 1050.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CBstage_Back::Update(void)
{
	return 0;
}

void CBstage_Back::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		TransparentBlt(_dc,
			0 + g_fScrollX, 0 + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Boss_Back")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 255));
	}	
}

void CBstage_Back::Release(void)
{
}
