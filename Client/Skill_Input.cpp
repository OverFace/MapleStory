#include "stdafx.h"
#include "Skill_Input.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"

CSkill_Input::CSkill_Input(void)
{
	m_eUiType = UI_SKILL;
	m_fx = 0.f;
	m_fy = 0.f;
	m_dwTime = 0;
}

CSkill_Input::CSkill_Input(INFO & _rInfo)
{
	m_eUiType = UI_SKILL;
	m_fx = _rInfo.fx;
	m_fy = _rInfo.fy;
	m_dwTime = 0;
	m_tSkill_Info = _rInfo;
}

CSkill_Input::~CSkill_Input(void)
{
	Release();
}

void CSkill_Input::Initialize(void)
{
	//Position Setting
	m_tInfo.fcx = 140.f;
	m_tInfo.fcy = 155.f;
	m_eRenderType = RENDER_UI;

	m_dwTime = GetTickCount();
}

int CSkill_Input::Update(void)
{
	//Position
	m_fx = m_tSkill_Info.fx + g_fScrollX;
	m_fy = m_tSkill_Info.fy + g_fScrollY;

	//Key Setting
	Skill_Key();

	return 0;
}

void CSkill_Input::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_fx + 10.f) - g_fScrollX, int(m_fy + 90.f) - g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Skill_Input")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CSkill_Input::Release(void)
{
}

void CSkill_Input::Skill_Key(void)
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

