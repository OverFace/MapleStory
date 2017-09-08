#include "stdafx.h"
#include "Inven.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "Slot.h"
#include "Player.h"

//Item----------------------------
#include "Npc.h"
#include "Item.h"
#include "Armor.h"
#include "Glove.h"
#include "Accessory.h"
#include "Helmet.h"
#include "Shoes.h"
#include "Potion.h"
#include "Weapon.h"
//--------------------------------

typedef list<CItem*>::iterator ITEMITER;
typedef list<CSlot*>::iterator SLOTITER;

CInven::CInven(void)
{
	m_eUiType = UI_INVEN;
	m_dwTime = 0;

	ZeroMemory(&m_tInvenMove_Rect, sizeof(RECT));
	ZeroMemory(&m_tInvenEquip_Rect, sizeof(RECT));
	ZeroMemory(&m_tInvenConsume_Rect, sizeof(RECT));
	ZeroMemory(&m_tInvenEtc_Rect, sizeof(RECT));
	for (int i = 0; i < 3; ++i)
		ZeroMemory(&m_tInvenSelect_Info[i], sizeof(INFO));
	ZeroMemory(&m_tInven_EscButton_Rect, sizeof(RECT));
	ZeroMemory(&m_tInven_EscButton_Info, sizeof(INFO));

	m_bStoreInven_Check = false;
	m_bInvenItem_CreateCheck = false;
	m_bInvenMoveCheck = false;
	m_bInvenItem_DragCheck = false;
	m_bInvenItem_SwapCheck = false;
	m_bInvenItem_DropCheck = false;
	m_bInvenMode[INVEN_EQUIP] = true;
	for (int i = 1; i < INVEN_END; ++i)
		m_bInvenMode[i] = false;

	m_pSelect_Item = NULL;
	m_pSelect_Slot = NULL;
}

CInven::~CInven(void)
{
	Save_InvenData();
	Release();
}

void CInven::Initialize(void)
{
	m_tInfo.fx = 460.f;
	m_tInfo.fy = 160.f;
	m_tInfo.fcx = 172.f;
	m_tInfo.fcy = 335.f;
	m_eRenderType = RENDER_UI;

	//Load Inven Item Data
	Load_InvenData();

	//Inven Equip
	m_tInvenSelect_Info[0].fx = m_tInfo.fx + 9.f;
	m_tInvenSelect_Info[0].fy = m_tInfo.fy + 26.f;
	m_tInvenSelect_Info[0].fcx = 30.f;
	m_tInvenSelect_Info[0].fcy = 20.f;

	//Inven Consume
	m_tInvenSelect_Info[1].fx = m_tInfo.fx + 40.f;
	m_tInvenSelect_Info[1].fy = m_tInfo.fy + 26.f;
	m_tInvenSelect_Info[1].fcx = 30.f;
	m_tInvenSelect_Info[1].fcy = 20.f;

	//Inven Etc
	m_tInvenSelect_Info[2].fx = m_tInfo.fx + 71.f;
	m_tInvenSelect_Info[2].fy = m_tInfo.fy + 26.f;
	m_tInvenSelect_Info[2].fcx = 30.f;
	m_tInvenSelect_Info[2].fcy = 20.f;

	//Inven Esc Button
	m_tInven_EscButton_Info.fx = m_tInfo.fx + 150.f;
	m_tInven_EscButton_Info.fy = m_tInfo.fy + 8.f;
	m_tInven_EscButton_Info.fcx = 12.f;
	m_tInven_EscButton_Info.fcy = 12.f;

	//Inven Slot
	Inven_SlotCreate();

	m_dwTime = GetTickCount();
}

int CInven::Update(void)
{
	//Inven Move Rect
	m_tInvenMove_Rect.left		= long(m_tInfo.fx + (172.f - 12.f / 2.f) - 172.f - 12.f / 2.f);
	m_tInvenMove_Rect.right		= long(m_tInfo.fx + (172.f - 12.f / 2.f) + 172.f - 12.f / 2.f);
	m_tInvenMove_Rect.top		= long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
	m_tInvenMove_Rect.bottom	= long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);

	//Inven Equip & Consume & Etc Rect
	m_tInvenSelect_Info[0].fx = m_tInfo.fx + 9.f;
	m_tInvenSelect_Info[0].fy = m_tInfo.fy + 26.f;
	m_tInvenEquip_Rect.left		= long(m_tInvenSelect_Info[0].fx + (m_tInvenSelect_Info[0].fcx / 2.f) - m_tInvenSelect_Info[0].fcx / 2.f);
	m_tInvenEquip_Rect.right	= long(m_tInvenSelect_Info[0].fx + (m_tInvenSelect_Info[0].fcx / 2.f) + m_tInvenSelect_Info[0].fcx / 2.f);
	m_tInvenEquip_Rect.top		= long(m_tInvenSelect_Info[0].fy + (m_tInvenSelect_Info[0].fcy / 2.f) - m_tInvenSelect_Info[0].fcy / 2.f);
	m_tInvenEquip_Rect.bottom	= long(m_tInvenSelect_Info[0].fy + (m_tInvenSelect_Info[0].fcy / 2.f) + m_tInvenSelect_Info[0].fcy / 2.f);

	m_tInvenSelect_Info[1].fx = m_tInfo.fx + 40.f;
	m_tInvenSelect_Info[1].fy = m_tInfo.fy + 26.f;
	m_tInvenConsume_Rect.left	= long(m_tInvenSelect_Info[1].fx + (m_tInvenSelect_Info[1].fcx / 2.f) - m_tInvenSelect_Info[1].fcx / 2.f);
	m_tInvenConsume_Rect.right	= long(m_tInvenSelect_Info[1].fx + (m_tInvenSelect_Info[1].fcx / 2.f) + m_tInvenSelect_Info[1].fcx / 2.f);
	m_tInvenConsume_Rect.top	= long(m_tInvenSelect_Info[1].fy + (m_tInvenSelect_Info[1].fcy / 2.f) - m_tInvenSelect_Info[1].fcy / 2.f);
	m_tInvenConsume_Rect.bottom = long(m_tInvenSelect_Info[1].fy + (m_tInvenSelect_Info[1].fcy / 2.f) + m_tInvenSelect_Info[1].fcy / 2.f);

	m_tInvenSelect_Info[2].fx = m_tInfo.fx + 71.f;
	m_tInvenSelect_Info[2].fy = m_tInfo.fy + 26.f;
	m_tInvenEtc_Rect.left		= long(m_tInvenSelect_Info[2].fx + (m_tInvenSelect_Info[2].fcx / 2.f) - m_tInvenSelect_Info[2].fcx / 2.f);
	m_tInvenEtc_Rect.right		= long(m_tInvenSelect_Info[2].fx + (m_tInvenSelect_Info[2].fcx / 2.f) + m_tInvenSelect_Info[2].fcx / 2.f);
	m_tInvenEtc_Rect.top		= long(m_tInvenSelect_Info[2].fy + (m_tInvenSelect_Info[2].fcy / 2.f) - m_tInvenSelect_Info[2].fcy / 2.f);
	m_tInvenEtc_Rect.bottom		= long(m_tInvenSelect_Info[2].fy + (m_tInvenSelect_Info[2].fcy / 2.f) + m_tInvenSelect_Info[2].fcy / 2.f);

	//Inven Esc Button
	m_tInven_EscButton_Info.fx = m_tInfo.fx + 150.f;
	m_tInven_EscButton_Info.fy = m_tInfo.fy + 8.f;
	m_tInven_EscButton_Rect.left	= long(m_tInven_EscButton_Info.fx + (m_tInven_EscButton_Info.fcx / 2.f) - m_tInven_EscButton_Info.fcx / 2.f);
	m_tInven_EscButton_Rect.right	= long(m_tInven_EscButton_Info.fx + (m_tInven_EscButton_Info.fcx / 2.f) + m_tInven_EscButton_Info.fcx / 2.f);
	m_tInven_EscButton_Rect.top		= long(m_tInven_EscButton_Info.fy + (m_tInven_EscButton_Info.fcy / 2.f) - m_tInven_EscButton_Info.fcy / 2.f);
	m_tInven_EscButton_Rect.bottom	= long(m_tInven_EscButton_Info.fy + (m_tInven_EscButton_Info.fcy / 2.f) + m_tInven_EscButton_Info.fcy / 2.f);

	//Key Setting
	Inven_Key();

	if (m_bVisible == true)
	{
		Inven_Move();			//Inven Move
		Inven_SelectMenu();
		Inven_SelectItem();
		Inven_DragItem();
		Inven_SwapItem();
		Inven_EscButton_Click();

		Inven_ItemUpdate();		//Inven Update
	}

	//Slot
	Inven_SlotUpdate();

	return 0;
}

void CInven::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		if (m_bInvenMode[INVEN_EQUIP] == true)
		{
			TransparentBlt(_dc,
				int(m_tInfo.fx), int(m_tInfo.fy),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				GETS(CBitMapMgr)->FindImage(L"Inventory_Equip")->GetMemDC(),
				0, 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(0, 0, 0));
		}
		else if (m_bInvenMode[INVEN_CONSUME] == true)
		{
			TransparentBlt(_dc,
				int(m_tInfo.fx), int(m_tInfo.fy),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				GETS(CBitMapMgr)->FindImage(L"Inventory_Consume")->GetMemDC(),
				0, 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(0, 0, 0));
		}
		else if (m_bInvenMode[INVEN_ETC] == true)
		{
			TransparentBlt(_dc,
				int(m_tInfo.fx), int(m_tInfo.fy),
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				GETS(CBitMapMgr)->FindImage(L"Inventory_Etc")->GetMemDC(),
				0, 0,
				int(m_tInfo.fcx), int(m_tInfo.fcy),
				RGB(0, 0, 0));
		}

		Inven_Item_Render(_dc);
		Inven_Messo_Render(_dc);
		Inven_ConsumeItem_CountRender(_dc);
		//Inven_SlotRender(_dc);		//Slot
	}	
}

void CInven::Release(void)
{	
	ITEMITER iter_Equip = m_Inven_EquipList.begin();
	ITEMITER iter_Consume = m_Inven_ConsumeList.begin();
	ITEMITER iter_Etc = m_Inven_EtcList.begin();
	SLOTITER iter_Slot = m_Inven_SlotList.begin();

	for (iter_Equip; iter_Equip != m_Inven_EquipList.end(); ++iter_Equip)
	{
		SAFE_DELETE(*iter_Equip);
	}
	m_Inven_EquipList.clear();

	for (iter_Consume; iter_Consume != m_Inven_ConsumeList.end(); ++iter_Consume)
	{
		SAFE_DELETE(*iter_Consume);
	}
	m_Inven_ConsumeList.clear();

	for (iter_Etc; iter_Etc != m_Inven_EtcList.end(); ++iter_Etc)
	{
		SAFE_DELETE(*iter_Etc);
	}
	m_Inven_EtcList.clear();

	for (iter_Slot; iter_Slot != m_Inven_SlotList.end(); ++iter_Slot)
	{
		SAFE_DELETE(*iter_Slot);
	}
	m_Inven_SlotList.clear();
}

void CInven::Inven_Key(void)
{
	static bool bIsPress_Inven = false;
	if (GETS(CKeyMgr)->OnceKeyDown('I') && bIsPress_Inven == false)
	{
		if (m_bVisible == true)
			m_bVisible = false;
		else
			m_bVisible = true;

		bIsPress_Inven = true;
	}

	if (m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if (bIsPress_Inven == true)
			bIsPress_Inven = false;
	}
}

void CInven::Inven_Move(void)
{
	//Inven창을 마우스로 움직이게 만드는 함수.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tInvenMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bInvenMoveCheck = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bInvenMoveCheck == true)
		m_bInvenMoveCheck = false;

	if (m_bInvenMoveCheck == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);    //10.f 는 Rect의 y의 / 2 한 값.

		//Inven Move Rect
		m_tInvenMove_Rect.left = long(m_tInfo.fx + (172.f / 2.f) - 172.f / 2.f);
		m_tInvenMove_Rect.right = long(m_tInfo.fx + (172.f / 2.f) + 172.f / 2.f);
		m_tInvenMove_Rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
		m_tInvenMove_Rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);
	}
}

void CInven::Inven_EscButton_Click(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tInven_EscButton_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		m_bVisible = false;
}

#pragma region Inven Slot
void CInven::Inven_SlotCreate(void)
{
	//인벤토리 Slot 만들기
	float fOffsetPosY = 0.f;
	int   iIndex = 0;
	for (int i = 0; i < 24; ++i, ++iIndex)
	{
		CSlot* pSlot = new CSlot();
		pSlot->Initialize();

		//Slot Info & Rect Setting
		if (iIndex == 4)
		{
			iIndex = 0;
			fOffsetPosY += 38.f;
		}

		pSlot->SetPos(m_tInfo.fx + 9.f + (35.f * iIndex), m_tInfo.fy + 52.f + fOffsetPosY);
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetSlotNumber(i);

		m_Inven_SlotList.push_back(pSlot);
	}
}

void CInven::Inven_SlotUpdate(void)
{
	SLOTITER iter_Slot = m_Inven_SlotList.begin();
	float fOffsetPosY = 0.f;
	int   iIndex = 0;

	for (iter_Slot; iter_Slot != m_Inven_SlotList.end(); ++iter_Slot, ++iIndex)
	{
		if (iIndex == 4)
		{
			iIndex = 0;
			fOffsetPosY += 35.f;
		}

		(*iter_Slot)->SetPos(m_tInfo.fx + 9.f + (36.5f * iIndex), m_tInfo.fy + 52.f + fOffsetPosY);
		(*iter_Slot)->Update();
	}		
}

void CInven::Inven_SlotRender(HDC _dc)
{
	SLOTITER iter_Slot = m_Inven_SlotList.begin();
	for (iter_Slot; iter_Slot != m_Inven_SlotList.end(); ++iter_Slot)
		(*iter_Slot)->Render(_dc);
}
#pragma endregion

#pragma region Inven Function
int CInven::Inven_ItemUpdate(void)
{
	ITEMITER iter_Equip = m_Inven_EquipList.begin();
	ITEMITER iter_Consume = m_Inven_ConsumeList.begin();
	ITEMITER iter_Etc = m_Inven_EtcList.begin();

	if (m_bInvenMode[INVEN_EQUIP])
	{
		for (iter_Equip; iter_Equip != m_Inven_EquipList.end(); ++iter_Equip)
			(*iter_Equip)->Update();
	}
	else if (m_bInvenMode[INVEN_CONSUME])
	{
		for (iter_Consume; iter_Consume != m_Inven_ConsumeList.end(); ++iter_Consume)
			(*iter_Consume)->Update();
	}
	else if (m_bInvenMode[INVEN_ETC])
	{
		for (iter_Etc; iter_Etc != m_Inven_EtcList.end(); ++iter_Etc)
			(*iter_Etc)->Update();
	}

	return 0;
}

void CInven::Inven_SelectMenu(void)
{
	//인벤토리의 모드 선텍
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tInvenEquip_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bInvenMoveCheck == false)
	{
		m_bInvenMode[INVEN_EQUIP] = true;
		m_bInvenMode[INVEN_CONSUME] = false;
		m_bInvenMode[INVEN_ETC] = false;
	}
	else if (PtInRect(&m_tInvenConsume_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bInvenMoveCheck == false)
	{
		m_bInvenMode[INVEN_CONSUME] = true;
		m_bInvenMode[INVEN_EQUIP] = false;
		m_bInvenMode[INVEN_ETC] = false;
	}
	else if (PtInRect(&m_tInvenEtc_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bInvenMoveCheck == false)
	{
		m_bInvenMode[INVEN_ETC] = true;
		m_bInvenMode[INVEN_CONSUME] = false;
		m_bInvenMode[INVEN_EQUIP] = false;
	}
}

void CInven::Inven_SelectItem(void)
{
	//인벤토리 아이템 선택
	POINT pt;
	pt = CMouse::GetPos();

	if (m_bInvenMode[INVEN_EQUIP])
	{
		//장비창 모드
		ITEMITER iter = m_Inven_EquipList.begin();
		ITEMITER iter_End = m_Inven_EquipList.end();

		for (iter; iter != iter_End; ++iter)
		{
			if (PtInRect((*iter)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				m_pSelect_Item = (*iter);
			}
		}
	}
	else if (m_bInvenMode[INVEN_CONSUME])
	{
		//소비창 모드
		ITEMITER iter = m_Inven_ConsumeList.begin();
		ITEMITER iter_End = m_Inven_ConsumeList.end();

		for (iter; iter != iter_End; ++iter)
		{
			if (PtInRect((*iter)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				m_pSelect_Item = (*iter);
			}
		}
	}
	else if (m_bInvenMode[INVEN_ETC])
	{
		//기타 모드
		ITEMITER iter = m_Inven_EtcList.begin();
		ITEMITER iter_End = m_Inven_EtcList.end();

		for (iter; iter != iter_End; ++iter)
		{
			if (PtInRect((*iter)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				m_pSelect_Item = (*iter);
			}
		}
	}
}

void CInven::Inven_DragItem(void)
{
	//인벤토리 아이템 드레그
	POINT pt;
	pt = CMouse::GetPos();

	if (m_pSelect_Item != NULL)
	{
		if (m_pSelect_Item->GetRect() && GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON) && m_bInvenMoveCheck == false)
			m_bInvenItem_DragCheck = true;
		else if (m_bInvenItem_DragCheck == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
		{
			m_bInvenItem_SwapCheck = false;		//다시 스왑 가능하게 하기 위애서.
			m_bInvenItem_DragCheck = false;
			m_bInvenItem_DropCheck = true;			
		}
	}

	if (m_bInvenItem_DragCheck == true)
	{
		m_pSelect_Item->SetPos(pt.x - (m_pSelect_Item->GetInfo()->fcx / 2.f), pt.y - (m_pSelect_Item->GetInfo()->fcy / 2.f));
	}
}

void CInven::Inven_SwapItem(void)
{
	//Inven Swap 기능
	if (m_bInvenItem_DropCheck == true && !GETS(CKeyMgr)->StayKeyDown(VK_LBUTTON))
	{
		SLOTITER iter_Slot = m_Inven_SlotList.begin();
		SLOTITER iter_Slot_End = m_Inven_SlotList.end();

		CItem* pTemp = NULL;		
		
		RECT rc;
		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if (IntersectRect(&rc, m_pSelect_Item->GetRect(), (*iter_Slot)->GetRect()))
			{
				if (m_bInvenMode[INVEN_EQUIP])
				{
					ITEMITER iter = m_Inven_EquipList.begin();
					ITEMITER iter_End = m_Inven_EquipList.end();
					ITEMITER iter_Select;

					if ((*iter_Slot)->GetSlotNumber() == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						break;

					for (iter; iter != iter_End; ++iter)
					{
						if ((*iter)->GetItemData()->m_dwInven_SlotNumber == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						{
							iter_Select = iter;
							break;
						}
					}

					iter = m_Inven_EquipList.begin();
					iter_End = m_Inven_EquipList.end();
					for (iter; iter != iter_End;)
					{
						if ((*iter_Slot)->GetSlotNumber() == (*iter)->GetItemData()->m_dwInven_SlotNumber && m_bInvenItem_SwapCheck == false)
						{
							//pTemp Allocate
							pTemp = Inven_ItemSwapClassification((*iter));
							pTemp->SetItem_SlotNumber(m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber);

							//Select Item Input
							m_pSelect_Item->SetItem_SlotNumber((*iter)->GetItemData()->m_dwInven_SlotNumber);
							m_Inven_EquipList.insert(iter, m_pSelect_Item);

							//Temp Item Input
							m_Inven_EquipList.insert(iter_Select, pTemp);

							//Replace Item Erase
							m_Inven_EquipList.erase(iter);
							iter = m_Inven_EquipList.begin();

							m_Inven_EquipList.erase(iter_Select);
							iter = m_Inven_EquipList.begin();
							
							m_bInvenItem_SwapCheck = true;
						}
						else
							++iter;
					}

					m_bInvenItem_DropCheck = false;
					m_bInvenItem_CreateCheck = false;	//아이템 분류하여 새로 생성하기 위해 false 값으로 설정.
				}
				else if (m_bInvenMode[INVEN_CONSUME])
				{
					ITEMITER iter = m_Inven_ConsumeList.begin();
					ITEMITER iter_End = m_Inven_ConsumeList.end();
					ITEMITER iter_Select;

					if ((*iter_Slot)->GetSlotNumber() == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						break;

					for (iter; iter != iter_End; ++iter)
					{
						if ((*iter)->GetItemData()->m_dwInven_SlotNumber == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						{
							iter_Select = iter;
							break;
						}
					}

					iter = m_Inven_ConsumeList.begin();
					iter_End = m_Inven_ConsumeList.end();
					for (iter; iter != iter_End;)
					{
						if ((*iter_Slot)->GetSlotNumber() == (*iter)->GetItemData()->m_dwInven_SlotNumber && m_bInvenItem_SwapCheck == false)
						{
							//pTemp Allocate
							pTemp = Inven_ItemSwapClassification((*iter));
							pTemp->SetItem_SlotNumber(m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber);
							pTemp->SetItem_Count((*iter)->GetItemData()->m_iCount);

							//Select Item Input
							m_pSelect_Item->SetItem_SlotNumber((*iter)->GetItemData()->m_dwInven_SlotNumber);
							m_pSelect_Item->SetItem_Count(m_pSelect_Item->GetItemData()->m_iCount);
							m_Inven_ConsumeList.insert(iter, m_pSelect_Item);

							//Temp Item Input
							m_Inven_ConsumeList.insert(iter_Select, pTemp);

							//Replace Item Erase
							m_Inven_ConsumeList.erase(iter);
							iter = m_Inven_ConsumeList.begin();

							m_Inven_ConsumeList.erase(iter_Select);
							iter = m_Inven_ConsumeList.begin();

							m_bInvenItem_SwapCheck = true;
						}
						else
							++iter;
					}

					m_bInvenItem_DropCheck = false;
					m_bInvenItem_CreateCheck = false;	//아이템 분류하여 새로 생성하기 위해 false 값으로 설정.
				}
				else if (m_bInvenMode[INVEN_ETC])
				{
					ITEMITER iter = m_Inven_EtcList.begin();
					ITEMITER iter_End = m_Inven_EtcList.end();
					ITEMITER iter_Select;

					if ((*iter_Slot)->GetSlotNumber() == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						break;

					for (iter; iter != iter_End; ++iter)
					{
						if ((*iter)->GetItemData()->m_dwInven_SlotNumber == m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber)
						{
							iter_Select = iter;
							break;
						}
					}

					iter = m_Inven_EtcList.begin();
					iter_End = m_Inven_EtcList.end();
					for (iter; iter != iter_End;)
					{
						if ((*iter_Slot)->GetSlotNumber() == (*iter)->GetItemData()->m_dwInven_SlotNumber && m_bInvenItem_SwapCheck == false)
						{
							//pTemp Allocate
							pTemp = Inven_ItemSwapClassification((*iter));
							pTemp->SetItem_SlotNumber(m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber);

							//Select Item Input
							m_pSelect_Item->SetItem_SlotNumber((*iter)->GetItemData()->m_dwInven_SlotNumber);
							m_Inven_EtcList.insert(iter, m_pSelect_Item);

							//Temp Item Input
							m_Inven_EtcList.insert(iter_Select, pTemp);

							//Replace Item Erase
							m_Inven_EtcList.erase(iter);
							iter = m_Inven_EtcList.begin();

							m_Inven_EtcList.erase(iter_Select);
							iter = m_Inven_EtcList.begin();

							m_bInvenItem_SwapCheck = true;
						}
						else
							++iter;
					}

					m_bInvenItem_DropCheck = false;
					m_bInvenItem_CreateCheck = false;	//아이템 분류하여 새로 생성하기 위해 false 값으로 설정.
				}
			}
		}		
	}
}

void CInven::Inven_ConsumeItem_CountRender(HDC _dc)
{
	if (m_bInvenMode[INVEN_CONSUME])
	{
		m_myConsumeItemFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
		HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

		TCHAR szHpPotion_Count[100] = { 0 };
		TCHAR szMpPotion_Count[100] = { 0 };

		ITEMITER iter = m_Inven_ConsumeList.begin();
		ITEMITER iter_End = m_Inven_ConsumeList.end();

		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->GetItemData()->m_dwOption == 11)
			{
				_stprintf_s(szHpPotion_Count, _countof(szHpPotion_Count), L"%d", (*iter)->GetItemData()->m_iCount);

				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, int((*iter)->GetInfo()->fx + 28.f), int((*iter)->GetInfo()->fy + 23.f), szHpPotion_Count, lstrlen(szHpPotion_Count));
				SelectObject(_dc, oldFont);
			}

			if ((*iter)->GetItemData()->m_dwOption == 12)
			{
				_stprintf_s(szMpPotion_Count, _countof(szMpPotion_Count), L"%d", (*iter)->GetItemData()->m_iCount);

				SetBkMode(_dc, TRANSPARENT);
				TextOut(_dc, int((*iter)->GetInfo()->fx + 28.f), int((*iter)->GetInfo()->fy + 23.f), szMpPotion_Count, lstrlen(szMpPotion_Count));
				SelectObject(_dc, oldFont);
			}
		}
	}
}

void CInven::Inven_Item_Render(HDC _dc)
{
	//인벤 모드에서의 인벤 아이템 배치
	if (m_bInvenMode[INVEN_EQUIP])
	{
		//장비 목록
		ITEMITER iter_Equip = m_Inven_EquipList.begin();
		ITEMITER iter_Equip_End = m_Inven_EquipList.end();

		float fOffsetPosY = 0.f;
		int iIndex = 0;
		int iSize = m_Inven_EquipList.size();

		for (iter_Equip; iter_Equip != iter_Equip_End; ++iter_Equip, ++iIndex)
		{
			SLOTITER iter_Slot = m_Inven_SlotList.begin();
			SLOTITER iter_Slot_End = m_Inven_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter_Slot)->GetSlotNumber() == iIndex)
				{
					//Slot Data Setting
					(*iter_Slot)->SetSlotData(*(*iter_Equip)->GetItemData());

					//Item Poisition Setting
					(*iter_Equip)->SetItem_SlotNumber(iIndex);

					if (m_bInvenItem_DragCheck == true)
					{
						if (m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber == (*iter_Equip)->GetItemData()->m_dwInven_SlotNumber){
						}
						else
							(*iter_Equip)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					}
					else
						(*iter_Equip)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
			}

			//Item Render
			(*iter_Equip)->Render(_dc);
		}
	}
	else if (m_bInvenMode[INVEN_CONSUME])
	{
		//소비 목록
		//Slot에 있는 타 목록의 정보를 다 지워준다.
		SLOTITER iter_Slot = m_Inven_SlotList.begin();
		SLOTITER iter_Slot_End = m_Inven_SlotList.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			ITEM tItem;
			ZeroMemory(&tItem, sizeof(ITEM));

			(*iter_Slot)->SetSlotData(tItem);
		}

		//Consume List Rendering
		ITEMITER iter_Consume = m_Inven_ConsumeList.begin();
		ITEMITER iter_Consume_End = m_Inven_ConsumeList.end();

		float fOffsetPosY = 0.f;
		int iIndex = 0;
		int iSize = m_Inven_ConsumeList.size();

		for (iter_Consume; iter_Consume != iter_Consume_End; ++iter_Consume, ++iIndex)
		{
			iter_Slot = m_Inven_SlotList.begin();
			iter_Slot_End = m_Inven_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter_Slot)->GetSlotNumber() == iIndex)
				{
					//Slot Data Setting
					(*iter_Slot)->SetSlotData(*(*iter_Consume)->GetItemData());

					//Item Poisition Setting
					(*iter_Consume)->SetItem_SlotNumber(iIndex);
									
					if (m_bInvenItem_DragCheck == true)
					{
						if (m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber == (*iter_Consume)->GetItemData()->m_dwInven_SlotNumber) {
						}
						else
							(*iter_Consume)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					}
					else
						(*iter_Consume)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
			}

			//Item Render
			(*iter_Consume)->Render(_dc);
		}
	}
	else if (m_bInvenMode[INVEN_ETC])
	{
		//기타 목록
		//Slot에 있는 타 목록의 정보를 다 지워준다.
		SLOTITER iter_Slot = m_Inven_SlotList.begin();
		SLOTITER iter_Slot_End = m_Inven_SlotList.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			ITEM tItem;
			ZeroMemory(&tItem, sizeof(ITEM));

			(*iter_Slot)->SetSlotData(tItem);
		}

		//Etc List Rendering
		ITEMITER iter_Etc = m_Inven_EtcList.begin();
		ITEMITER iter_Etc_End = m_Inven_EtcList.end();

		float fOffsetPosY = 0.f;
		int iIndex = 0;
		int iSize = m_Inven_EtcList.size();

		for (iter_Etc; iter_Etc != iter_Etc_End; ++iter_Etc, ++iIndex)
		{
			iter_Slot = m_Inven_SlotList.begin();
			iter_Slot_End = m_Inven_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter_Slot)->GetSlotNumber() == iIndex)
				{
					//Slot Data Setting
					(*iter_Slot)->SetSlotData(*(*iter_Etc)->GetItemData());

					//Item Poisition Setting
					(*iter_Etc)->SetItem_SlotNumber(iIndex);
				
					if (m_bInvenItem_DragCheck == true)
					{
						if (m_pSelect_Item->GetItemData()->m_dwInven_SlotNumber == (*iter_Etc)->GetItemData()->m_dwInven_SlotNumber) {
						}
						else
							(*iter_Etc)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					}
					else
						(*iter_Etc)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
				}
			}

			//Item Render
			(*iter_Etc)->Render(_dc);
		}
	}
}

void CInven::Inven_Messo_Render(HDC _dc)
{
	CPlayer* pPlayer = NULL;
	pPlayer = ((CPlayer*)(GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->back()));

	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

	//Money
	TCHAR szMesso[128] = { 0 };
	_stprintf_s(szMesso, _countof(szMesso), L"%d", pPlayer->GetMoney());

	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, int(m_tInfo.fx + 56.f), int(m_tInfo.fy + 269.f), szMesso, lstrlen(szMesso));
	SelectObject(_dc, oldFont);
}
#pragma endregion

void CInven::Inven_ItemClassification(CItem* pItem)
{
	static int iConsumeItem_Count_Hp = 0;
	static int iConsumeItem_Count_Mp = 0;

	//아이템 구매시에 종류별로 구별 한다.
	if (pItem->GetItemData()->m_dwOption == 0 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pArmor = new CArmor(L"Armor");
		((CArmor*)pArmor)->Initialize();
		((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
		pArmor->SetItemDescription(L"기본 갑옷");
		m_Inven_EquipList.push_back(pArmor);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 1 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pArmor = new CArmor(L"Armor1");
		((CArmor*)pArmor)->Initialize();
		((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
		pArmor->SetItemDescription(L"고급 갑옷");
		m_Inven_EquipList.push_back(pArmor);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 2 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pWeapon = new CWeapon(L"Weapon");
		((CWeapon*)pWeapon)->Initialize();
		((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
		pWeapon->SetItemDescription(L"기본 무기");
		m_Inven_EquipList.push_back(pWeapon);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 3 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pWeapon = new CWeapon(L"Weapon1");
		((CWeapon*)pWeapon)->Initialize();
		((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
		pWeapon->SetItemDescription(L"고급 무기");
		m_Inven_EquipList.push_back(pWeapon);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 4 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pGlove = new CGlove(L"Glove");
		((CGlove*)pGlove)->Initialize();
		((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
		pGlove->SetItemDescription(L"기본 장갑");
		m_Inven_EquipList.push_back(pGlove);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 5 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pGlove = new CGlove(L"Glove1");
		((CGlove*)pGlove)->Initialize();
		((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
		pGlove->SetItemDescription(L"고급 장갑");
		m_Inven_EquipList.push_back(pGlove);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 6 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pHelmet = new CHelmet(L"Helmet");
		((CHelmet*)pHelmet)->Initialize();
		((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
		pHelmet->SetItemDescription(L"투구");
		m_Inven_EquipList.push_back(pHelmet);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 7 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
		((CAccessory*)pAcs)->Initialize();
		((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
		pAcs->SetItemDescription(L"메이플 반지");
		m_Inven_EquipList.push_back(pAcs);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 8 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pAcs = new CAccessory(L"Accessory1", ITEM_RING);
		((CAccessory*)pAcs)->Initialize();
		((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
		pAcs->SetItemDescription(L"고급 반지");
		m_Inven_EquipList.push_back(pAcs);
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 9 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pShoes = new CShoes(L"Shoes");
		((CShoes*)pShoes)->Initialize();
		((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
		pShoes->SetItemDescription(L"기본 신발");
		m_Inven_EquipList.push_back(pShoes);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 10 && m_bInvenItem_CreateCheck == false)
	{
		CItem* pShoes = new CShoes(L"Shoes1");
		((CShoes*)pShoes)->Initialize();
		((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
		pShoes->SetItemDescription(L"고급 신발");
		m_Inven_EquipList.push_back(pShoes);

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 11 && m_bInvenItem_CreateCheck == false)
	{
		//초반 갯수 1개로 설정.
		++iConsumeItem_Count_Hp;
		
		static bool bCheck = false;

		//list 검사시에 관련된 아이템이 있다면 증가된 Count 값만 넣어줌.
		ITEMITER iter = m_Inven_ConsumeList.begin();
		ITEMITER iter_End = m_Inven_ConsumeList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->GetItemData()->m_dwOption == 11)
			{
				(*iter)->SetItem_Count(iConsumeItem_Count_Hp);
				bCheck = true;
				break;
			}
		}

		//아이템이 없으면 동적 할당해서 생성.
		if (bCheck == false)
		{
			CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
			((CPotion*)pPotion)->Initialize();
			((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
			pPotion->SetItemDescription(L"생명력 포션");
			pPotion->SetItem_Count(iConsumeItem_Count_Hp);
			m_Inven_ConsumeList.push_back(pPotion);
		}		

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 12 && m_bInvenItem_CreateCheck == false)
	{
		++iConsumeItem_Count_Mp;

		static bool bCheck = false;

		//list 검사시에 관련된 아이템이 있다면 증가된 Count 값만 넣어줌.
		ITEMITER iter = m_Inven_ConsumeList.begin();
		ITEMITER iter_End = m_Inven_ConsumeList.end();
		for (iter; iter != iter_End; ++iter)
		{
			if ((*iter)->GetItemData()->m_dwOption == 12)
			{
				(*iter)->SetItem_Count(iConsumeItem_Count_Mp);
				bCheck = true;
				break;
			}
		}

		//아이템이 없으면 동적 할당해서 생성.
		if (bCheck == false)
		{
			CItem* pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
			((CPotion*)pPotion)->Initialize();
			((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
			pPotion->SetItemDescription(L"마나 포션");
			pPotion->SetItem_Count(iConsumeItem_Count_Mp);
			m_Inven_ConsumeList.push_back(pPotion);
		}	
		
		m_bInvenItem_CreateCheck = true;
	}
}

CItem * CInven::Inven_ItemSwapClassification(CItem * pItem)
{
	//Inven 안에서 Swap 시에 아이템 분류 하는 기능.

	CItem* pTemp = NULL;

	if (pItem->GetItemData()->m_dwOption == 0 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CArmor(L"Armor");
		((CArmor*)pTemp)->Initialize();
		((CArmor*)pTemp)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
		pTemp->SetItemDescription(L"기본 갑옷");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 1 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CArmor(L"Armor1");
		((CArmor*)pTemp)->Initialize();
		((CArmor*)pTemp)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
		pTemp->SetItemDescription(L"고급 갑옷");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 2 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CWeapon(L"Weapon");
		((CWeapon*)pTemp)->Initialize();
		((CWeapon*)pTemp)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
		pTemp->SetItemDescription(L"기본 무기");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 3 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CWeapon(L"Weapon1");
		((CWeapon*)pTemp)->Initialize();
		((CWeapon*)pTemp)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
		pTemp->SetItemDescription(L"고급 무기");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 4 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CGlove(L"Glove");
		((CGlove*)pTemp)->Initialize();
		((CGlove*)pTemp)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
		pTemp->SetItemDescription(L"기본 장갑");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 5 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CGlove(L"Glove1");
		((CGlove*)pTemp)->Initialize();
		((CGlove*)pTemp)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
		pTemp->SetItemDescription(L"고급 장갑");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 6 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CHelmet(L"Helmet");
		((CHelmet*)pTemp)->Initialize();
		((CHelmet*)pTemp)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
		pTemp->SetItemDescription(L"투구");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 7 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CAccessory(L"Accessory", ITEM_RING);
		((CAccessory*)pTemp)->Initialize();
		((CAccessory*)pTemp)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
		pTemp->SetItemDescription(L"메이플 반지");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 8 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CAccessory(L"Accessory1", ITEM_RING);
		((CAccessory*)pTemp)->Initialize();
		((CAccessory*)pTemp)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
		pTemp->SetItemDescription(L"고급 반지");
		
		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 9 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CShoes(L"Shoes");
		((CShoes*)pTemp)->Initialize();
		((CShoes*)pTemp)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
		pTemp->SetItemDescription(L"기본 신발");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 10 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CShoes(L"Shoes1");
		((CShoes*)pTemp)->Initialize();
		((CShoes*)pTemp)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
		pTemp->SetItemDescription(L"고급 신발");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 11 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
		((CPotion*)pTemp)->Initialize();
		((CPotion*)pTemp)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
		pTemp->SetItemDescription(L"생명력 포션");

		m_bInvenItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 12 && m_bInvenItem_CreateCheck == false)
	{
		pTemp = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
		((CPotion*)pTemp)->Initialize();
		((CPotion*)pTemp)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
		pTemp->SetItemDescription(L"마나 포션");

		m_bInvenItem_CreateCheck = true;
	}

	return pTemp;
}

#pragma region Save & Load
void CInven::Save_InvenData(void)
{
	//Inven Item Data Save
	//Eequip
	DWORD dwByte;
	HANDLE hFile_Equip = CreateFile(L"../Data/Player_Inven_Item_Equip.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ITEMITER iter = m_Inven_EquipList.begin();
	ITEMITER iter_End = m_Inven_EquipList.end();
	for (iter; iter != iter_End; ++iter)
	{
		ITEM tItem;
		ZeroMemory(&tItem, sizeof(ITEM));
		memcpy_s(&tItem, sizeof(ITEM), (*iter)->GetItemData(), sizeof(ITEM));
		WriteFile(hFile_Equip, &tItem, sizeof(ITEM), &dwByte, NULL);
	}
	CloseHandle(hFile_Equip);

	//Consume
	DWORD dwConsume_Byte;
	HANDLE hFile_Consume = CreateFile(L"../Data/Player_Inven_Item_Consume.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ITEMITER iter_Consume = m_Inven_ConsumeList.begin();
	ITEMITER iter_Consume_End = m_Inven_ConsumeList.end();
	for (iter_Consume; iter_Consume != iter_Consume_End; ++iter_Consume)
	{
		ITEM tItem;
		ZeroMemory(&tItem, sizeof(ITEM));
		memcpy_s(&tItem, sizeof(ITEM), (*iter_Consume)->GetItemData(), sizeof(ITEM));
		WriteFile(hFile_Consume, &tItem, sizeof(ITEM), &dwConsume_Byte, NULL);
	}
	CloseHandle(hFile_Consume);

	//Etc
	DWORD dwEtc_Byte;
	HANDLE hFile_Etc = CreateFile(L"../Data/Player_Inven_Item_Etc.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ITEMITER iter_Etc = m_Inven_EtcList.begin();
	ITEMITER iter_Etc_End = m_Inven_EtcList.end();
	for (iter_Etc; iter_Etc != iter_Etc_End; ++iter_Etc)
	{
		ITEM tItem;
		ZeroMemory(&tItem, sizeof(ITEM));
		memcpy_s(&tItem, sizeof(ITEM), (*iter_Etc)->GetItemData(), sizeof(ITEM));
		WriteFile(hFile_Etc, &tItem, sizeof(ITEM), &dwEtc_Byte, NULL);
	}
	CloseHandle(hFile_Etc);
}

void CInven::Load_InvenData(void)
{
	CItem* pItem = NULL;
	ITEM tItem;
	ZeroMemory(&tItem, sizeof(ITEM));
	
	DWORD dwByte;
	HANDLE hFile = CreateFile(L"../Data/Player_Inven_Item_Equip.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	while (true)
	{
		ReadFile(hFile, &tItem, sizeof(ITEM), &dwByte, NULL);

		if (dwByte == 0)
			break;

		if (tItem.m_dwOption == 0)
		{
			pItem = new CArmor(L"Armor");
			((CArmor*)pItem)->Initialize();
			((CArmor*)pItem)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
			pItem->SetItemDescription(L"기본 갑옷");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 1)
		{
			pItem = new CArmor(L"Armor1");
			((CArmor*)pItem)->Initialize();
			((CArmor*)pItem)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
			pItem->SetItemDescription(L"고급 갑옷");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 2)
		{
			pItem = new CWeapon(L"Weapon");
			((CWeapon*)pItem)->Initialize();
			((CWeapon*)pItem)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
			pItem->SetItemDescription(L"기본 무기");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 3)
		{
			pItem = new CWeapon(L"Weapon1");
			((CWeapon*)pItem)->Initialize();
			((CWeapon*)pItem)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
			pItem->SetItemDescription(L"고급 무기");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 4)
		{
			pItem = new CGlove(L"Glove");
			((CGlove*)pItem)->Initialize();
			((CGlove*)pItem)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
			pItem->SetItemDescription(L"기본 장갑");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 5)
		{
			pItem = new CGlove(L"Glove1");
			((CGlove*)pItem)->Initialize();
			((CGlove*)pItem)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
			pItem->SetItemDescription(L"고급 장갑");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 6)
		{
			pItem = new CHelmet(L"Helmet");
			((CHelmet*)pItem)->Initialize();
			((CHelmet*)pItem)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
			pItem->SetItemDescription(L"투구");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 7)
		{
			pItem = new CAccessory(L"Accessory", ITEM_RING);
			((CAccessory*)pItem)->Initialize();
			((CAccessory*)pItem)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
			pItem->SetItemDescription(L"메이플 반지");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 8)
		{
			pItem = new CAccessory(L"Accessory1", ITEM_RING);
			((CAccessory*)pItem)->Initialize();
			((CAccessory*)pItem)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
			pItem->SetItemDescription(L"고급 반지");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 9)
		{
			pItem = new CShoes(L"Shoes");
			((CShoes*)pItem)->Initialize();
			((CShoes*)pItem)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
			pItem->SetItemDescription(L"기본 신발");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 10)
		{
			pItem = new CShoes(L"Shoes1");
			((CShoes*)pItem)->Initialize();
			((CShoes*)pItem)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
			pItem->SetItemDescription(L"고급 신발");
			m_Inven_EquipList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}				
	}
	CloseHandle(hFile);

	DWORD dwConsume_Byte;
	HANDLE hFile_Consume = CreateFile(L"../Data/Player_Inven_Item_Consume.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	while (true)
	{
		ReadFile(hFile_Consume, &tItem, sizeof(ITEM), &dwConsume_Byte, NULL);
	
		if (dwConsume_Byte == 0)
			break;

		if (tItem.m_dwOption == 11)
		{
			pItem = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
			((CPotion*)pItem)->Initialize();
			((CPotion*)pItem)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
			pItem->SetItemDescription(L"생명력 포션");
			pItem->SetItem_Count(tItem.m_iCount);
			m_Inven_ConsumeList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}
		else if (tItem.m_dwOption == 12)
		{
			pItem = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
			((CPotion*)pItem)->Initialize();
			((CPotion*)pItem)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
			pItem->SetItemDescription(L"마나 포션");
			pItem->SetItem_Count(tItem.m_iCount);
			m_Inven_ConsumeList.push_back(pItem);
			m_Inven_ItemList.push_back(pItem);
		}				
	}	
	CloseHandle(hFile_Consume);
}
#pragma endregion
