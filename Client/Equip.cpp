#include "stdafx.h"
#include "Equip.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "Slot.h"

//UI
#include "Item.h"
#include "Inven.h"
#include "Stat.h"

//Item
//-------------------------
#include "Armor.h"
#include "Shoes.h"
#include "Accessory.h"
#include "Weapon.h"
#include "Glove.h"
#include "Helmet.h"
//-------------------------

typedef list<CItem*>::iterator ITEMITER;
typedef list<CSlot*>::iterator SLOTITER;

CEquip::CEquip(void)
{
	m_eUiType = UI_EQUIP;
	m_dwTime = 0;

	m_pSelect_Item = NULL;
	m_pSelect_Slot = NULL;

	m_bEquipMoveCheck = false;
	m_bEquipItem_CreateCheck = false;
	m_bEquipItem_ApplyCheck = false;
	m_bEquipItem_SwapCheck = false;
	m_bUnEquipItem_Check = false;

	ZeroMemory(&m_tEquipMove_Rect, sizeof(RECT));
	ZeroMemory(&m_tEquipEscButton_Info, sizeof(INFO));
	ZeroMemory(&m_tEquipEscButton_Rect, sizeof(RECT));
}

CEquip::~CEquip(void)
{
	Release();
}

void CEquip::Initialize(void)
{
	m_tInfo.fx  = 173.f;
	m_tInfo.fy  = 0.f;
	m_tInfo.fcx = 237.f;
	m_tInfo.fcy = 332.f;
	m_eRenderType = RENDER_UI;

	//Equip Esc Button
	m_tEquipEscButton_Info.fx = m_tInfo.fx + 215.f;
	m_tEquipEscButton_Info.fy = m_tInfo.fy + 5.f;
	m_tEquipEscButton_Info.fcx = 14.f;
	m_tEquipEscButton_Info.fcy = 14.f;

	//Slot Create
	Equip_SlotCreate();

	m_dwTime = GetTickCount();
}

int CEquip::Update(void)
{
	//Equip Move Rect
	m_tEquipMove_Rect.left   = long(m_tInfo.fx + (m_tInfo.fcx / 2.f - 12.f) - m_tInfo.fcx - 12.f / 2.f);
	m_tEquipMove_Rect.right  = long(m_tInfo.fx + (m_tInfo.fcx / 2.f - 12.f) + m_tInfo.fcx - 12.f / 2.f);
	m_tEquipMove_Rect.top    = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
	m_tEquipMove_Rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);

	//Equip Esc Button Rect
	m_tEquipEscButton_Rect.left   = long(m_tEquipEscButton_Info.fx + (m_tEquipEscButton_Info.fcx / 2.f) - m_tEquipEscButton_Info.fcx / 2.f);
	m_tEquipEscButton_Rect.right  = long(m_tEquipEscButton_Info.fx + (m_tEquipEscButton_Info.fcx / 2.f) + m_tEquipEscButton_Info.fcx / 2.f);
	m_tEquipEscButton_Rect.top    = long(m_tEquipEscButton_Info.fy + (m_tEquipEscButton_Info.fcy / 2.f) - m_tEquipEscButton_Info.fcy / 2.f);
	m_tEquipEscButton_Rect.bottom = long(m_tEquipEscButton_Info.fy + (m_tEquipEscButton_Info.fcy / 2.f) + m_tEquipEscButton_Info.fcy / 2.f);

	//Key Setting
	Equip_Key();
	Equip_EscButton_Click();

	if (m_bVisible == true)
	{
		Equip_Move();
		Equip_SlotUpdqte();
		Equip_Item_SetPosition();
		UnEquip_Item();

		//Equip Item Update
		ITEMITER iter_Equip = m_Equip_ItemList.begin();
		for (iter_Equip; iter_Equip != m_Equip_ItemList.end(); ++iter_Equip)
			(*iter_Equip)->Update();
	}

	return 0;
}

void CEquip::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx), int(m_tInfo.fy),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Equipment")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));

		ITEMITER iter = m_Equip_ItemList.begin();
		ITEMITER iter_End = m_Equip_ItemList.end();

		for (iter; iter != iter_End; ++iter)
			(*iter)->Render(_dc);

		//Equip_SlotRender(_dc);

		/*
		Rectangle(_dc,
			m_tEquipEscButton_Rect.left,
			m_tEquipEscButton_Rect.top,
			m_tEquipEscButton_Rect.right,
			m_tEquipEscButton_Rect.bottom);
		*/
	}
}

void CEquip::Release(void)
{
	ITEMITER iter_Item = m_Equip_ItemList.begin();
	ITEMITER iter_Item_End = m_Equip_ItemList.end();
	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
	{
		SAFE_DELETE((*iter_Item));
	}
	m_Equip_ItemList.clear();

	SLOTITER iter_Slot = m_Equip_SlotList.begin();
	SLOTITER iter_Slot_End = m_Equip_SlotList.end();
	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		SAFE_DELETE((*iter_Slot));
	}
	m_Equip_SlotList.clear();
}

void CEquip::Equip_Key(void)
{
	static bool bIsPress_Equip = false;
	if (GETS(CKeyMgr)->OnceKeyDown('E') && bIsPress_Equip == false)
	{
		if (m_bVisible == true)
			m_bVisible = false;
		else
			m_bVisible = true;

		bIsPress_Equip = true;
	}

	if (m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if (bIsPress_Equip == true)
			bIsPress_Equip = false;
	}

	//���콺 ������ ��ư�� Up �Ǹ� UnEquipItem_Check = false
	if (m_bUnEquipItem_Check == true && GETS(CKeyMgr)->OnceKeyUp(VK_RBUTTON))
		m_bUnEquipItem_Check = false;
}

void CEquip::Equip_Move(void)
{
	//Equip â�� ���콺�� �����̰� ����� �Լ�.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tEquipMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bEquipMoveCheck = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bEquipMoveCheck == true)
		m_bEquipMoveCheck = false;

	if (m_bEquipMoveCheck == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);    //10.f �� Rect�� y�� / 2 �� ��.

	   //Inven Move Rect
		m_tEquipMove_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f - 12.f) - m_tInfo.fcx - 12.f / 2.f);
		m_tEquipMove_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f - 12.f) + m_tInfo.fcx - 12.f / 2.f);
		m_tEquipMove_Rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
		m_tEquipMove_Rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);

		//Equip Esc Button
		m_tEquipEscButton_Info.fx = m_tInfo.fx + 215.f;
		m_tEquipEscButton_Info.fy = m_tInfo.fy + 5.f;
		m_tEquipEscButton_Info.fcx = 14.f;
		m_tEquipEscButton_Info.fcy = 14.f;
	}
}

void CEquip::Equip_EscButton_Click(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tEquipEscButton_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		m_bVisible = false;
}

#pragma region Equip Function
void CEquip::Equip_Item(CItem* pItem)
{
	//Item ���� ��� �Լ�
	if (pItem->GetItemData()->m_eType == ITEM_ARMOR)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_ARMOR;
		Equip_Slot_ItemCheck(pItem);
	}
	else if (pItem->GetItemData()->m_eType == ITEM_HELMET)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_HELMET;
		Equip_Slot_ItemCheck(pItem);
	}
	else if (pItem->GetItemData()->m_eType == ITEM_GLOVES)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_GLOVES;
		Equip_Slot_ItemCheck(pItem);
	}
	else if (pItem->GetItemData()->m_eType == ITEM_RING)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_RING;
		Equip_Slot_ItemCheck(pItem);
	}
	else if (pItem->GetItemData()->m_eType == ITEM_SHOES)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_SHOES;
		Equip_Slot_ItemCheck(pItem);
	}
	else if (pItem->GetItemData()->m_eType == ITEM_WEAPON)
	{
		pItem->GetItemData()->m_eEquip_Type = EQUIP_WEAPON;
		Equip_Slot_ItemCheck(pItem);
	}
}

void CEquip::Equip_Slot_ItemCheck(CItem * pItem)
{
	//�������� ���� �Ӽ��̶� ��.	
	SLOTITER iter = m_Equip_SlotList.begin();
	SLOTITER iter_End = m_Equip_SlotList.end();

	CSlot* pSlot = NULL;
	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->GetEquipType() == pItem->GetItemData()->m_eEquip_Type)
		{
			pSlot = (*iter);
			break;
		}
	}

	//Slot �� Item�� Rect�� �浹�Ҷ��� �˻�
	RECT rc;
	if (IntersectRect(&rc, pItem->GetRect(), pSlot->GetRect()))
	{
		//Slot�� �ִ� Equip Item �� pItem�� dwOption ���� ���� �Ǹ� 
		//������ �Ӽ��� ���� X (�̹� ������ �����̸�)

		SLOTITER iter_Slot = m_Equip_SlotList.begin();
		SLOTITER iter_Slot_End = m_Equip_SlotList.end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if ((*iter_Slot)->GetEquipType() == pItem->GetItemData()->m_eEquip_Type)
			{
				ITEMITER iter = m_Equip_ItemList.begin();
				for (iter; iter != m_Equip_ItemList.end(); ++iter)
				{
					//Swap ���¸� �����ϴ� ���� �ƴϹǷ� ���� ������������ �Ǵ��ؼ� ������ ���¸�
					//���̻� �Ӽ� �߰� �ȵǵ��� �Ѵ�.
					if ((*iter)->GetItemData()->m_dwOption == pItem->GetItemData()->m_dwOption
						&& pSlot->GetEquip_Status() == 1)
					{
						m_bEquipItem_ApplyCheck = true;
						break;
					}
				}			
			}
		}

		//Equip Item�� Inven Item Swap ���.
		if (pItem->GetItemData()->m_dwEquip_Status == 0 && pSlot->GetEquip_Status() == 1)
			Equip_Swap_Item(pItem);
		
		//pItem�� ������ ���°� �ƴϸ� �������� ���� �����Ǽ� �����ǰ� ����.
		if (pItem->GetItemData()->m_dwEquip_Status != 1 && pSlot->GetEquip_Status() == 0)
		{
			CItem* pEquipItem = Equip_Item_Classification(pItem, pSlot);
			pEquipItem->SetPos(pSlot->GetInfo()->fx, pSlot->GetInfo()->fy);
			m_Equip_ItemList.push_back(pEquipItem);
		}
	}	
}

CItem* CEquip::Equip_Item_Classification(CItem * pItem, CSlot* pSlot)
{
	//pItem �� EquipStatus�� ���� �����ش���
	//pItem�� EquipSTatus�� 0�϶��� ���� �����ǰ� �ϰ�
	//�ƴҶ��� Swap �ǰ� ����.

	CItem* pEquip_Item = NULL;

	if (pItem->GetItemData()->m_dwOption == 0 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CArmor(L"Armor");
		((CArmor*)pEquip_Item)->Initialize();
		((CArmor*)pEquip_Item)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
		pEquip_Item->SetItemDescription(L"�⺻ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 1 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CArmor(L"Armor1");
		((CArmor*)pEquip_Item)->Initialize();
		((CArmor*)pEquip_Item)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);
		
		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 2 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CWeapon(L"Weapon");
		((CWeapon*)pEquip_Item)->Initialize();
		((CWeapon*)pEquip_Item)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
		pEquip_Item->SetItemDescription(L"�⺻ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 3 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CWeapon(L"Weapon1");
		((CWeapon*)pEquip_Item)->Initialize();
		((CWeapon*)pEquip_Item)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 4 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CGlove(L"Glove");
		((CGlove*)pEquip_Item)->Initialize();
		((CGlove*)pEquip_Item)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
		pEquip_Item->SetItemDescription(L"�⺻ �尩");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 5 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CGlove(L"Glove1");
		((CGlove*)pEquip_Item)->Initialize();
		((CGlove*)pEquip_Item)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
		pEquip_Item->SetItemDescription(L"��� �尩");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 6 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CHelmet(L"Helmet");
		((CHelmet*)pEquip_Item)->Initialize();
		((CHelmet*)pEquip_Item)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
		pEquip_Item->SetItemDescription(L"����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 7 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CAccessory(L"Accessory", ITEM_RING);
		((CAccessory*)pEquip_Item)->Initialize();
		((CAccessory*)pEquip_Item)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
		pEquip_Item->SetItemDescription(L"������ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 8 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CAccessory(L"Accessory1", ITEM_RING);
		((CAccessory*)pEquip_Item)->Initialize();
		((CAccessory*)pEquip_Item)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 9 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CShoes(L"Shoes");
		((CShoes*)pEquip_Item)->Initialize();
		((CShoes*)pEquip_Item)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
		pEquip_Item->SetItemDescription(L"�⺻ �Ź�");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 10 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CShoes(L"Shoes1");
		((CShoes*)pEquip_Item)->Initialize();
		((CShoes*)pEquip_Item)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
		pEquip_Item->SetItemDescription(L"��� �Ź�");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);
		pSlot->SetEquip_Status(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Apply_To_ItemArrtibute(pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}

	return pEquip_Item;
}

void CEquip::Equip_Item_SetPosition(void)
{
	ITEMITER iter = m_Equip_ItemList.begin();
	ITEMITER iter_End = m_Equip_ItemList.end();

	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_RING)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_HELMET)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_ARMOR)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_PANTS)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_GLOVES)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_SHOES)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
		else if ((*iter)->GetItemData()->m_eEquip_Type == EQUIP_WEAPON)
		{
			SLOTITER iter_Slot = m_Equip_SlotList.begin();
			SLOTITER iter_Slot_End = m_Equip_SlotList.end();

			for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
			{
				if ((*iter)->GetItemData()->m_eEquip_Type == (*iter_Slot)->GetEquipType())
				{
					(*iter)->SetPos((*iter_Slot)->GetInfo()->fx, (*iter_Slot)->GetInfo()->fy);
					(*iter_Slot)->SetEquipSlot_Check(true);
				}
			}
		}
	}
}

void CEquip::Equip_Apply_To_ItemArrtibute(CItem* pItem)
{
	//Stat ���� Player Stat ���ϱ�.
	if (m_bEquipItem_ApplyCheck == false)
	{
		OBJITER iter_Obj = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
		OBJITER iter_Obj_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

		CStat* pStat = NULL;
		for (iter_Obj; iter_Obj != iter_Obj_End; ++iter_Obj)
		{
			if (((CUi*)(*iter_Obj))->GetUiType() == UI_STAT)
			{
				pStat = ((CStat*)(*iter_Obj));
				break;
			}
		}

		STAT tStat;
		tStat.m_iSTR = pStat->Get_PlayerStat()->m_iSTR + pItem->GetItemData()->m_iStr;
		tStat.m_iDEX = pStat->Get_PlayerStat()->m_iDEX + pItem->GetItemData()->m_iDex;
		tStat.m_iINT = pStat->Get_PlayerStat()->m_iINT + pItem->GetItemData()->m_iInt;
		tStat.m_iLUK = pStat->Get_PlayerStat()->m_iLUK + pItem->GetItemData()->m_iLuk;
		pStat->Set_PlayerStat(tStat);
	}	
}

void CEquip::Equip_Swap_Apply_To_ItemAttribute(CItem * pItem, CItem * pSwapItem)
{
	//Stat ���� Player Stat ���ϱ�.
	OBJITER iter_Obj = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_Obj_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CStat* pStat = NULL;
	for (iter_Obj; iter_Obj != iter_Obj_End; ++iter_Obj)
	{
		if (((CUi*)(*iter_Obj))->GetUiType() == UI_STAT)
		{
			pStat = ((CStat*)(*iter_Obj));
			break;
		}
	}

	STAT tStat;
	tStat.m_iSTR = pStat->Get_PlayerStat()->m_iSTR + pSwapItem->GetItemData()->m_iStr - pItem->GetItemData()->m_iStr;
	tStat.m_iDEX = pStat->Get_PlayerStat()->m_iDEX + pSwapItem->GetItemData()->m_iDex - pItem->GetItemData()->m_iDex;
	tStat.m_iINT = pStat->Get_PlayerStat()->m_iINT + pSwapItem->GetItemData()->m_iInt - pItem->GetItemData()->m_iInt;
	tStat.m_iLUK = pStat->Get_PlayerStat()->m_iLUK + pSwapItem->GetItemData()->m_iLuk - pItem->GetItemData()->m_iLuk;
	pStat->Set_PlayerStat(tStat);
}

void CEquip::Equip_Swap_Item(CItem* pItem)
{
	//Swap Item ���
	ITEMITER iter_Inven_SelectItem;

	//Inven ��������
	CInven* pInven = NULL;
	OBJITER iter_Inven = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_Inven_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
	{
		if (((CUi*)(*iter_Inven))->GetUiType() == UI_INVEN)
		{
			pInven = ((CInven*)(*iter_Inven));
			break;
		}
	}

	//���õ� Inven Item iter ã��
	ITEMITER iter_Inven_Item = pInven->GetInevn_EquipItemList()->begin();
	ITEMITER iter_Inven_Item_End = pInven->GetInevn_EquipItemList()->end();
	for (iter_Inven_Item; iter_Inven_Item != iter_Inven_Item_End; ++iter_Inven_Item)
	{
		if ((*iter_Inven_Item)->GetItemData()->m_dwInven_SlotNumber == pItem->GetItemData()->m_dwInven_SlotNumber)
		{
			iter_Inven_SelectItem = iter_Inven_Item;
			break;
		}
	}

	//Swap ���
	/*
	Swap�� Inven Item�� �����ÿ� �������� �����Ƿ� Inven�� �ִ� �������� �ǵ� 
	�ʿ䰡 ����. �׷��Ƿ� Equip â�� ���� �ִ� �͸� ���� ���� �ִ� ���� �־��ָ� ���̴�.
	*/

	ITEMITER iter = m_Equip_ItemList.begin();
	ITEMITER iter_End = m_Equip_ItemList.end();
	for (iter; iter != iter_End;)
	{
		if ((*iter)->GetItemData()->m_eEquip_Type == pItem->GetItemData()->m_eEquip_Type
			&& m_bEquipItem_SwapCheck == false)
		{
			CItem* pTemp = Equip_Swap_Item_Classification((*iter), pItem);

			//Select Item Input
			m_Equip_ItemList.insert(iter, pTemp);

			//�κ�â���� �������� �����۰� ���� �������� ã�Ƽ� EquipStatus�� 0���� ����� �ش�.
			iter_Inven_Item = pInven->GetInevn_EquipItemList()->begin();
			iter_Inven_Item_End = pInven->GetInevn_EquipItemList()->end();
			for (iter_Inven_Item; iter_Inven_Item != iter_Inven_Item_End; ++iter_Inven_Item)
			{
				if ((*iter_Inven_Item)->GetItemData()->m_dwOption == (*iter)->GetItemData()->m_dwOption)
				{
					(*iter_Inven_Item)->SetITem_EquipStatus(0);
					break;
				}
			}

			//Item Erase
			m_Equip_ItemList.erase(iter);
			iter = m_Equip_ItemList.begin();

			m_bEquipItem_SwapCheck = true;
		}
		else
			++iter;
	}
}

CItem * CEquip::Equip_Swap_Item_Classification(CItem* pSwapItem, CItem * pItem)
{
	//pSwapItem : ���â���� ���ҵ� ������
	//pItem     : �κ�â���� �� ������

	CItem* pEquip_Item = NULL;

	if (pItem->GetItemData()->m_dwOption == 0 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CArmor(L"Armor");
		((CArmor*)pEquip_Item)->Initialize();
		((CArmor*)pEquip_Item)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
		pEquip_Item->SetItemDescription(L"�⺻ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 1 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CArmor(L"Armor1");
		((CArmor*)pEquip_Item)->Initialize();
		((CArmor*)pEquip_Item)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 2 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CWeapon(L"Weapon");
		((CWeapon*)pEquip_Item)->Initialize();
		((CWeapon*)pEquip_Item)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
		pEquip_Item->SetItemDescription(L"�⺻ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 3 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CWeapon(L"Weapon1");
		((CWeapon*)pEquip_Item)->Initialize();
		((CWeapon*)pEquip_Item)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 4 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CGlove(L"Glove");
		((CGlove*)pEquip_Item)->Initialize();
		((CGlove*)pEquip_Item)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
		pEquip_Item->SetItemDescription(L"�⺻ �尩");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 5 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CGlove(L"Glove1");
		((CGlove*)pEquip_Item)->Initialize();
		((CGlove*)pEquip_Item)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
		pEquip_Item->SetItemDescription(L"��� �尩");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 6 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CHelmet(L"Helmet");
		((CHelmet*)pEquip_Item)->Initialize();
		((CHelmet*)pEquip_Item)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
		pEquip_Item->SetItemDescription(L"����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 7 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CAccessory(L"Accessory", ITEM_RING);
		((CAccessory*)pEquip_Item)->Initialize();
		((CAccessory*)pEquip_Item)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
		pEquip_Item->SetItemDescription(L"������ ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 8 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CAccessory(L"Accessory1", ITEM_RING);
		((CAccessory*)pEquip_Item)->Initialize();
		((CAccessory*)pEquip_Item)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
		pEquip_Item->SetItemDescription(L"��� ����");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 9 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CShoes(L"Shoes");
		((CShoes*)pEquip_Item)->Initialize();
		((CShoes*)pEquip_Item)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
		pEquip_Item->SetItemDescription(L"�⺻ �Ź�");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}
	else if (pItem->GetItemData()->m_dwOption == 10 && m_bEquipItem_CreateCheck == false)
	{
		pEquip_Item = new CShoes(L"Shoes1");
		((CShoes*)pEquip_Item)->Initialize();
		((CShoes*)pEquip_Item)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
		pEquip_Item->SetItemDescription(L"��� �Ź�");
		pEquip_Item->SetItem_EquipType(pItem->GetItemData()->m_eEquip_Type);
		pEquip_Item->SetITem_EquipStatus(1);
		pItem->SetITem_EquipStatus(1);

		//Equip Item Attribute Apply To Player Stat
		Equip_Swap_Apply_To_ItemAttribute(pSwapItem, pEquip_Item);

		m_bEquipItem_CreateCheck = true;
	}

	return pEquip_Item;
}

void CEquip::UnEquip_Item(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	SLOTITER iter_Slot = m_Equip_SlotList.begin();
	SLOTITER iter_Slot_End = m_Equip_SlotList.end();

	ITEMITER iter_Item = m_Equip_ItemList.begin();
	ITEMITER iter_Item_End = m_Equip_ItemList.end();

	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		if (PtInRect((*iter_Slot)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_RBUTTON) && m_bUnEquipItem_Check == false)
		{
			for (iter_Item; iter_Item != iter_Item_End;)
			{
				//������ Ŭ���� Slot â�� EquipType�� EquipItemList�� �ִ� Item�� EquipType
				//���� �ÿ��� �� ������ ���� �ϸ鼭 Slot�� EquipStauts�� 0���� ������ش�.
				if ((*iter_Slot)->GetEquipType() == (*iter_Item)->GetItemData()->m_eEquip_Type)
				{
					//Item Attribute ReSetting
					UnEquip_Apply_To_ItemAttribute((*iter_Item));

					//Item Erase
					m_Equip_ItemList.erase(iter_Item);
					iter_Item = m_Equip_ItemList.begin();

					//Slot Equip_Status = 0
					(*iter_Slot)->SetEquip_Status(0);
				}
				else
					++iter_Item;
			}

			m_bUnEquipItem_Check = true;
		}
	}
}
void CEquip::UnEquip_Apply_To_ItemAttribute(CItem * pItem)
{
	OBJITER iter_Obj = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_Obj_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CStat* pStat = NULL;
	for (iter_Obj; iter_Obj != iter_Obj_End; ++iter_Obj)
	{
		if (((CUi*)(*iter_Obj))->GetUiType() == UI_STAT)
		{
			pStat = ((CStat*)(*iter_Obj));
			break;
		}
	}

	STAT tStat;
	tStat.m_iSTR = pStat->Get_PlayerStat()->m_iSTR - pItem->GetItemData()->m_iStr;
	tStat.m_iDEX = pStat->Get_PlayerStat()->m_iDEX - pItem->GetItemData()->m_iDex;
	tStat.m_iINT = pStat->Get_PlayerStat()->m_iINT - pItem->GetItemData()->m_iInt;
	tStat.m_iLUK = pStat->Get_PlayerStat()->m_iLUK - pItem->GetItemData()->m_iLuk;
	pStat->Set_PlayerStat(tStat);
}
#pragma endregion

#pragma region Equip Slot
void CEquip::Equip_SlotCreate(void)
{
	//Equip Slot Create
	for (int i = 0; i < 7; ++i)
	{
		CSlot* pSlot = new CSlot();
		pSlot->Initialize();

		//Ring
		if (i == 0)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 17.f, m_tInfo.fy + 50.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Helmet
		else if (i == 1)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 50.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Armor
		else if (i == 2)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 173.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Pants
		else if (i == 3)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 213.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Gloves
		else if (i == 4)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 140.f, m_tInfo.fy + 213.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Shoes
		else if (i == 5)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 255.f);
			pSlot->SetSize(38.f, 38.f);
		}
		//Weapon
		else if (i == 6)
		{
			pSlot->SetEquipType(i);
			pSlot->SetPos(m_tInfo.fx + 58.f, m_tInfo.fy + 173.f);
			pSlot->SetSize(38.f, 38.f);
		}

		m_Equip_SlotList.push_back(pSlot);
	}
}

void CEquip::Equip_SlotUpdqte(void)
{
	SLOTITER iter_Slot = m_Equip_SlotList.begin();
	SLOTITER iter_Slot_End = m_Equip_SlotList.end();
	
	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		if ((*iter_Slot)->GetEquipType() == EQUIP_RING)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 17.f, m_tInfo.fy + 50.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_HELMET)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 50.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_ARMOR)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 173.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_PANTS)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 213.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_GLOVES)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 140.f, m_tInfo.fy + 213.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_SHOES)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 99.f, m_tInfo.fy + 255.f);
			(*iter_Slot)->Update();
		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_WEAPON)
		{
			(*iter_Slot)->SetPos(m_tInfo.fx + 58.f, m_tInfo.fy + 173.f);
			(*iter_Slot)->Update();
		}
	}
}

void CEquip::Equip_SlotRender(HDC _dc)
{
	SLOTITER iter_Slot = m_Equip_SlotList.begin();
	SLOTITER iter_Slot_End = m_Equip_SlotList.end();

	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		(*iter_Slot)->Render(_dc);
}
#pragma endregion
 