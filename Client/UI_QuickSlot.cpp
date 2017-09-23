#include "stdafx.h"
#include "UI_QuickSlot.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"

//UI
#include "UI.h"
#include "Skill.h"
#include "Inven.h"
#include "Quick_Slot.h"

typedef list<CQuick_Slot*>::iterator SLOTITER;

CUi_QuickSlot::CUi_QuickSlot(void)
{
	m_eUiType = UI_QUICKSLOT;
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

	return 0;
}

void CUi_QuickSlot::Render(HDC _dc)
{
	SLOTITER iter = m_QuickSlot_List.begin();
	SLOTITER iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Render(_dc);
	}
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
			if (IntersectRect(&rc, pSkill_Ui->GetRect(), (*iter_Slot)->GetRect()))
			{
				//Quick Slot의 Rect와 선택된 스킬 아이콘의 Rect가 충돌할때
				//list에 넣어줌.
				m_QuickSlot_SkillList.push_back(pSkill_Ui->Get_Select_Icon());
				break;
			}
		}
	}
}
#pragma endregion