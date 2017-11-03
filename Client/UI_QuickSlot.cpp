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
#include "Stat.h"

//Item
#include "Item.h"
#include "Potion.h"

typedef list<CQuick_Slot*>::iterator SLOTITER;
typedef list<CSkill_Icon*>::iterator SKILLITER;
typedef list<CItem*>::iterator		 ITEMITER;

CUi_QuickSlot::CUi_QuickSlot(void)
{
	m_eUiType = UI_QUICKSLOT;
	m_pSelect_SkillIcon = NULL;

	for (int i = 0; i < CK_END; ++i)
		m_bSkill_CutDownKey_check[i] = false;
	for (int i = 0; i < 4; ++i)
		m_bSkill_Cool_TimeCheck[i] = false;
	m_bSkill_Icon_pushCheck = false;
	m_bItem_Icon_pushCheck = false;
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

	//Skill Icon
	QuickSlot_Set_SkillIcon();
	QuickSlot_Set_SkillIcon_Position();
	QuickSlot_Set_SkillIcon_Active();
	QuickSlot_Set_SkillIcon_CutDownKey();
	QuickSlot_SkillIcon_CoolTime();

	//Item Icon
	QuickSlot_Set_ItemIcon();
	QuickSlot_Set_ItemIcon_Position();
	QuickSlot_Set_ItemIcon_CutDownKey();

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
	QuickSlot_Item_Icon_Render(_dc);
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

	ITEMITER iter_Item = m_QuickSlot_ItemList.begin();
	ITEMITER iter_Item_End = m_QuickSlot_ItemList.end();
	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
	{
		SAFE_DELETE(*iter_Item);
	}
	m_QuickSlot_ItemList.clear();
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

			//이미 쿨타임 중이면 단축기 안먹게 하기.
			if ((*iter)->Get_Skill_Icon_Num() == 0 && (*iter)->Get_Skill_Icon_Check() == false)
				break;

			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_1
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_1] == false)
			{
				cout << "1번 스킬 발동" << endl;
				m_bSkill_CutDownKey_check[CK_1] = true;
				break;
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
			//이미 쿨타임 중이면 단축기 안먹게 하기.
			if ((*iter)->Get_Skill_Icon_Num() == 1 && (*iter)->Get_Skill_Icon_Check() == false)
				break;

			//2번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_2
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_2] == false)
			{
				cout << "2번 스킬 발동" << endl;
				m_bSkill_CutDownKey_check[CK_2] = true;
				break;
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
			//이미 쿨타임 중이면 단축기 안먹게 하기.
			if ((*iter)->Get_Skill_Icon_Num() == 2 && (*iter)->Get_Skill_Icon_Check() == false)
				break;

			//3번 숫자키 클릭시
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_3
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_3] == false)
			{
				cout << "3번 스킬 발동" << endl;
				m_bSkill_CutDownKey_check[CK_3] = true;
				break;
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
			//이미 쿨타임 중이면 단축기 안먹게 하기.
			if ((*iter)->Get_Skill_Icon_Num() == 3 && (*iter)->Get_Skill_Icon_Check() == false)
				break;

			//4번 숫자키 클릭시 
			if ((*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey == CK_4
				&& (*iter)->Get_Skill_Icon_Check() == true
				&& m_bSkill_CutDownKey_check[CK_4] == false)
			{
				cout << "4번 스킬 발동" << endl;
				m_bSkill_CutDownKey_check[CK_4] = true;
				break;
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
			if (m_bSkill_CutDownKey_check[(*iter)->Get_Skill_Icon_Info()->m_eSkill_CutDownKey] == true)
			{
				//Skill Icon의 단축기가 눌렸을때 Cool Time 시간 동안 활성화.
				//Skill 구조체의 m_dwSkill_CoolTime_Prs 값을 계속해서 증가한 다음에
				//그 값에 Cool Time 값을 비교해야 된다. 안된다!!!!
				if ((*iter)->Get_Skill_Icon_Num() == 0 && m_bSkill_Cool_TimeCheck[0] == false)
				{
					m_bSkill_Cool_TimeCheck[0] = true;
					break;
				}
				else if ((*iter)->Get_Skill_Icon_Num() == 1 && m_bSkill_Cool_TimeCheck[1] == false)
				{
					m_bSkill_Cool_TimeCheck[1] = true;
					break;
				}
				else if ((*iter)->Get_Skill_Icon_Num() == 2 && m_bSkill_Cool_TimeCheck[2] == false)
				{
					m_bSkill_Cool_TimeCheck[2] = true;
					break;
				}
				else if ((*iter)->Get_Skill_Icon_Num() == 3 && m_bSkill_Cool_TimeCheck[3] == false)
				{
					m_bSkill_Cool_TimeCheck[3] = true;
					break;
				}
			}
		}
	}

	if (m_bSkill_Cool_TimeCheck[0] == true)
	{
		/*
			각각의 Skill Icon에 m_dwSkill_Prs_Time 을 + 1 해주면서 
			Skill의 Skill_CoolTime을 넘기는지 체크 하는 부분.
			
			스킬 쿨 타임 중이라면 Skill_Icon_Check 부분을 false로 처리
			false 이면 스킬 나가지 않게 나중에 처리 해야 된다.
		*/

		iter = m_QuickSlot_SkillList.begin();
		iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->Get_Skill_Icon_Num() == 0)
			{
				(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time = GetTickCount();

				if ((*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time > (*iter)->Get_Skill_Icon_Info()->m_fSkill_CoolTime)
				{
					(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time = 0;
					(*iter)->Set_Skill_Icon_Check(true);

					m_bSkill_Cool_TimeCheck[0] = false;
					break;
				}
				else
				{
					(*iter)->Set_Skill_Icon_Check(false);
				}
			}
		}
	}
	else if (m_bSkill_Cool_TimeCheck[1] == true)
	{
		iter = m_QuickSlot_SkillList.begin();
		iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->Get_Skill_Icon_Num() == 1)
			{
				(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time += 1;

				if ((*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time > (*iter)->Get_Skill_Icon_Info()->m_fSkill_CoolTime)
				{
					(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time = 0;
					(*iter)->Set_Skill_Icon_Check(true);

					m_bSkill_Cool_TimeCheck[1] = false;
					break;
				}
				else
				{
					(*iter)->Set_Skill_Icon_Check(false);
				}
			}
		}
	}
	else if (m_bSkill_Cool_TimeCheck[2] == true)
	{
		iter = m_QuickSlot_SkillList.begin();
		iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->Get_Skill_Icon_Num() == 2)
			{
				(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time += 1;

				if ((*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time > (*iter)->Get_Skill_Icon_Info()->m_fSkill_CoolTime)
				{
					(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time = 0;
					(*iter)->Set_Skill_Icon_Check(true);

					m_bSkill_Cool_TimeCheck[2] = false;
					break;
				}
				else
				{
					(*iter)->Set_Skill_Icon_Check(false);
				}
			}
		}
	}
	else if (m_bSkill_Cool_TimeCheck[3] == true)
	{
		iter = m_QuickSlot_SkillList.begin();
		iter_End = m_QuickSlot_SkillList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->Get_Skill_Icon_Num() == 3)
			{
				(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time += 1;

				if ((*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time > (*iter)->Get_Skill_Icon_Info()->m_fSkill_CoolTime)
				{
					(*iter)->Get_Skill_Icon_Info()->m_dwSkill_Prs_Time = 0;
					(*iter)->Set_Skill_Icon_Check(true);

					m_bSkill_Cool_TimeCheck[3] = false;
					break;
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

#pragma region QuickSlot Item Icon Function
void CUi_QuickSlot::QuickSlot_Set_ItemIcon(void)
{
	/*
		Inven Item을 Quick Slot Item List에 등록하는 함수.
	*/

	//Inven Pointer Variable Setting
	CInven* pInven = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = (CInven*)(*iter);
			break;
		}
	}

	if (pInven != NULL && m_bItem_Icon_pushCheck == false)
	{
		if (pInven->GetInevn_ConsumeItemList()->empty() != 1)
		{
			ITEMITER iter_Inven = pInven->GetInevn_ConsumeItemList()->begin();
			ITEMITER iter_Inven_End = pInven->GetInevn_ConsumeItemList()->end();
			for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
			{
				//아이템이 처음 할당 시킨 다음 그다음 부터는 갯수를 올려야 된다.
				static int	iHpPotion_Count = 1;
				static int  iMpPotion_Count = 1;

				if ((*iter_Inven)->GetItemData()->m_dwOption == 11)
				{
					//Item Check (Quick Slot)
					ITEMITER iter = m_QuickSlot_ItemList.begin();
					ITEMITER iter_End = m_QuickSlot_ItemList.end();
					for (iter; iter != iter_End; ++iter)
					{
						if ((*iter)->GetItemData()->m_dwOption == 11)
						{
							++iHpPotion_Count;
							(*iter)->SetItem_Count(iHpPotion_Count);
							break;
						}
					}

					//Allocate HpPotion
					static bool bAllocate_Check = false;
					if (bAllocate_Check == false)
					{
						CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
						((CPotion*)pPotion)->Initialize();
						((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
						pPotion->SetItemDescription(L"생명력 포션");
						pPotion->SetItem_Count(iHpPotion_Count);
						m_QuickSlot_ItemList.push_back(pPotion);

						bAllocate_Check = true;
					}
				}
				else if ((*iter_Inven)->GetItemData()->m_dwOption == 12)
				{
					//Item Check (Quick Slot)
					ITEMITER iter = m_QuickSlot_ItemList.begin();
					ITEMITER iter_End = m_QuickSlot_ItemList.end();
					for (iter; iter != iter_End; ++iter)
					{
						if ((*iter)->GetItemData()->m_dwOption == 12)
						{
							++iHpPotion_Count;
							(*iter)->SetItem_Count(iHpPotion_Count);
							break;
						}
					}

					//Allocate MpPotion
					static bool bAllocate_Check = false;
					if (bAllocate_Check == false)
					{
						CItem* pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
						((CPotion*)pPotion)->Initialize();
						((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
						pPotion->SetItemDescription(L"마나 포션");
						pPotion->SetItem_Count(iMpPotion_Count);
						m_QuickSlot_ItemList.push_back(pPotion);

						bAllocate_Check = true;
					}
				}
			}

			m_bItem_Icon_pushCheck = true;
		}
	}
}

void CUi_QuickSlot::QuickSlot_Set_ItemIcon_Position(void)
{
	/*
		Item List Postion Setting
	*/

	ITEMITER iter = m_QuickSlot_ItemList.begin();
	ITEMITER iter_End = m_QuickSlot_ItemList.end();

	for (iter; iter != iter_End; ++iter)
	{
		SLOTITER iter_Slot = m_QuickSlot_List.begin();
		SLOTITER iter_Slot_End = m_QuickSlot_List.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if ((*iter_Slot)->Get_SlotNumber() == 4)
			{
				if ((*iter)->GetItemData()->m_dwOption == 11)
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
			}
			else if ((*iter_Slot)->Get_SlotNumber() == 5)
			{
				if ((*iter)->GetItemData()->m_dwOption == 12)
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
			}
		}
	}
}

void CUi_QuickSlot::QuickSlot_Set_ItemIcon_CutDownKey(void)
{
	/*
		Item CutDown Key Setting
		0x46 : F key
		0x47 : G Key
	*/

	//ObjMgr 에서 Stat 가져오기
	CStat* pStat = NULL;
	CInven* pInven = NULL;
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_STAT)
		{
			pStat = (CStat*)(*iter);
			break;
		}
	}
	iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = (CInven*)(*iter);
			break;
		}
	}

	if (GETS(CKeyMgr)->OnceKeyDown(0x46))
	{
		//F Key : Hp Potion Using
		ITEMITER iter = m_QuickSlot_ItemList.begin();
		ITEMITER iter_End = m_QuickSlot_ItemList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->GetItemData()->m_dwOption == 11)
			{
				if ((*iter)->GetItemData()->m_iCount > 0)
				{
					//Item Count가 1개 이상일때 Count Setting
					//Quick Slot
					int iCount = (*iter)->GetItemData()->m_iCount;
					--iCount;
					(*iter)->SetItem_Count(iCount);

					//Inven Item List에도 조정.
					if (pInven != NULL)
					{
						ITEMITER iter_Inven = pInven->GetInevn_ConsumeItemList()->begin();
						ITEMITER iter_Inven_End = pInven->GetInevn_ConsumeItemList()->end();
						for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
						{
							if ((*iter_Inven)->GetItemData()->m_dwOption == 11)
							{
								(*iter_Inven)->SetItem_Count(iCount);
								break;
							}
						}
					}

					//Using Hp Potion Function(Player Hp 채우기)
					QucikSlot_Potion_Using(pStat, (*iter), (*iter)->GetItemData()->m_dwOption);
					break;
				}
			}
		}
	}
	if(GETS(CKeyMgr)->OnceKeyDown(0x47))
	{
		//G Key : Mp Potion Using
		ITEMITER iter = m_QuickSlot_ItemList.begin();
		ITEMITER iter_End = m_QuickSlot_ItemList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->GetItemData()->m_dwOption == 12)
			{
				if ((*iter)->GetItemData()->m_iCount > 0)
				{
					//Item Count가 1개 이상일때 Count Setting
					int iCount = (*iter)->GetItemData()->m_iCount;
					--iCount;
					(*iter)->SetItem_Count(iCount);

					//Inven Item List에도 조정.
					if (pInven != NULL)
					{
						ITEMITER iter_Inven = pInven->GetInevn_ConsumeItemList()->begin();
						ITEMITER iter_Inven_End = pInven->GetInevn_ConsumeItemList()->end();
						for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
						{
							if ((*iter_Inven)->GetItemData()->m_dwOption == 12)
							{
								(*iter_Inven)->SetItem_Count(iCount);
								break;
							}
						}
					}

					//Using Mp Potion Function(Player Mp 채우기)
					QucikSlot_Potion_Using(pStat, (*iter), (*iter)->GetItemData()->m_dwOption);
					break;
				}
			}
		}
	}
}

void CUi_QuickSlot::QucikSlot_Potion_Using(CStat * _pStat, CItem* _pItem, DWORD _dwOption)
{
	if (_dwOption == 11)
	{
		//Hp Potion
		if (_pStat->Get_PlayerStat()->m_iHp >= _pStat->Get_PlayerStat()->m_iMaxHp)
		{
			//Max Hp에 비해 Hp가 같거나 크면
			_pStat->Set_PlayerHp(_pStat->Get_PlayerStat()->m_iMaxHp);
		}
		else if (_pStat->Get_PlayerStat()->m_iHp <  _pStat->Get_PlayerStat()->m_iMaxHp)
		{
			//Max Hp 보다 Hp가 작으면
			int iHp_Gap = _pStat->Get_PlayerStat()->m_iMaxHp - _pStat->Get_PlayerStat()->m_iHp;
			
			//HpGap이 Hp Potion 회복량 보다 작으면 HpGap 만큼 회복
			//HpGap이 Hp Potion 회복량 보다 크면 회복량 만큼 회복.
			if (iHp_Gap <= 1000)
			{
				int iHp = _pStat->Get_PlayerStat()->m_iHp;
				iHp += iHp_Gap;
				_pStat->Set_PlayerHp(iHp);
			}
			else
			{
				int iHp = _pStat->Get_PlayerStat()->m_iHp;
				iHp += _pItem->GetItemData()->m_iHp;
				_pStat->Set_PlayerHp(iHp);
			}
		}
	}
	else if (_dwOption == 12)
	{
		//Mp Potion
		if (_pStat->Get_PlayerStat()->m_iMp >= _pStat->Get_PlayerStat()->m_iMaxMp)
		{
			//Max Hp에 비해 Hp가 같거나 크면
			_pStat->Set_PlayerMp(_pStat->Get_PlayerStat()->m_iMaxMp);
		}
		else if (_pStat->Get_PlayerStat()->m_iMp <  _pStat->Get_PlayerStat()->m_iMaxMp)
		{
			//Max Mp 보다 Mp가 작으면
			int iMp_Gap = _pStat->Get_PlayerStat()->m_iMaxMp - _pStat->Get_PlayerStat()->m_iMp;

			//MpGap이 Mp Potion 회복량 보다 작으면 MpGap 만큼 회복
			//MpGap이 Mp Potion 회복량 보다 크면 회복량 만큼 회복.
			if (iMp_Gap <= 1000)
			{
				int iMp = _pStat->Get_PlayerStat()->m_iMp;
				iMp += iMp_Gap;
				_pStat->Set_PlayerMp(iMp);
			}
			else
			{
				int iMp = _pStat->Get_PlayerStat()->m_iMp;
				iMp += _pItem->GetItemData()->m_iMp;
				_pStat->Set_PlayerMp(iMp);
			}
		}
	}
}
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

void CUi_QuickSlot::QuickSlot_Item_Icon_Render(HDC _dc)
{
	/*
		Item Icon Render & Item Count Render(카운트 갯수는 Inven과 실시간 연동.
	*/
	ITEMITER iter = m_QuickSlot_ItemList.begin();
	ITEMITER iter_End = m_QuickSlot_ItemList.end();
	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->GetItemData()->m_dwOption == 11)
		{
			//Hp Potion
			if((*iter)->GetItemData()->m_iCount > 0)
				(*iter)->Render(_dc);
			else if ((*iter)->GetItemData()->m_iCount == 0)
			{
				TransparentBlt(_dc,
					int((*iter)->GetInfo()->fx), int((*iter)->GetInfo()->fy),
					int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
					GETS(CBitMapMgr)->FindImage(L"Hp_Potion_Nothing")->GetMemDC(),
					0, 0,
					int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
					RGB(0, 0, 0));
			}
		}
		else if ((*iter)->GetItemData()->m_dwOption == 12)
		{
			//Mp Potion
			if ((*iter)->GetItemData()->m_iCount > 0)
				(*iter)->Render(_dc);
			else if ((*iter)->GetItemData()->m_iCount == 0)
			{
				TransparentBlt(_dc,
					int((*iter)->GetInfo()->fx), int((*iter)->GetInfo()->fy),
					int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
					GETS(CBitMapMgr)->FindImage(L"Mp_Potion_Nothing")->GetMemDC(),
					0, 0,
					int((*iter)->GetInfo()->fcx), int((*iter)->GetInfo()->fcy),
					RGB(0, 0, 0));
			}
		}
	}
}
#pragma endregion