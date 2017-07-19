#include "stdafx.h"
#include "Stage2_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage2_Map::CStage2_Map(void)
{
	m_bRender = false;
}

CStage2_Map::~CStage2_Map(void)
{
	Release();
}

void CStage2_Map::Initialize(void)
{
	m_tInfo.fcx = 3056.f;
	m_tInfo.fcy = 1462.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CStage2_Map::Update(void)
{
	return 0;
}

void CStage2_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		BitBlt(_dc,
			int(0 + g_fScrollX), int(0 + g_fScrollY),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stage2_Map")->GetMemDC(),
			0, 0, SRCCOPY);
	}	
}

void CStage2_Map::Release(void)
{
}
