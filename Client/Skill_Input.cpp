#include "stdafx.h"
#include "Skill_Input.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CSkill_Input::CSkill_Input(void)
{
	m_eUiType = UI_SKILL;
	m_fx = 0.f;
	m_fy = 0.f;
}

CSkill_Input::CSkill_Input(INFO & _rInfo)
{
	m_eUiType = UI_SKILL;
	m_fx = _rInfo.fx;
	m_fy = _rInfo.fy;
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
}

int CSkill_Input::Update(void)
{
	return 0;
}

void CSkill_Input::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_fx + 10.f) + g_fScrollX, int(m_fy + 90.f) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Skill_Input")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 0));
}

void CSkill_Input::Release(void)
{
}
