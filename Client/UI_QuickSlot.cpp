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
	m_dwTime = 0;

	for (int i = 0; i < CK_END; ++i)
		m_bSkill_CutDownKey_check[i] = false;
	m_bSkill_Icon_pushCheck = false;
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

	QuickSlot_Set_SkillIcon();
	QuickSlot_Set_SkillIcon_Position();
	QuickSlot_Set_SkillIcon_Active();
	QuickSlot_Set_SkillIcon_CutDownKey();
	QuickSlot_SkillIcon_CoolTime();

	//QuickSlot_Drag_SkillIcon();
	//QuickSlot_Drop_Swap_SkillIcon();

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

	SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
	SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
	for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
	{
		SAFE_DELETE(*iter_Skill);
	}
	m_QuickSlot_SkillList.clear();
}

void CUi_QuickSlot::Set_QuickSlot_SkillIcon_CoolTime(float _fTime, int _iSkillNum)
{
	SKILLITER iter = m_QuickSlot_SkillList.begin();
	SKILLITER iter_End = m_QuickSlot_SkillList.end();

	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->Get_Skill_Icon_Num() == _iSkillNum)
		{
			(*iter)->Set_Skill_Icon_CoolTime(_fTime);
			break;
		}
	}
}

#pragma region QuickSlot Skill Icon Function
void CUi_QuickSlot::QuickSlot_Set_SkillIcon(void)
{
	/*
	스킬 아이콘을 QuickSlot에 등록하는 함수.
	*/

	//Skill UI Pointer Variable Setting
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

	//Skill Icon Setting Function
	if (pSkill_Ui != NULL && m_bSkill_Icon_pushCheck == false)
	{
		vector<CSkill_Icon*>* pSkill_Icon_List = pSkill_Ui->Get_Skill_Icon();

		for (size_t i = 0; i < pSkill_Icon_List->size(); ++i)
		{
			SKILL tSkill;
			memcpy_s(&tSkill, sizeof(SKILL), (*pSkill_Icon_List)[i]->Get_Skill_Icon_Info(), sizeof(SKILL));

			CSkill_Icon* pSkill = new CSkill_Icon();
			pSkill->Set_Skill_Icon_Info(tSkill);
			pSkill->Set_Skill_Icon_Num((*pSkill_Icon_List)[i]->Get_Skill_Icon_Num());
			pSkill->SetSize(32.f, 32.f);

			m_QuickSlot_SkillList.push_back(pSkill);
		}

		m_bSkill_Icon_pushCheck = true;
	}
}

void CUi_QuickSlot::QuickSlot_Set_SkillIcon_Position(void)
{
	SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
	SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();

	for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
	{
		SLOTITER iter_Slot = m_QuickSlot_List.begin();
		SLOTITER iter_Slot_End = m_QuickSlot_List.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if ((*iter_Slot)->Get_SlotNumber() == (*iter_Skill)->Get_Skill_Icon_Num())
				(*iter_Skill)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
		}
	}
}

void CUi_QuickSlot::QuickSlot_Set_SkillIcon_Active(void)
{
	//Skill UI 에서 스킬 아이콘이 활성화 되어 있는지 확인하여
	//활성화 시키는 함수.

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

	if (pSkill_Ui != NULL)
	{
		for (size_t i = 0; i < pSkill_Ui->Get_Skill_Icon()->size(); ++i)
		{
			CSkill_Icon* pTemp = (*pSkill_Ui->Get_Skill_Icon())[i];

			//for문 안에서 계속해서 받아와야 갱신이된다.
			SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
			SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
			for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
			{
				if (pTemp->Get_Skill_Icon_Num() == 0 && (*iter_Skill)->Get_Skill_Icon_Num() == 0)
				{
					//0번 스킬
					if (pTemp->Get_Skill_Icon_Check() == true)
						(*iter_Skill)->Set_Skill_Icon_Check(true);
					else
						(*iter_Skill)->Set_Skill_Icon_Check(false);
				}
				else if (pTemp->Get_Skill_Icon_Num() == 1 && (*iter_Skill)->Get_Skill_Icon_Num() == 1)
				{
					//1번 스킬
					if (pTemp->Get_Skill_Icon_Check() == true)
						(*iter_Skill)->Set_Skill_Icon_Check(true);
					else
						(*iter_Skill)->Set_Skill_Icon_Check(false);
				}
				else if (pTemp->Get_Skill_Icon_Num() == 2 && (*iter_Skill)->Get_Skill_Icon_Num() == 2)
				{
					//2번 스킬
					if (pTemp->Get_Skill_Icon_Check() == true)
						(*iter_Skill)->Set_Skill_Icon_Check(true);
					else
						(*iter_Skill)->Set_Skill_Icon_Check(false);
				}
				else if (pTemp->Get_Skill_Icon_Num() == 3 && (*iter_Skill)->Get_Skill_Icon_Num() == 3)
				{
					//3번 스킬
					if (pTemp->Get_Skill_Icon_Check() == true)
						(*iter_Skill)->Set_Skill_Icon_Check(true);
					else
						(*iter_Skill)->Set_Skill_Icon_Check(false);
				}
			}
		}
	}
}

void CUi_QuickSlot::QuickSlot_Set_SkillIcon_CutDownKey(void)
{
	/*
		Skill Icon CutDown 키로 스킬을 사용하는 함수.
		-- 나중에 스킬이 나가도록 조정 해야 된다 --
	*/

	//0x30 ~ 0x39 : 0 ~ 9번 숫자키.
	if (GETS(CKeyMgr)->OnceKeyDown(0x31))
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();

		for (iter; iter != iter_End; ++iter)
		{
			//1번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_1
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_1] == false)
			{
				cout << "1번 스킬 발동" << endl;
				//m_bSkill_CutDownKey_check[CK_1] = true;
			}
		}
	}
	else if (GETS(CKeyMgr)->OnceKeyUp(0x31))
	{
		m_bSkill_CutDownKey_check[CK_1] = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown(0x32))
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();

		for (iter; iter != iter_End; ++iter)
		{
			//2번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_2
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_2] == false)
			{
				cout << "2번 스킬 발동" << endl;
				//m_bSkill_CutDownKey_check[CK_2] = true;
			}
		}
	}
	else if (GETS(CKeyMgr)->OnceKeyUp(0x32))
	{
		m_bSkill_CutDownKey_check[CK_2] = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown(0x33))
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();

		for (iter; iter != iter_End; ++iter)
		{
			//3번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_3
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_3] == false)
			{
				cout << "3번 스킬 발동" << endl;
				//m_bSkill_CutDownKey_check[CK_3] = true;
			}
		}
	}
	else if (GETS(CKeyMgr)->OnceKeyUp(0x33))
	{
		m_bSkill_CutDownKey_check[CK_3] = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown(0x34))
	{
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();

		for (iter; iter != iter_End; ++iter)
		{
			//4번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_4
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_4] == false)
			{
				cout << "4번 스킬 발동" << endl;
				//m_bSkill_CutDownKey_check[CK_4] = true;
			}
		}
	}
	else if (GETS(CKeyMgr)->OnceKeyUp(0x34))
	{
		m_bSkill_CutDownKey_check[CK_4] = false;
	}
}

void CUi_QuickSlot::QuickSlot_SkillIcon_CoolTime(void)
{
	SKILLITER iter = m_QuickSlot_SkillList.begin();
	SKILLITER iter_End = m_QuickSlot_SkillList.end();

	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->Get_Skill_Icon_Check() == true)
		{
			if (m_bSkill_CutDownKey_check[(*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey])
			{
				//Skill Icon의 단축기가 눌렸을때 Cool Time 시간 동안 활성화.
				//이렇게 하면 안된다. 각각 Skill Icon이 시간을 가지고 있어야 된다.
				//Skill struct 부터 건드리자!!!
				m_dwTime = GetTickCount();

				if (m_dwTime > (*iter)->Get_Skill_Icon_Info()->m_fSkill_CoolTime)
				{
					m_dwTime = 0;
					m_bSkill_CutDownKey_check[(*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey] = false;
					(*iter)->Set_Skill_Icon_Check(true);
				}
				else
				{
					(*iter)->Set_Skill_Icon_Check(false);
				}
			}
		}
	}
}
#pragma endregion

#pragma region 기능 변경 후 필요 없는 부분.
/*
void CUi_QuickSlot::QuickSlot_Drag_SkillIcon(void)
{
	//Quick Slot에 있는 Skill Icon Drag 기능

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
				if (PtInRect((*iter_Slot)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
				{
					if ((*iter_Slot)->Get_SlotNumber() == (*iter)->Get_Skill_Icon_QuickNumber())
					{
						m_pSelect_SkillIcon = (*iter);
						break;
					}
				}
			}
		}
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
			m_bSkill_Icon_SwapCheck = false;
			m_bSkill_Icon_DragCheck = false;
			m_bSkill_Icon_DropCheck = true;

			//Skill Icon이 Slot에서 벗어 났을 때 선택된 스킬 아이콘을 지운다.
			QuickSlot_Escape_SkillIcon();
		}
	}

	if (m_bSkill_Icon_DragCheck == true && m_bSkill_Icon_DropCheck == false)
	{
		//Skill Drag 움직임
		if (m_pSelect_SkillIcon != NULL)
			m_pSelect_SkillIcon->SetPos(pt.x - (m_pSelect_SkillIcon->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_SkillIcon->GetInfo()->fcy / 2.f));
	}
}

void CUi_QuickSlot::QuickSlot_Escape_SkillIcon(void)
{
	//선택된 Skill Icon이 Quick Slot의 어느 Rect에도 충돌 되지 않았을때
	//Skill Icon 삭제 하는 함수.

	SLOTITER iter = m_QuickSlot_List.begin();
	SLOTITER iter_End = m_QuickSlot_List.end();
	RECT rc;

	if (m_bSkill_Icon_DropCheck == true)
	{
		if (m_pSelect_SkillIcon != NULL)
		{
			for (iter; iter != iter_End; ++iter)
			{
				if (!IntersectRect(&rc, (*iter)->GetRect(), m_pSelect_SkillIcon->GetRect()))
				{
					m_bSkill_Icon_EscapeCheck = true;

					//충돌 되지 않았을때.
					SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
					SKILLITER iter_Skill_End = m_QuickSlot_SkillList.end();
					for (iter_Skill; iter_Skill != iter_Skill_End; )
					{
						if ((*iter_Skill)->Get_Skill_Icon_QuickNumber() == m_pSelect_SkillIcon->Get_Skill_Icon_QuickNumber())
						{
							m_QuickSlot_SkillList.erase(iter_Skill);
							iter_Skill = m_QuickSlot_SkillList.begin();
						}
						else
							++iter_Skill;
					}

					m_bSkill_Icon_DropCheck = false;
				}
			}
		}
	}
}

void CUi_QuickSlot::QuickSlot_Drop_Swap_SkillIcon(void)
{
	//Skill Icon을 Drop 했을때 list 안에 있는 Skill 아이콘을 지운다.
	//Skill Icon을 Drop 시 Slot과 충돌되면 Swap 한다.

	if (m_bSkill_Icon_DropCheck == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
	{
		//iter가 없는 값으로 나와서 안된다... 이거 찾아야 된다.

		SLOTITER  iter_Slot = m_QuickSlot_List.begin();
		SLOTITER  iter_Slot_End = m_QuickSlot_List.end();
		SKILLITER iter = m_QuickSlot_SkillList.begin();
		SKILLITER iter_End = m_QuickSlot_SkillList.end();
		SKILLITER iter_Select;								//선택된 Skill Icon의 List에서의 위치.
		CSkill_Icon* pTemp = NULL;
		RECT rc;

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if (IntersectRect(&rc, m_pSelect_SkillIcon->GetRect(), (*iter_Slot)->GetRect()))
				m_bSkill_Icon_SwapCheck = true;

			if (m_bSkill_Icon_SwapCheck == true)
			{
				//Swap 기능

				//자기 자신일때는 Swap 안되게 예외처리
				//if ((*iter_Slot)->Get_SlotNumber() == m_pSelect_SkillIcon->Get_Skill_Icon_QuickNumber())
				//break;

				//Find Select Skill Icon Iterator
				for (iter; iter != iter_End; ++iter)
				{
					if ((*iter)->Get_Skill_Icon_Num() == m_pSelect_SkillIcon->Get_Skill_Icon_Num())
					{
						iter_Select = iter;
						break;
					}
				}

				if ((*iter_Select) != NULL)
				{
					iter = m_QuickSlot_SkillList.begin();
					iter_End = m_QuickSlot_SkillList.end();
					for (iter; iter != iter_End;)
					{
						if ((*iter_Slot)->Get_SlotNumber() == (*iter_Select)->Get_Skill_Icon_QuickNumber())
						{
							//pTemp Allocate
							SKILL tSkill;
							ZeroMemory(&tSkill, sizeof(SKILL));
							memcpy_s(&tSkill, sizeof(SKILL), (*iter_Select)->Get_Skill_Icon_Info(), sizeof(SKILL));

							pTemp = new CSkill_Icon();
							pTemp->Set_Skill_Icon_Info(tSkill);
							pTemp->Set_Skill_Icon_Num((*iter_Select)->Get_Skill_Icon_Num());
							pTemp->SetSize(32.f, 32.f);
							pTemp->Set_Skill_Icon_QuickNumber((*iter_Select)->Get_Skill_Icon_QuickNumber());
							pTemp->Set_Skill_Icon_QuickSetCheck(true);
							pTemp->Set_Skill_Icon_Check(true);

							//Select Skill Icon Input
							m_pSelect_SkillIcon->Set_Skill_Icon_QuickNumber((*iter)->Get_Skill_Icon_QuickNumber());
							m_QuickSlot_SkillList.insert(iter, m_pSelect_SkillIcon);

							//Temp Skill Icon Input
							m_QuickSlot_SkillList.insert(iter_Select, pTemp);

							//Replace Skill Icon Erase
							m_QuickSlot_SkillList.erase(iter);
							iter = m_QuickSlot_SkillList.begin();

							m_QuickSlot_SkillList.erase(iter_Select);
							iter = m_QuickSlot_SkillList.begin();

							m_bSkill_Icon_SwapCheck = false;
							break;
						}
						else
							++iter;
					}
				}

				m_bSkill_Icon_DropCheck = false;
			}
			else if (m_bSkill_Icon_SwapCheck == false)
			{
				//Drop 기능

				iter = m_QuickSlot_SkillList.begin();
				iter_End = m_QuickSlot_SkillList.end();
				for (iter; iter != iter_End;)
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
	}
}

void CUi_QuickSlot::QuickSlot_Swap_SkillIcon(void)
{
	if (m_bSkill_Icon_DropCheck == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
	{
		SLOTITER iter_Slot = m_QuickSlot_List.begin();
		SLOTITER iter_Slot_End = m_QuickSlot_List.end();

		CSkill_Icon* pTemp = NULL;
		RECT rc;

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if (IntersectRect(&rc, m_pSelect_SkillIcon->GetRect(), (*iter_Slot)->GetRect()))
			{
				m_bSkill_Icon_SwapCheck = true;

				SKILLITER iter_Skill = m_QuickSlot_SkillList.begin();
				SKILLITER iter_Skill_End = m_QuickSlot_SkillList.begin();
				SKILLITER iter_Select;

				if ((*iter_Slot)->Get_SlotNumber() == m_pSelect_SkillIcon->Get_Skill_Icon_QuickNumber())
					break;

				//Find Select Skill Icon Iterator
				for (iter_Skill; iter_Skill != iter_Skill_End; ++iter_Skill)
				{
					if (lstrcmp((*iter_Skill)->Get_Skill_Icon_Info()->m_szName, m_pSelect_SkillIcon->Get_Skill_Icon_Info()->m_szName))
					{
						iter_Select = iter_Skill;
						break;
					}
				}

				iter_Skill = m_QuickSlot_SkillList.begin();
				iter_Skill_End = m_QuickSlot_SkillList.begin();
				for (iter_Skill; iter_Skill != iter_Skill_End;)
				{
					if ((*iter_Slot)->Get_SlotNumber() == (*iter_Select)->Get_Skill_Icon_QuickNumber() && m_bSkill_Icon_SwapCheck == false)
					{
						//pTemp Allocate
						SKILL tSkill;
						ZeroMemory(&tSkill, sizeof(SKILL));
						memcpy_s(&tSkill, sizeof(SKILL), (*iter_Select)->Get_Skill_Icon_Info(), sizeof(SKILL));

						pTemp = new CSkill_Icon();
						pTemp->Set_Skill_Icon_Info(tSkill);
						pTemp->Set_Skill_Icon_Num((*iter_Select)->Get_Skill_Icon_Num());
						pTemp->SetSize(32.f, 32.f);
						pTemp->Set_Skill_Icon_QuickNumber((*iter_Select)->Get_Skill_Icon_QuickNumber());
						pTemp->Set_Skill_Icon_QuickSetCheck(true);
						pTemp->Set_Skill_Icon_Check(true);

						//Select Skill Icon Input
						m_pSelect_SkillIcon->Set_Skill_Icon_QuickNumber((*iter_Skill)->Get_Skill_Icon_QuickNumber());
						m_QuickSlot_SkillList.insert(iter_Skill, m_pSelect_SkillIcon);

						//Temp Skill Icon Input
						m_QuickSlot_SkillList.insert(iter_Select, pTemp);

						//Replace Skill Icon Erase
						m_QuickSlot_SkillList.erase(iter_Skill);
						iter_Skill = m_QuickSlot_SkillList.begin();

						m_QuickSlot_SkillList.erase(iter_Select);
						iter_Skill = m_QuickSlot_SkillList.begin();
					}
					else
						++iter_Skill;
				}

				m_bSkill_Icon_DropCheck = false;
			}
		}
	}
}
*/
#pragma endregion

#pragma region Quick Slot Render
void CUi_QuickSlot::QuickSlot_Skill_Icon_Render(HDC _dc)
{
	TCHAR szOn[30] = L"_Icon_On";
	TCHAR szIcon_Name[50] = L"";
	TCHAR szOff[30] = L"_Icon_Off";
	TCHAR szIcon_OffName[50] = L"";

	SKILLITER iter = m_QuickSlot_SkillList.begin();
	SKILLITER iter_End = m_QuickSlot_SkillList.end();

	for (iter; iter != iter_End; ++iter)
	{
		//Icon Off Render
		lstrcpy(szIcon_OffName, (*iter)->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_OffName, szOff);

		if ((*iter)->Get_Skill_Icon_Check() == false)
		{
			TransparentBlt(_dc,
				int((*iter)->GetInfo()->fx), int((*iter)->GetInfo()->fy),
				int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_OffName)->GetMemDC(),
				0, 0,
				int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
				RGB(255, 255, 255));
		}

		//Icon On Render
		lstrcpy(szIcon_Name, (*iter)->Get_Skill_Icon_Info()->m_szName);
		lstrcat(szIcon_Name, szOn);

		if ((*iter)->Get_Skill_Icon_Check() == true)
		{
			TransparentBlt(_dc,
				int((*iter)->GetInfo()->fx), int((*iter)->GetInfo()->fy),
				int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
				GETS(CBitMapMgr)->FindImage(szIcon_Name)->GetMemDC(),
				0, 0,
				int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
				RGB(255, 255, 255));
		}
	}
}
#pragma endregion