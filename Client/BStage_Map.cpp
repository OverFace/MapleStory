#include "stdafx.h"
#include "BStage_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CBstage_Map::CBstage_Map(void)
{
	m_bRender = false;
}

CBstage_Map::~CBstage_Map(void)
{
	Release();
}

void CBstage_Map::Initialize(void)
{
	m_tInfo.fcx = 1799.f;
	m_tInfo.fcy = 781.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CBstage_Map::Update(void)
{
	return 0;
}

void CBstage_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		TransparentBlt(_dc,
			0 + g_fScrollX, 0 + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Boss_Map")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(66, 66, 66));
	}	
}

void CBstage_Map::Release(void)
{
}
