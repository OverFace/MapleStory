#include "stdafx.h"
#include "Skill.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"

//UI
#include "UI.h"
#include "Stat.h"
#include "Skill_Icon.h"
#include "Skill_Slot.h"

CSkill_UI::CSkill_UI(void)
{
	m_eUiType = UI_SKILL;
	m_dwTime = 0;

	ZeroMemory(&m_tSkill_Input_Info, sizeof(INFO));
	ZeroMemory(&m_tSkill_Input_Rect, sizeof(RECT));
	ZeroMemory(&m_tSkillMove_Rect, sizeof(RECT));
	ZeroMemory(&m_tSkill_EscButton_Info, sizeof(INFO));
	ZeroMemory(&m_tSkill_EscButton_Rect, sizeof(RECT));
	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&m_tSkill_PlusButton_Info[i], sizeof(INFO));
		ZeroMemory(&m_tSkill_PlusButton_Rect[i], sizeof(RECT));
		m_iSkill_PlusButton_Option[i] = 0;
	}
	
	m_bSkillMoveCheck = false;
	m_bSkillPlus_Button_Visible = false;
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

	//Skill Plus Button 
	for (int i = 0; i < 4; ++i)
	{
		m_tSkill_PlusButton_Info[i].fx = m_tInfo.fx + 136.f;
		m_tSkill_PlusButton_Info[i].fy = m_tInfo.fy + 115.f + (39.f * i);
		m_tSkill_PlusButton_Info[i].fcx = 13.f;
		m_tSkill_PlusButton_Info[i].fcy = 12.f;
	}

	//Skill Icon
	Skill_Icon_Create();
	Skill_Icon_Position();

	m_dwTime = GetTickCount();
}

int CSkill_UI::Update(void)
{
	Skill_Rect_Update();
		
	//Key Setting
	Skill_Key();

	if (m_bVisible == true)
	{
		Skill_Move();
		Skill_EscButton_Click();
		Skill_PlusButton_Click();
		Skill_Icon_Update();
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

		//Skill Plus Button
		if (m_bSkillPlus_Button_Visible == true)
		{
			for (int i = 0; i < 4; ++i)
			{
				TransparentBlt(_dc,
					int(m_tSkill_PlusButton_Info[i].fx), int(m_tSkill_PlusButton_Info[i].fy),
					int(m_tSkill_PlusButton_Info[i].fcx), int(m_tSkill_PlusButton_Info[i].fcy),
					GETS(CBitMapMgr)->FindImage(L"Button_Plus")->GetMemDC(),
					int(m_iSkill_PlusButton_Option[i] * m_tSkill_PlusButton_Info[i].fcx), 0,
					int(m_tSkill_PlusButton_Info[i].fcx), int(m_tSkill_PlusButton_Info[i].fcy),
					RGB(255, 255, 255));
			}
		}

		//Skill Icon
		Skill_Icon_Render(_dc);
	}
}

void CSkill_UI::Release(void)
{
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		SAFE_DELETE(m_vecSkill[i]);
	}
	m_vecSkill.clear();
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
	//Skill â�� ���콺�� �����̰� ����� �Լ�.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tSkillMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bSkillMoveCheck = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bSkillMoveCheck == true)
		m_bSkillMoveCheck = false;

	if (m_bSkillMoveCheck == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);    //10.f �� Rect�� y�� / 2 �� ��.

		//Skill Move Rect
		m_tSkillMove_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx - 12.f / 2.f) - m_tInfo.fcx - 12.f / 2.f);
		m_tSkillMove_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx - 12.f / 2.f) + m_tInfo.fcx - 12.f / 2.f);
		m_tSkillMove_Rect.top = long(m_tInfo.fx + (20.f / 2.f) - 20.f / 2.f);
		m_tSkillMove_Rect.bottom = long(m_tInfo.fx + (20.f / 2.f) + 20.f / 2.f);
	}
}

void CSkill_UI::Skill_Rect_Update(void)
{
	//Skill Move Rect
	m_tSkillMove_Rect.left = long(m_tInfo.fx + (174.f - 12.f / 2.f) - 174.f - 12.f / 2.f);
	m_tSkillMove_Rect.right = long(m_tInfo.fx + (174.f - 12.f / 2.f) + 174.f - 12.f / 2.f);
	m_tSkillMove_Rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
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

	//Skill Plus Button Rect
	for (int i = 0; i < 4; ++i)
	{
		m_tSkill_PlusButton_Info[i].fx		= m_tInfo.fx + 136.f;
		m_tSkill_PlusButton_Info[i].fy		= m_tInfo.fy + 115.f + (39.f * i);
		m_tSkill_PlusButton_Rect[i].left	= long(m_tSkill_PlusButton_Info[i].fx + (m_tSkill_PlusButton_Info[i].fcx / 2.f) - m_tSkill_PlusButton_Info[i].fcx / 2);
		m_tSkill_PlusButton_Rect[i].right	= long(m_tSkill_PlusButton_Info[i].fx + (m_tSkill_PlusButton_Info[i].fcx / 2.f) + m_tSkill_PlusButton_Info[i].fcx / 2);
		m_tSkill_PlusButton_Rect[i].top		= long(m_tSkill_PlusButton_Info[i].fy + (m_tSkill_PlusButton_Info[i].fcy / 2.f) - m_tSkill_PlusButton_Info[i].fcy / 2);
		m_tSkill_PlusButton_Rect[i].bottom  = long(m_tSkill_PlusButton_Info[i].fy + (m_tSkill_PlusButton_Info[i].fcy / 2.f) + m_tSkill_PlusButton_Info[i].fcy / 2);
	}	
}

#pragma region Button Function
void CSkill_UI::Skill_EscButton_Click(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tSkill_EscButton_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		m_bVisible = false;
}

void CSkill_UI::Skill_PlusButton_Click(void)
{
	/* Skill Plus Button Click ���. Button Click�� Skill Level Up(���� ó�� �ȵ�) */

	POINT pt;
	pt = CMouse::GetPos();
	
	//Get Stat UI
	CStat* pStat = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_STAT)
			pStat = ((CStat*)(*iter));
	}

	//Level Up Check
	if (pStat->Get_LevelUp_Check() == true)
	{
		m_bSkillPlus_Button_Visible = true;
		
		static bool bCheck = false;
		if (PtInRect(&m_tSkill_PlusButton_Rect[0], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 1 = First Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[1], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 2 = Second Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[2], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 3 = Thrid Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[3], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 4 = Four Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			bCheck = true;
		}

		for (int i = 0; i < 4; ++i)
		{
			m_iSkill_PlusButton_Option[i] = 1;

			if (PtInRect(&m_tSkill_PlusButton_Rect[i], pt) == false && bCheck == true)
				bCheck = false;
		}
	}
	else
	{
		m_bSkillPlus_Button_Visible = false;
		
		for (int i = 0; i < 4; ++i)
			m_iSkill_PlusButton_Option[i] = 0;
	}
}
#pragma endregion

#pragma region Skill Function
void CSkill_UI::Skill_Icon_Create(void)
{
	/*
	MeanStrike_Icon_On & MeanStrike_Icon_Off       - skill 1
	Blot_Icon_On & Blot_Icon_Off			       - skill 2
	Ascension_Icon_On & Ascension_Icon_Off		   - skill 3
	Annihilation_Icon_On & Annihilation_Icon_Off   = skill 4
	*/

	//MeanStrike
	SKILL tSkill;
	CSkill_Icon* pIcon = new CSkill_Icon();
	pIcon->Initialize();
	
	//Skill Info
	//MeanStrike
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"MeanStrike");
	lstrcpy(tSkill.m_szDescription, L"�⺻ ����");
	tSkill.m_iSkill_Level = 1;
	tSkill.m_fSkill_Att = 10;
	tSkill.m_eSkill_CutDownKey = CK_END;	
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);
	
	//Blot
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Blot");
	lstrcpy(tSkill.m_szDescription, L"õõ ����");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_fSkill_Att = 30;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);

	//Ascension(��õ)
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Ascension");
	lstrcpy(tSkill.m_szDescription, L"��õ");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_fSkill_Att = 50;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);

	//Annihilation(����)
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Ascension");
	lstrcpy(tSkill.m_szDescription, L"����");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_fSkill_Att = 200;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);
}

void CSkill_UI::Skill_Icon_Position(void)
{
	float fx = 10.f;
	float fy = 32.f;
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		m_vecSkill[i]->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (32.f * i));
		m_vecSkill[i]->SetSize(32.f, 32.f);
		m_vecSkill[i]->Set_Skill_Icon_Num(i);
	}
}

void CSkill_UI::Skill_Icon_Update(void)
{
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		m_vecSkill[i]->Update();
	}
}

void CSkill_UI::Skill_Icon_Render(HDC _dc)
{
	TCHAR szOn[30] = L"_On";
	TCHAR szIcon_Name[50] = L"";

	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		//Icon Image Render
		lstrcpy(szIcon_Name, m_vecSkill[i]->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_Name, szOn);

		TransparentBlt(_dc,
			int(m_vecSkill[i]->GetInfo()->fx), int(m_vecSkill[i]->GetInfo()->fy),
			int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
			GETS(CBitMapMgr)->FindImage(szIcon_Name)->GetMemDC(),
			0, 0,
			int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
			RGB(255, 255, 255));

		//Rect Render
		//m_vecSkill[i]->Render(_dc);
	}
}
#pragma endregion


