#include "stdafx.h"
#include "Stage3_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage3_Map::CStage3_Map(void)
{
	m_bRender = false;
}

CStage3_Map::~CStage3_Map(void)
{
	Release();
}

void CStage3_Map::Initialize(void)
{
	m_tInfo.fcx = 1510.f;
	m_tInfo.fcy = 768.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CStage3_Map::Update(void)
{
	return 0;
}

void CStage3_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		BitBlt(_dc,
			int(0 + g_fScrollX), int(0 + g_fScrollY),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stage3_Map")->GetMemDC(),
			0, 0, SRCCOPY);
	}	
}

void CStage3_Map::Release(void)
{
}
