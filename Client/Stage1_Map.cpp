#include "stdafx.h"
#include "Stage1_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage1_Map::CStage1_Map(void)
{
}

CStage1_Map::~CStage1_Map(void)
{
	Release();
}

void CStage1_Map::Initialize(void)
{
	m_tInfo.fcx = 1620.f;
	m_tInfo.fcy = 1025.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CStage1_Map::Update(void)
{
	return 0;
}

void CStage1_Map::Render(HDC _dc)
{
	TransparentBlt(_dc,
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Stage1_Map")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy), RGB(0, 0, 255));
}

void CStage1_Map::Release(void)
{
}
