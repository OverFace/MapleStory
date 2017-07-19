#include "stdafx.h"
#include "Stage1_Back.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage1_Back::CStage1_Back(void)
{
}

CStage1_Back::~CStage1_Back(void)
{
	Release();
}

void CStage1_Back::Initialize(void)
{
	m_tInfo.fcx = 1620.f;
	m_tInfo.fcy = 1012.f;

	m_eRenderType = RENDER_BACKGROUND;
}

int CStage1_Back::Update(void)
{
	return 0;
}

void CStage1_Back::Render(HDC _dc)
{
	TransparentBlt(_dc,
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Stage1_Back")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy), RGB(0, 0, 255));
}

void CStage1_Back::Release(void)
{
}
