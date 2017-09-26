#include "stdafx.h"
#include "UI_QuickSlot.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "Mouse.h"

//UI
#include "UI.h"
#include "Skill.h"
#include "Inven.h"
#include "Quick_Slot.h"
#include "Skill_Icon.h"

typedef list<CQuick_Slot*>::iterator SLOTITER;
typedef list<CSkill_Icon*>::iterator SKILLITER;

CUi_QuickSlot::CUi_QuickSlot(void)
{
	m_eUiType = UI_QUICKSLOT;
	m_pSelect_SkillIcon = NULL;
	m_bSkill_Icon_DragCheck = false;
	m_bSkill_Icon_DropCheck = false;
	m_bSkill_Icon_OverlapCheck = false;
}

CUi_QuickSlot::~CUi_QuickSlot(void)
{
	Release();
}

void CUi_QuickSlot::Initialize(void)
{
	m_tInfo.fx = 890.f;
	m_tInfo.fy = 655.f;
	m_tInfo.fcx = 31.f;
	m_tInfo.fcy = 31.f;

	//Quick Slot Create
	float fx = 33.f;
	float fy = 0.f;
	int	  iIndex = 0;
	for (int i = 0; i < 8; ++i, ++iIndex)
	{
		CQuick_Slot* pSlot = new CQuick_Slot;
		pSlot->Initialize();
		pSlot->SetSize(m_tInfo.fcx, m_tInfo.fcy);

		//Position Setting
		if (iIndex == 4)
		{
			iIndex = 0;
			fy += 32.f;
		}
		pSlot->SetPos(m_tInfo.fx + (fx * iIndex), m_tInfo.fy + fy);

		//Slot Number 와 CutDonw_Key를 인덱스 순서대로, 지정해주었다.
		//CutDonw_Key : 1, 2, 3, 4
		//              a, d, f, g
		pSlot->Set_Slot_CutDpwn_Key((eCutDown_Key)i);
		pSlot->Set_SlotNumber(i);
		m_QuickSlot_List.push_back(pSlot);
	}

	m_eRenderType = RENDER_UI;
}

int CUi_QuickSlot::Update(void)
{
	SLOTITER iter = m_QuickSlot_List.begin();
	SLOTITER iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Update();
	}

	SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
	SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
	for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
	{
		(*iter_Skill)->Update();
	}

	QuickSlot_Set_SkillIcon();
	QuickSlot_Set_Position();
	QuickSlot_Drag_SkillIcon();
	QuickSlot_Drop_SkillIcon();

	return 0;
}

void CUi_QuickSlot::Render(HDC _dc)
{
	SLOTITER iter = m_QuickSlot_List.begin();
	SLOTITER iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		//(*iter)->Render(_dc);
	}

	QuickSlot_Skill_Icon_Render(_dc);
}

void CUi_QuickSlot::Release(void)
{
	SLOTITER iter = m_QuickSlot_List.begin();
	SLOTITER iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_QuickSlot_List.clear();
}

#pragma region Quick Slot Interlock To Skill UI
void CUi_QuickSlot::QuickSlot_Set_SkillIcon(void)
{
	/*
	스킬 아이콘을 QuickSlot에 등록하는 함수.
	*/
	CSkill_UI* pSkill_Ui = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_SKILL)
		{
			pSkill_Ui = (CSkill_UI*)(*iter);
			break;
		}
	}

	//Function
	RECT rc;
	if (pSkill_Ui->Get_Drop_Check() == true)
	{
		SLOTITER iter_Slot = m_QuickSlot_List.begin();
		SLOTITER iter_Slot_End = m_QuickSlot_List.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if (IntersectRect(&rc, pSkill_Ui->Get_Select_Icon()->GetRect(), (*iter_Slot)->GetRect()))
			{
				//먼저 충돌된 곳에 Skill_Icon이 있는지 없는지 판단해서
				//있으면 만들어 지지 않게 한다.
				SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
				SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
				for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
				{
					if ((*iter_Skill)->Get_Skill_Icon_QuickNumber() == (*iter_Slot)->Get_SlotNumber())
					{
						if ((*iter_Skill)->Get_Skill_Icon_QuickSetCheck() == true)
						{
							m_bSkill_Icon_OverlapCheck = true;
							break;
						}
					}
				}

				//Quick Slot의 Rect와 선택된 스킬 아이콘의 Rect가 충돌할때
				//Quick Slot의 Slot Number를 Skill Icon에 넣어준 다음(구분 용도) 
				//Skill Icon을 새로 만들어서 list에 넣어줌.
				if (pSkill_Ui->Get_Select_Icon()->Get_Skill_Icon_Check() == true && m_bSkill_Icon_OverlapCheck == false)
				{
					//Skill Icon이 활성화 상태일때만 QuickSlot에 넣어준다.
					SKILL tSkill;
					memcpy_s(&tSkill, sizeof(SKILL), pSkill_Ui->Get_Select_Icon()->Get_Skill_Icon_Info(), sizeof(SKILL));

					CSkill_Icon* pSkill_Icon = new CSkill_Icon();
					pSkill_Icon->Set_Skill_Icon_Info(tSkill);
					pSkill_Icon->Set_Skill_Icon_Num(pSkill_Ui->Get_Select_Icon()->Get_Skill_Icon_Num());
					pSkill_Icon->SetSize(32.f, 32.f);
					pSkill_Icon->Set_Skill_Icon_QuickNumber((*iter_Slot)->Get_SlotNumber());
					pSkill_Icon->Set_Skill_Icon_QuickSetCheck(true);
					pSkill_Icon->Set_Skill_Icon_Check(true);

					m_QuickSlot_SkillList.push_back(pSkill_Icon);
				}

				//Skill UI 에서 선택됫던 Icon은 원래 위치대로 되돌리자.
				for (size_t i = 0; i < pSkill_Ui->Get_Skill_Icon()->size(); ++i)
				{
					if ((*(pSkill_Ui->Get_Skill_Icon()))[i]->Get_Skill_Icon_Num() == pSkill_Ui->Get_Select_Icon()->Get_Skill_Icon_Num())
					{
						pSkill_Ui->Get_Select_Icon()->SetPos((*(pSkill_Ui->Get_Skill_Icon()))[i]->GetInfo()->fx, (*(pSkill_Ui->Get_Skill_Icon()))[i]->GetInfo()->fy);
						break;
					}
				}

				break;
			}
		}

		pSkill_Ui->Set_Drop_Check(false);
		m_bSkill_Icon_OverlapCheck = false;
	}
}

void CUi_QuickSlot::QuickSlot_Set_Position(void)
{
	CSkill_UI* pSkill_Ui = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_SKILL)
		{
			pSkill_Ui = (CSkill_UI*)(*iter);
			break;
		}
	}

	SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
	SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();

	for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
	{
		SLOTITER iter_Slot = m_QuickSlot_List.begin();
		SLOTITER iter_Slot_End = m_QuickSlot_List.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			//Skill Icon의 Number와 Quick Slot 자체의 넘버가 같으면 그 위치에 셋팅
			if ((*iter_Skill)->Get_Skill_Icon_QuickNumber() == (*iter_Slot)->Get_SlotNumber())
			{
				if ((*iter_Skill)->Get_Skill_Icon_QuickSetCheck() == true)
				{
					(*iter_Skill)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
				else if((*iter_Skill)->Get_Skill_Icon_QuickSetCheck() == false)
				{
					//Skill Icon Drag 상태가 아닐 때
					if (m_bSkill_Icon_DragCheck == false)
					{
						vector<CSkill_Icon*>::iterator iter_Skill_Ui = pSkill_Ui->Get_Skill_Icon()->begin();
						vector<CSkill_Icon*>::iterator iter_Skill_Ui_End = pSkill_Ui->Get_Skill_Icon()->end();

						for (iter_Skill_Ui; iter_Skill_Ui != iter_Skill_Ui_End; ++iter_Skill_Ui)
						{
							if ((*iter_Skill_Ui)->Get_Skill_Icon_Num() == (*iter_Skill)->Get_Skill_Icon_Num())
							{
								(*iter_Skill)->SetPos((*iter_Skill_Ui)->GetInfo()->fx, (*iter_Skill_Ui)->GetInfo()->fy);
								break;
							}
						}
					}
				}
			} 
		}
	}
}

void CUi_QuickSlot::QuickSlot_Drag_SkillIcon(void)
{
	/*
		Quick Slot에 있는 Skill Icon Drag 기능.
	*/

	POINT pt;
	pt = CMouse::GetPos();

	//Select Skill Icon
	SLOTITER  iter_Slot = m_QuickSlot_List.begin();
	SLOTITER  iter_Slot_End = m_QuickSlot_List.end();
	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; ++iter)
		{
			//Quick Slot에 있는 Quick Slot Number와 Skill Icon의 Number가 같을때
			//해당되는 Skill Icon을 Select Skill Icon으로 지정
			//지정되면서 퀵슬롯 체크를 false로 만들어 준다.
			if ((*iter)->Get_Skill_Icon_QuickSetCheck() == true)
			{
				if (PtInRect((*iter)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
				{
					if ((*iter_Slot)->Get_SlotNumber() == (*iter)->Get_Skill_Icon_QuickNumber())
					{
						m_pSelect_SkillIcon = (*iter);
						break;
					}
				}
			}
		}

		break;
	}

	//Drag Skill Icon
	if (m_pSelect_SkillIcon != NULL)
	{
		if (PtInRect(m_pSelect_SkillIcon->GetRect(), pt) && GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
		{
			m_bSkill_Icon_DragCheck = true;
			m_pSelect_SkillIcon->Set_Skill_Icon_QuickSetCheck(false);
		}
		else if (m_bSkill_Icon_DragCheck == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
		{
			m_bSkill_Icon_DragCheck = false;
			m_bSkill_Icon_DropCheck = true;
		}
	}

	if (m_bSkill_Icon_DragCheck == true && m_bSkill_Icon_DropCheck == false)
	{
		//Skill Drag 움직임
		m_pSelect_SkillIcon->SetPos(pt.x - (m_pSelect_SkillIcon->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_SkillIcon->GetInfo()->fcy / 2.f));
	}
}

void CUi_QuickSlot::QuickSlot_Drop_SkillIcon(void)
{
	/*
		Skill Icon을 Drop 했을때 list 안에 있는 Skill 아이콘을 지운다.
		잘안된다..... m_pSelect_SkillIcon이 바뀌지 않음.
	*/

	if (m_bSkill_Icon_DropCheck == true)
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; )
		{
			if ((*iter)->Get_Skill_Icon_QuickNumber() == m_pSelect_SkillIcon->Get_Skill_Icon_QuickNumber())
			{
				m_QuickSlot_SkillList.erase(iter);
				iter = m_QuickSlot_SkillList.begin();
			}
			else
				++iter;
		}

		m_bSkill_Icon_DropCheck = false;
	}
}
#pragma endregion

#pragma region Quick Slot Render
void CUi_QuickSlot::QuickSlot_Skill_Icon_Render(HDC _dc)
{
	SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
	SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
	for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
	{
		TCHAR szOn[30] = L"_Icon_On";
		TCHAR szIcon_Name[50] = L"";
		TCHAR szOff[30] = L"_Icon_Off";
		TCHAR szIcon_OffName[50] = L"";

		lstrcpy(szIcon_Name, (*iter_Skill)->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_Name, szOn);

		if ((*iter_Skill)->Get_Skill_Icon_Check() == true)
		{
			TransparentBlt(_dc,
				int((*iter_Skill)->GetInfo()->fx), int((*iter_Skill)->GetInfo()->fy),
				int((*iter_Skill)->GetInfo()->fcx), int((*iter_Skill)->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_Name)->GetMemDC(),
				0, 0,
				int((*iter_Skill)->GetInfo()->fcx), int((*iter_Skill)->GetInfo()->fcy),
				RGB(255, 255, 255));
		}
	}
}
#pragma endregion