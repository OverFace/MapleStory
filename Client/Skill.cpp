#include "stdafx.h"
#include "Skill.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"

CSkill_UI::CSkill_UI(void)
{
	m_eUiType = UI_SKILL;
	m_dwTime = 0;
	ZeroMemory(&m_tSkill_Input_Info, sizeof(INFO));
	ZeroMemory(&m_tSkill_Input_Rect, sizeof(RECT));
	ZeroMemory(&m_tSkillMove_Rect, sizeof(RECT));
	ZeroMemory(&m_tSkill_EscButton_Info, sizeof(INFO));
	ZeroMemory(&m_tSkill_EscButton_Rect, sizeof(RECT));
	m_bSkillMoveCheck = false;
}

CSkill_UI::~CSkill_UI(void)
{
	Release();
}

void CSkill_UI::Initialize(void)
{
	//Skill
	m_tInfo.fx = 410.f;
	m_tInfo.fy = 150.f;
	m_tInfo.fcx = 174.f;
	m_tInfo.fcy = 300.f;
	m_eRenderType = RENDER_UI;

	//Skill Input 
	m_tSkill_Input_Info.fx = m_tInfo.fx + 10.f;
	m_tSkill_Input_Info.fy = m_tInfo.fy + 90.f;
	m_tSkill_Input_Info.fcx = 140.f;
	m_tSkill_Input_Info.fcy = 155.f;
	
	//Skill Esc Button
	m_tSkill_EscButton_Info.fx = m_tInfo.fx + 151.f;
	m_tSkill_EscButton_Info.fy = m_tInfo.fy + 8.f;
	m_tSkill_EscButton_Info.fcx = 15.f;
	m_tSkill_EscButton_Info.fcy = 15.f;

	m_dwTime = GetTickCount();
}

int CSkill_UI::Update(void)
{
	//Skill Move Rect
	m_tSkillMove_Rect.left	 = long(m_tInfo.fx + (174.f - 12.f / 2.f) - 174.f - 12.f / 2.f);
	m_tSkillMove_Rect.right  = long(m_tInfo.fx + (174.f - 12.f / 2.f) + 174.f - 12.f / 2.f);
	m_tSkillMove_Rect.top	 = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
	m_tSkillMove_Rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);
	
	//Skill Input
	m_tSkill_Input_Info.fx = m_tInfo.fx + 10.f;
	m_tSkill_Input_Info.fy = m_tInfo.fy + 90.f;

	//Esc Button Rect
	m_tSkill_EscButton_Info.fx = m_tInfo.fx + 151.f;
	m_tSkill_EscButton_Info.fy = m_tInfo.fy + 8.f;
	m_tSkill_EscButton_Rect.left = long(m_tSkill_EscButton_Info.fx + (m_tSkill_EscButton_Info.fcx / 2.f) - m_tSkill_EscButton_Info.fcx / 2.f);
	m_tSkill_EscButton_Rect.right = long(m_tSkill_EscButton_Info.fx + (m_tSkill_EscButton_Info.fcx / 2.f) + m_tSkill_EscButton_Info.fcx / 2.f);
	m_tSkill_EscButton_Rect.top = long(m_tSkill_EscButton_Info.fy + (m_tSkill_EscButton_Info.fcy / 2.f) - m_tSkill_EscButton_Info.fcy / 2.f);
	m_tSkill_EscButton_Rect.bottom = long(m_tSkill_EscButton_Info.fy + (m_tSkill_EscButton_Info.fcy / 2.f) + m_tSkill_EscButton_Info.fcy / 2.f);

	//Key Setting
	Skill_Key();

	if (m_bVisible == true)
	{
		Skill_Move();
		Skill_EscButton_Click();
	}

	return 0;
}

void CSkill_UI::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		//Skill
		TransparentBlt(_dc,
			int(m_tInfo.fx), int(m_tInfo.fy),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Skill")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));

		//Skill Input
		TransparentBlt(_dc,
			int(m_tSkill_Input_Info.fx), int(m_tSkill_Input_Info.fy),
			int(m_tSkill_Input_Info.fcx), int(m_tSkill_Input_Info.fcy),
			GETS(CBitMapMgr)->FindImage(L"Skill_Input")->GetMemDC(),
			0, 0,
			int(m_tSkill_Input_Info.fcx), int(m_tSkill_Input_Info.fcy),
			RGB(0, 0, 0));
	}
}

void CSkill_UI::Release(void)
{
}

void CSkill_UI::Skill_Key(void)
{
	static bool bIsPress_Skill = false;
	if (GETS(CKeyMgr)->OnceKeyDown('K') && bIsPress_Skill == false)
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

void CSkill_UI::Skill_Move(void)
{
	//Skill 창을 마우스로 움직이게 만드는 함수.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tSkillMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bSkillMoveCheck = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bSkillMoveCheck == true)
		m_bSkillMoveCheck = false;

	if (m_bSkillMoveCheck == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);    //10.f 는 Rect의 y의 / 2 한 값.

		//Skill Move Rect
		m_tSkillMove_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx - 12.f / 2.f) - m_tInfo.fcx - 12.f / 2.f);
		m_tSkillMove_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx - 12.f / 2.f) + m_tInfo.fcx - 12.f / 2.f);
		m_tSkillMove_Rect.top = long(m_tInfo.fx + (20.f / 2.f) - 20.f / 2.f);
		m_tSkillMove_Rect.bottom = long(m_tInfo.fx + (20.f / 2.f) + 20.f / 2.f);
	}
}

void CSkill_UI::Skill_EscButton_Click(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tSkill_EscButton_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		m_bVisible = false;
}

