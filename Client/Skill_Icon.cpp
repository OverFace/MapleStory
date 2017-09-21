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
	Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CSkill_Icon::Release(void)
{
}
