#include "stdafx.h"
#include "Skill.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CSkill_UI::CSkill_UI(void)
{
	m_eUiType = UI_SKILL;
}

CSkill_UI::~CSkill_UI(void)
{
	Release();
}

void CSkill_UI::Initialize(void)
{
	m_tInfo.fx = 410.f;
	m_tInfo.fy = 0.f;
	m_tInfo.fcx = 174.f;
	m_tInfo.fcy = 300.f;

	m_eRenderType = RENDER_UI;
}

int CSkill_UI::Update(void)
{
	return 0;
}

void CSkill_UI::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Skill")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CSkill_UI::Release(void)
{
}
