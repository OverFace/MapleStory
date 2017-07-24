#include "stdafx.h"
#include "Skill.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

CSkill_UI::CSkill_UI(void)
{
	m_eUiType = UI_SKILL;
	m_dwTime = 0;
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

	m_dwTime = GetTickCount();
}

int CSkill_UI::Update(void)
{
	//Position
	m_tInfo.fx = 410.f + g_fScrollX;
	m_tInfo.fy = 0.f + g_fScrollY;

	//Key Setting
	Skill_Key();

	return 0;
}

void CSkill_UI::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Skill")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CSkill_UI::Release(void)
{
}

void CSkill_UI::Skill_Key(void)
{
	static bool bIsPress_Skill = false;
	if (GETS(CKeyMgr)->GetKeyDown('K') && bIsPress_Skill == false)
	{
		if (m_bVisible == true)
			m_bVisible = false;
		else
			m_bVisible = true;

		bIsPress_Skill = true;
	}

	if (m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if (bIsPress_Skill == true)
			bIsPress_Skill = false;
	}
}

