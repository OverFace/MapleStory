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
#include "UI_QuickSlot.h"

typedef list<CSkill_Slot*>::iterator SKILLSLOTITER;

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
	m_bSkillLevel_Up_Check = false;
	m_bSkill_Select_Check = false;
	m_bSkill_Drop_Check = false;

	for (int i = 0; i < 4; ++i)
		m_pSelect_Skill[i] = NULL;
	m_pPick_Icon = NULL;
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

	//Skill Slot
	Skill_Slot_Create();

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

		//Skill Slot
		Skill_Slot_Update();
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
		Skill_Icon_InfoRender(_dc);

		//Skill Slot
		//Skill_Slot_Render(_dc);
	}
}

void CSkill_UI::Release(void)
{
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		SAFE_DELETE(m_vecSkill[i]);
	}
	m_vecSkill.clear();

	for (size_t i = 0; i < m_vecSkill_Slot.size(); ++i)
	{
		SAFE_DELETE(m_vecSkill_Slot[i]);
	}
	m_vecSkill_Slot.clear();

	for (int i = 0; i < 4; ++i)
	{
		if (m_pSelect_Skill[i] != NULL)
			SAFE_DELETE(m_pSelect_Skill[i]);
	}
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
	/* Skill Plus Button Click 기능. Button Click시 Skill Level Up(아직 처리 안됨) */

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

	//Level Up Check On & Off
	static bool bCheck = false;
	if (pStat->Get_PlayerStat()->m_iSkillPoint <= 0 && bCheck == true)
	{
		m_bSkillLevel_Up_Check = false;
		bCheck = false;
	}

	if (pStat->Get_PlayerStat()->m_iSkillPoint > 0 && bCheck == false)
	{
		m_bSkillLevel_Up_Check = true;
		bCheck = true;
	}

	//Level Up Check
	if (m_bSkillLevel_Up_Check == true)
	{
		m_bSkillPlus_Button_Visible = true;
		
		static bool bCheck = false;
		if (PtInRect(&m_tSkill_PlusButton_Rect[0], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 1 = First Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			for (size_t i = 0; i < m_vecSkill.size(); ++i)
			{
				if (m_vecSkill[i]->Get_Skill_Icon_Num() == 0)
				{
					//Skill Level
					int iLevel = m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level;
					++iLevel;
					m_vecSkill[i]->Set_Skill_Icon_Level(iLevel);
					
					//Skill Att
					float fAtt = m_vecSkill[i]->Get_Skill_Icon_Info()->m_fSkill_Att;
					fAtt += 10.f;
					m_vecSkill[i]->Set_Skill_Icon_Att(fAtt);

					break;
				}
			}

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[1], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 2 = Second Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			for (size_t i = 0; i < m_vecSkill.size(); ++i)
			{
				if (m_vecSkill[i]->Get_Skill_Icon_Num() == 1)
				{
					//Skill Level
					int iLevel = m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level;
					++iLevel;
					m_vecSkill[i]->Set_Skill_Icon_Level(iLevel);

					//Skill Att
					float fAtt = m_vecSkill[i]->Get_Skill_Icon_Info()->m_fSkill_Att;
					fAtt += 20.f;
					m_vecSkill[i]->Set_Skill_Icon_Att(fAtt);

					break;
				}
			}

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[2], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 3 = Thrid Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			for (size_t i = 0; i < m_vecSkill.size(); ++i)
			{
				if (m_vecSkill[i]->Get_Skill_Icon_Num() == 2)
				{
					//Skill Level
					int iLevel = m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level;
					++iLevel;
					m_vecSkill[i]->Set_Skill_Icon_Level(iLevel);

					//Skill Att
					float fAtt = m_vecSkill[i]->Get_Skill_Icon_Info()->m_fSkill_Att;
					fAtt += 30.f;
					m_vecSkill[i]->Set_Skill_Icon_Att(fAtt);

					break;
				}
			}

			bCheck = true;
		}
		else if (PtInRect(&m_tSkill_PlusButton_Rect[3], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bCheck == false)
		{
			//Plus Button 4 = Four Skill Level Button
			--pStat->Get_PlayerStat()->m_iSkillPoint;

			for (size_t i = 0; i < m_vecSkill.size(); ++i)
			{
				if (m_vecSkill[i]->Get_Skill_Icon_Num() == 3)
				{
					//Skill Level
					int iLevel = m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level;
					++iLevel;
					m_vecSkill[i]->Set_Skill_Icon_Level(iLevel);

					//Skill Att
					float fAtt = m_vecSkill[i]->Get_Skill_Icon_Info()->m_fSkill_Att;
					fAtt += 40.f;
					m_vecSkill[i]->Set_Skill_Icon_Att(fAtt);

					break;
				}
			}

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
	Annihilation_Icon_On & Annihilation_Icon_Off   - skill 4
	*/

	//MeanStrike
	SKILL tSkill;
	CSkill_Icon* pIcon = new CSkill_Icon();
	pIcon->Initialize();
	
	//Skill Info
	//MeanStrike
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"MeanStrike");
	lstrcpy(tSkill.m_szDescription, L"쌔려뿌!");
	tSkill.m_iSkill_Level = 1;
	tSkill.m_iSkill_Master_Level = 15;
	tSkill.m_fSkill_Att = 10;
	tSkill.m_eSkill_CutDownKey = CK_END;	
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);
	
	//Blot
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Blot");
	lstrcpy(tSkill.m_szDescription, L"마! 번개간다이~");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_iSkill_Master_Level = 20;
	tSkill.m_fSkill_Att = 30;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);

	//Ascension(승천)
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Ascension");
	lstrcpy(tSkill.m_szDescription, L"골로 가고싶나아~?");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_iSkill_Master_Level = 20;
	tSkill.m_fSkill_Att = 50;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);

	//Annihilation(섬멸)
	pIcon = new CSkill_Icon();
	ZeroMemory(&tSkill, sizeof(SKILL));
	lstrcpy(tSkill.m_szName, L"Annihilation");
	lstrcpy(tSkill.m_szDescription, L"따 때려 뽀사뿔라");
	tSkill.m_iSkill_Level = 0;
	tSkill.m_iSkill_Master_Level = 30;
	tSkill.m_fSkill_Att = 200;
	tSkill.m_eSkill_CutDownKey = CK_END;
	pIcon->Set_Skill_Icon_Info(tSkill);

	m_vecSkill.push_back(pIcon);
}

void CSkill_UI::Skill_Icon_Position(void)
{
	float fx = 12.f;
	float fy = 95.f;
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		m_vecSkill[i]->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (40.f * i));
		m_vecSkill[i]->SetSize(32.f, 32.f);
		m_vecSkill[i]->Set_Skill_Icon_Num(i);
	}
}

void CSkill_UI::Skill_Icon_Update(void)
{
	float fx = 12.f;
	float fy = 95.f;
	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		m_vecSkill[i]->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (40.f * i));
		m_vecSkill[i]->Update();

		//Skill On Off Check1
		if (m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level == 0)
			m_vecSkill[i]->Set_Skill_Icon_Check(false);
		else if(m_vecSkill[i]->Get_Skill_Icon_Info()->m_iSkill_Level != 0)
			m_vecSkill[i]->Set_Skill_Icon_Check(true);
	}
}

void CSkill_UI::Skill_Icon_Render(HDC _dc)
{
	TCHAR szOn[30] = L"_Icon_On";
	TCHAR szIcon_Name[50] = L"";
	TCHAR szOff[30] = L"_Icon_Off";
	TCHAR szIcon_OffName[50] = L"";

	for (size_t i = 0; i < m_vecSkill.size(); ++i)
	{
		//Icon Off Render
		lstrcpy(szIcon_OffName, m_vecSkill[i]->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_OffName, szOff);

		if (m_vecSkill[i]->Get_Skill_Icon_Check() == false)
		{
			TransparentBlt(_dc,
				int(m_vecSkill[i]->GetInfo()->fx), int(m_vecSkill[i]->GetInfo()->fy),
				int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_OffName)->GetMemDC(),
				0, 0,
				int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
				RGB(255, 255, 255));
		}

		//Icon Image Render
		lstrcpy(szIcon_Name, m_vecSkill[i]->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_Name, szOn);

		if (m_vecSkill[i]->Get_Skill_Icon_Check() == true)
		{
			TransparentBlt(_dc,
				int(m_vecSkill[i]->GetInfo()->fx), int(m_vecSkill[i]->GetInfo()->fy),
				int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_Name)->GetMemDC(),
				0, 0,
				int(m_vecSkill[i]->GetInfo()->fcx), int(m_vecSkill[i]->GetInfo()->fcy),
				RGB(255, 255, 255));
		}
	}
}

void CSkill_UI::Skill_Icon_InfoRender(HDC _dc)
{
	//Skill Icon Info Render
	for(size_t i = 0; i < m_vecSkill.size(); ++i)
		m_vecSkill[i]->Render(_dc);

	//Skill Point Render
	CStat* pStat = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_STAT)
			pStat = ((CStat*)(*iter));
	}

	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

	//Skill Point
	TCHAR szSkill_Point[100] = { 0 };
	_stprintf_s(szSkill_Point, _countof(szSkill_Point), L"%d", pStat->Get_PlayerStat()->m_iSkillPoint);

	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, int(m_tInfo.fx + 145.f), int(m_tInfo.fy + 258.f), szSkill_Point, lstrlen(szSkill_Point));
	SelectObject(_dc, oldFont);
}
#pragma endregion

#pragma region Skill Slot
void CSkill_UI::Skill_Slot_Create(void)
{
	float fx = 12.f;
	float fy = 95.f;
	for (int i = 0; i < 4; ++i)
	{
		CSkill_Slot* pSlot = new CSkill_Slot();
		pSlot->Initialize();
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (40.f * i));
		pSlot->Set_SlotNumber(i);
		m_vecSkill_Slot.push_back(pSlot);
	}
}

void CSkill_UI::Skill_Slot_Update(void)
{
	float fx = 12.f;
	float fy = 95.f;
	for (size_t i = 0; i < m_vecSkill_Slot.size(); ++i)
	{
		m_vecSkill_Slot[i]->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (40.f * i));
		m_vecSkill_Slot[i]->Update();
	}
}

void CSkill_UI::Skill_Slot_Render(HDC _dc)
{
	for (size_t i = 0; i < m_vecSkill_Slot.size(); ++i)
		m_vecSkill_Slot[i]->Render(_dc);
}
#pragma endregion

#pragma region 기능 변경 해서 필요 없는 부분
/*
void CSkill_UI::Skill_Icon_Drag(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	//Select Skill
	for (size_t i = 0; i < m_vecSkill_Slot.size(); ++i)
	{
		if (PtInRect(m_vecSkill_Slot[i]->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		{
			for (size_t j = 0; j < m_vecSkill.size(); ++j)
			{
				if (m_vecSkill_Slot[i]->Get_SlotNumber() == m_vecSkill[i]->Get_Skill_Icon_Num())
				{
					//Allocate Skill Icon
					SKILL tSkill;
					memcpy_s(&tSkill, sizeof(SKILL), m_vecSkill[i]->Get_Skill_Icon_Info(), sizeof(SKILL));

					if (m_vecSkill[i]->Get_Skill_Icon_Num() == 0)
					{
						if (m_pSelect_Skill[0] == NULL)
						{
							m_pSelect_Skill[0] = new CSkill_Icon();
							m_pSelect_Skill[0]->Set_Skill_Icon_Info(tSkill);
							m_pSelect_Skill[0]->Set_Skill_Icon_Num(m_vecSkill[i]->Get_Skill_Icon_Num());
							m_pSelect_Skill[0]->SetSize(32.f, 32.f);
							m_pSelect_Skill[0]->SetPos(pt.x - (m_pSelect_Skill[0]->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_Skill[0]->GetInfo()->fcy / 2.f));
						}

						m_pPick_Icon = m_pSelect_Skill[0];
					}
					else if (m_vecSkill[i]->Get_Skill_Icon_Num() == 1)
					{
						if (m_pSelect_Skill[1] == NULL)
						{
							m_pSelect_Skill[1] = new CSkill_Icon();
							m_pSelect_Skill[1]->Set_Skill_Icon_Info(tSkill);
							m_pSelect_Skill[1]->Set_Skill_Icon_Num(m_vecSkill[i]->Get_Skill_Icon_Num());
							m_pSelect_Skill[1]->SetSize(32.f, 32.f);
							m_pSelect_Skill[1]->SetPos(pt.x - (m_pSelect_Skill[1]->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_Skill[1]->GetInfo()->fcy / 2.f));
						}

						m_pPick_Icon = m_pSelect_Skill[1];
					}
					else if (m_vecSkill[i]->Get_Skill_Icon_Num() == 2)
					{
						if (m_pSelect_Skill[2] == NULL)
						{
							m_pSelect_Skill[2] = new CSkill_Icon();
							m_pSelect_Skill[2]->Set_Skill_Icon_Info(tSkill);
							m_pSelect_Skill[2]->Set_Skill_Icon_Num(m_vecSkill[i]->Get_Skill_Icon_Num());
							m_pSelect_Skill[2]->SetSize(32.f, 32.f);
							m_pSelect_Skill[2]->SetPos(pt.x - (m_pSelect_Skill[2]->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_Skill[2]->GetInfo()->fcy / 2.f));
						}

						m_pPick_Icon = m_pSelect_Skill[2];
					}
					else if (m_vecSkill[i]->Get_Skill_Icon_Num() == 3)
					{
						if (m_pSelect_Skill[3] == NULL)
						{
							m_pSelect_Skill[3] = new CSkill_Icon();
							m_pSelect_Skill[3]->Set_Skill_Icon_Info(tSkill);
							m_pSelect_Skill[3]->Set_Skill_Icon_Num(m_vecSkill[i]->Get_Skill_Icon_Num());
							m_pSelect_Skill[3]->SetSize(32.f, 32.f);
							m_pSelect_Skill[3]->SetPos(pt.x - (m_pSelect_Skill[3]->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_Skill[3]->GetInfo()->fcy / 2.f));
						}

						m_pPick_Icon = m_pSelect_Skill[3];
					}

					break;
				}
			}

			break;
		}
	}

	//Drag Skill
	if (m_pPick_Icon != NULL)
	{
		if (PtInRect(m_pPick_Icon->GetRect(), pt) && GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON)
			&& m_bSkillMoveCheck == false)
		{
			//VK_LBUTTON 계속 누르고 SkillMoveCheck가 false일때 Drag
			m_bSkill_Select_Check = true;
		}
		else if (m_bSkill_Select_Check == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
		{
			m_bSkill_Select_Check = false;
			m_bSkill_Drop_Check = true;

			//Skill Icon이 Drop 되었을때 Quick Slot의 Rect와 충돌하지 않으면 지워준다.
		}
	}

	if (m_bSkill_Select_Check == true && m_bSkill_Drop_Check == false)
	{
		//Drag 움직임
		m_pPick_Icon->SetPos(pt.x - (m_pPick_Icon->GetInfo()->fcx / 2.f), pt.y - (m_pPick_Icon->GetInfo()->fcy / 2.f));
	}
}

void CSkill_UI::Skill_Icon_Escape(void)
{
	CUi_QuickSlot* pQuick_Slot = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_QUICKSLOT)
		{
			pQuick_Slot = (CUi_QuickSlot*)(*iter);
			break;
		}
	}

	if (pQuick_Slot->Get_QuickSlot_EscapeCheck() == true)
	{
		
		pQuick_Slot->Set_QuickSlot_EscapeCheck(false);
	}
}

void CSkill_UI::Skill_DragIcon_Update(void)
{
	if (m_pPick_Icon != NULL)
	{
		m_pPick_Icon->Update();
	}
}

void CSkill_UI::Skill_DragIcon_Render(HDC _dc)
{
	if (m_pPick_Icon != NULL)
	{
		TCHAR szOn[30] = L"_Icon_On";
		TCHAR szIcon_Name[50] = L"";
		TCHAR szOff[30] = L"_Icon_Off";
		TCHAR szIcon_OffName[50] = L"";

		//Icon Off Render
		lstrcpy(szIcon_OffName, m_pPick_Icon->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_OffName, szOff);
		
		//Skill Icon On / Off Setting
		if (m_pPick_Icon->Get_Skill_Icon_Info()->m_iSkill_Level <= 0)
			m_pPick_Icon->Set_Skill_Icon_Check(false);
		else if (m_pPick_Icon->Get_Skill_Icon_Info()->m_iSkill_Level > 0)
			m_pPick_Icon->Set_Skill_Icon_Check(true);

		if (m_pPick_Icon->Get_Skill_Icon_Check() == false)
		{
			TransparentBlt(_dc,
				int(m_pPick_Icon->GetInfo()->fx), int(m_pPick_Icon->GetInfo()->fy),
				int(m_pPick_Icon->GetInfo()->fcx), int(m_pPick_Icon->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_OffName)->GetMemDC(),
				0, 0,
				int(m_pPick_Icon->GetInfo()->fcx), int(m_pPick_Icon->GetInfo()->fcy),
				RGB(255, 255, 255));
		}

		//Icon Image Render
		lstrcpy(szIcon_Name, m_pPick_Icon->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_Name, szOn);

		if (m_pPick_Icon->Get_Skill_Icon_Check() == true)
		{
			TransparentBlt(_dc,
				int(m_pPick_Icon->GetInfo()->fx), int(m_pPick_Icon->GetInfo()->fy),
				int(m_pPick_Icon->GetInfo()->fcx), int(m_pPick_Icon->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_Name)->GetMemDC(),
				0, 0,
				int(m_pPick_Icon->GetInfo()->fcx), int(m_pPick_Icon->GetInfo()->fcy),
				RGB(255, 255, 255));
		}
	}
}
*/
#pragma endregion




