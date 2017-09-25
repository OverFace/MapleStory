#include "stdafx.h"
#include "Skill_Icon.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"

//UI
#include "Skill.h"


CSkill_Icon::CSkill_Icon(void)
{
	ZeroMemory(&m_tSkill, sizeof(SKILL));
	m_iSkill_Number = 0;
	m_iSkill_QuickSlot_Number = 0;
	m_bSkill_Icon_Check = false;
}

CSkill_Icon::~CSkill_Icon(void)
{
	Release();
}

void CSkill_Icon::Initialize(void)
{
}

int CSkill_Icon::Update(void)
{
	m_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) - m_tInfo.fcx / 2);
	m_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) + m_tInfo.fcx / 2);
	m_Rect.top = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) - m_tInfo.fcy / 2);
	m_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) + m_tInfo.fcy / 2);

	return 0;
}

void CSkill_Icon::Render(HDC _dc)
{
	//Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	
	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);
	
	//Level Render
	TCHAR szLevel[100] = { 0 };	
	_stprintf_s(szLevel, _countof(szLevel), L"%d", m_tSkill.m_iSkill_Level);
	
	SetBkMode(_dc, TRANSPARENT);
	
	TextOut(_dc, int(m_tInfo.fx + 40.f), int(m_tInfo.fy + 20.f), szLevel, lstrlen(szLevel));
	TextOut(_dc, int(m_tInfo.fx + 40.f), int(m_tInfo.fy), m_tSkill.m_szDescription, lstrlen(m_tSkill.m_szDescription));

	SelectObject(_dc, oldFont);
}

void CSkill_Icon::Release(void)
{
}
