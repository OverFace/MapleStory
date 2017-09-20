#include "stdafx.h"
#include "Store.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Player.h"

//UI
#include "UI.h"
#include "Inven.h"
#include "Slot.h"

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

CStore::CStore(void)
{
	m_eUiType = UI_STORE;
	for (int i = 0; i < 2; ++i)
	{
		ZeroMemory(&m_tEscButton_Rect[i], sizeof(RECT));
		ZeroMemory(&m_tEscButton_Info[i], sizeof(INFO));
	}	
	ZeroMemory(&m_tScroll_Rect, sizeof(RECT));
	ZeroMemory(&m_tScroll_Info, sizeof(INFO));
	ZeroMemory(&m_tBuyButton_Info, sizeof(INFO));
	ZeroMemory(&m_tBuyButton_Rect, sizeof(RECT));
	ZeroMemory(&m_tStoreInven_Scroll_Info, sizeof(INFO));
	ZeroMemory(&m_tStoreInven_Scroll_Rect, sizeof(RECT));
	ZeroMemory(&m_tSaleButton_Info, sizeof(INFO));
	ZeroMemory(&m_tSaleButton_Rect, sizeof(RECT));
	
	m_pStore_Npc = NULL;
	m_pSelect_Item = NULL;

	m_bScrollMove = false;
	m_bStoreInven_ScrollMove = false;
	m_bSale_Check = false;
	for (int i = 0; i < 4; ++i)
		m_bScroll_Item_Check[i] = false;
	for (int i = 0; i < 2; ++i)
		m_bPotion_Check[i] = false;

	m_iStoreInven_ItemCount = 0;
}

CStore::~CStore(void)
{
	Release();
}

void CStore::Initialize(void)
{
	m_tInfo.fx = 200.f;
	m_tInfo.fy = 100.f;
	m_tInfo.fcx = 508.f;
	m_tInfo.fcy = 505.f;

	//Esc Button / X ��ư
	m_tEscButton_Info[0].fx = m_tInfo.fx + m_tInfo.fcx / 2.f;
	m_tEscButton_Info[0].fy = m_tInfo.fy + 10.f;
	m_tEscButton_Info[0].fcx = 9.f;
	m_tEscButton_Info[0].fcy = 9.f;

	//Esc Button / ���� ������ ��ư
	m_tEscButton_Info[1].fx = m_tInfo.fx +  200.f;
	m_tEscButton_Info[1].fy = m_tInfo.fy + 53.f;
	m_tEscButton_Info[1].fcx = 66.f;
	m_tEscButton_Info[1].fcy = 16.f;

	//Scroll 
	m_tScroll_Info.fx = m_tInfo.fx + 258.f;
	m_tScroll_Info.fy = m_tInfo.fy + 134.f;
	m_tScroll_Info.fcx = 9.f;
	m_tScroll_Info.fcy = 26.f;

	m_tStoreInven_Scroll_Info.fx = m_tInfo.fx + 489.f;
	m_tStoreInven_Scroll_Info.fy = m_tInfo.fy + 134.f;
	m_tStoreInven_Scroll_Info.fcx = 9.f;
	m_tStoreInven_Scroll_Info.fcy = 26.f;

	//Buy Button
	m_tBuyButton_Info.fx = m_tInfo.fx + 200.f;
	m_tBuyButton_Info.fy = m_tInfo.fy + 73.f;
	m_tBuyButton_Info.fcx = 66.f;
	m_tBuyButton_Info.fcy = 16.f;

	//Sale Button
	m_tSaleButton_Info.fx = m_tInfo.fx + 432.f;
	m_tSaleButton_Info.fy = m_tInfo.fy + 73.f;
	m_tSaleButton_Info.fcx = 66.f;
	m_tSaleButton_Info.fcy = 16.f;

#pragma region Item List
	//Store Item
	//----------------------------------------------------------------------------------
	//Armor  (Armor, Armor1)
	CItem* pArmor = new CArmor(L"Armor");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);	
	pArmor->SetItemDescription(L"�⺻ ����");
	m_Store_ItemList.push_back(pArmor);

	pArmor = new CArmor(L"Armor1");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
	pArmor->SetItemDescription(L"��� ����");
	m_Store_ItemList.push_back(pArmor);
	//----------------------------------------------------------------------------------
	//Weapon (Weapon, Weapon1)
	CItem* pWeapon = new CWeapon(L"Weapon");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
	pWeapon->SetItemDescription(L"�⺻ ����");
	m_Store_ItemList.push_back(pWeapon);

	pWeapon = new CWeapon(L"Weapon1");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
	pWeapon->SetItemDescription(L"��� ����");
	m_Store_ItemList.push_back(pWeapon);
	//----------------------------------------------------------------------------------
	//Glove (Glove, Glove1)
	CItem* pGlove = new CGlove(L"Glove");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
	pGlove->SetItemDescription(L"�⺻ �尩");
	m_Store_ItemList.push_back(pGlove);

	pGlove = new CGlove(L"Glove1");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
	pGlove->SetItemDescription(L"��� �尩");
	m_Store_ItemList.push_back(pGlove);
	//----------------------------------------------------------------------------------
	//Helmet
	CItem* pHelmet = new CHelmet(L"Helmet");
	((CHelmet*)pHelmet)->Initialize();
	((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
	pHelmet->SetItemDescription(L"����");
	m_Store_ItemList.push_back(pHelmet);
	//----------------------------------------------------------------------------------
	//Accessory
	CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
	pAcs->SetItemDescription(L"������ ����");
	m_Store_ItemList.push_back(pAcs);

	pAcs = new CAccessory(L"Accessory1", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
	pAcs->SetItemDescription(L"��� ����");
	m_Store_ItemList.push_back(pAcs);
	//----------------------------------------------------------------------------------
	//Shoes
	CItem* pShoes = new CShoes(L"Shoes");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
	pShoes->SetItemDescription(L"�⺻ �Ź�");
	m_Store_ItemList.push_back(pShoes);

	pShoes = new CShoes(L"Shoes1");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
	pShoes->SetItemDescription(L"��� �Ź�");
	m_Store_ItemList.push_back(pShoes);
	//----------------------------------------------------------------------------------
	//Potion
	CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
	pPotion->SetItemDescription(L"����� ����");
	m_Store_ItemList.push_back(pPotion);

	pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
	pPotion->SetItemDescription(L"���� ����");
	m_Store_ItemList.push_back(pPotion);
	//----------------------------------------------------------------------------------

	float fx = 10.f;
	float fy = 125.f;
	int	iIndex = 0;
	ITEMITER iter = m_Store_ItemList.begin();
	for (iter; iter != m_Store_ItemList.end(); ++iter, ++iIndex)
	{
		(*iter)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));

		CSlot* pSlot = new CSlot();
		pSlot->Initialize();
		pSlot->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetSlotNumber(iIndex);
		m_Store_SlotList.push_back(pSlot);
	}	
#pragma endregion

	m_eRenderType = RENDER_UI;
}

int CStore::Update(void)
{
	//Button Rect
	m_tEscButton_Rect[0].left = long(m_tEscButton_Info[0].fx + (m_tEscButton_Info[0].fcx / 2.f) - m_tEscButton_Info[0].fcx / 2);
	m_tEscButton_Rect[0].right = long(m_tEscButton_Info[0].fx + (m_tEscButton_Info[0].fcx / 2.f) + m_tEscButton_Info[0].fcx / 2);
	m_tEscButton_Rect[0].top = long(m_tEscButton_Info[0].fy + (m_tEscButton_Info[0].fcy / 2.f) - m_tEscButton_Info[0].fcy / 2);
	m_tEscButton_Rect[0].bottom = long(m_tEscButton_Info[0].fy + (m_tEscButton_Info[0].fcy / 2.f) + m_tEscButton_Info[0].fcy / 2);

	m_tEscButton_Rect[1].left = long(m_tEscButton_Info[1].fx + (m_tEscButton_Info[1].fcx / 2.f) - m_tEscButton_Info[1].fcx / 2);
	m_tEscButton_Rect[1].right = long(m_tEscButton_Info[1].fx + (m_tEscButton_Info[1].fcx / 2.f) + m_tEscButton_Info[1].fcx / 2);
	m_tEscButton_Rect[1].top = long(m_tEscButton_Info[1].fy + (m_tEscButton_Info[1].fcy / 2.f) - m_tEscButton_Info[1].fcy / 2);
	m_tEscButton_Rect[1].bottom = long(m_tEscButton_Info[1].fy + (m_tEscButton_Info[1].fcy / 2.f) + m_tEscButton_Info[1].fcy / 2);

	m_tBuyButton_Rect.left = long(m_tBuyButton_Info.fx + (m_tBuyButton_Info.fcx / 2.f) - m_tBuyButton_Info.fcx / 2);
	m_tBuyButton_Rect.right = long(m_tBuyButton_Info.fx + (m_tBuyButton_Info.fcx / 2.f) + m_tBuyButton_Info.fcx / 2);
	m_tBuyButton_Rect.top = long(m_tBuyButton_Info.fy + (m_tBuyButton_Info.fcy / 2.f) - m_tBuyButton_Info.fcy / 2);
	m_tBuyButton_Rect.bottom = long(m_tBuyButton_Info.fy + (m_tBuyButton_Info.fcy / 2.f) + m_tBuyButton_Info.fcy / 2);

	m_tSaleButton_Rect.left = long(m_tSaleButton_Info.fx + (m_tSaleButton_Info.fcx / 2.f) - m_tSaleButton_Info.fcx / 2);
	m_tSaleButton_Rect.right = long(m_tSaleButton_Info.fx + (m_tSaleButton_Info.fcx / 2.f) + m_tSaleButton_Info.fcx / 2);
	m_tSaleButton_Rect.top = long(m_tSaleButton_Info.fy + (m_tSaleButton_Info.fcy / 2.f) - m_tSaleButton_Info.fcy / 2);
	m_tSaleButton_Rect.bottom = long(m_tSaleButton_Info.fy + (m_tSaleButton_Info.fcy / 2.f) + m_tSaleButton_Info.fcy / 2);

	//Scroll Rect
	m_tScroll_Rect.left = long(m_tScroll_Info.fx + (m_tScroll_Info.fcx / 2.f) - m_tScroll_Info.fcx / 2);
	m_tScroll_Rect.right = long(m_tScroll_Info.fx + (m_tScroll_Info.fcx / 2.f) + m_tScroll_Info.fcx / 2);
	m_tScroll_Rect.top = long(m_tScroll_Info.fy + (m_tScroll_Info.fcy / 2.f) - m_tScroll_Info.fcy / 2);
	m_tScroll_Rect.bottom = long(m_tScroll_Info.fy + (m_tScroll_Info.fcy / 2.f) + m_tScroll_Info.fcy / 2);

	m_tStoreInven_Scroll_Rect.left = long(m_tStoreInven_Scroll_Info.fx + (m_tStoreInven_Scroll_Info.fcx / 2.f) - m_tStoreInven_Scroll_Info.fcx / 2);
	m_tStoreInven_Scroll_Rect.right = long(m_tStoreInven_Scroll_Info.fx + (m_tStoreInven_Scroll_Info.fcx / 2.f) + m_tStoreInven_Scroll_Info.fcx / 2);
	m_tStoreInven_Scroll_Rect.top = long(m_tStoreInven_Scroll_Info.fy + (m_tStoreInven_Scroll_Info.fcy / 2.f) - m_tStoreInven_Scroll_Info.fcy / 2);
	m_tStoreInven_Scroll_Rect.bottom = long(m_tStoreInven_Scroll_Info.fy + (m_tStoreInven_Scroll_Info.fcy / 2.f) + m_tStoreInven_Scroll_Info.fcy / 2);

	//Item Update(Store)
	ITEMITER iter_Item = m_Store_ItemList.begin();
	ITEMITER iter_Item_End = m_Store_ItemList.end();
	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
		(*iter_Item)->Update();

	//Store Slot
	float fx = 10.f; float fy = 125.f; int iIndex = 0;
	SLOTITER iter_Slot = m_Store_SlotList.begin();
	SLOTITER iter_Slot_End = m_Store_SlotList.end();
	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot, ++iIndex)
	{
		(*iter_Slot)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
		(*iter_Slot)->Update();
	}
	Store_InvenSlotUpdate();

	//Slot�� �ƿ� ������ Item Count�� 0���� �ʱ�ȭ
	//if (m_Store_InvenSlot_List.size() == 0)
		//m_iStoreInven_ItemCount = -1;

	if (m_bVisible == true)
	{
		Scroll_Move();
		Item_View_Control();
		StoreInven_Scroll_Move();		
		StoreInven_ItemView_Control();
		Select_StoreItem();
		Buy_Button_Click();
		Select_StoreInvenItem();
		Sale_Button_Click();
	}

	return 0;
}

void CStore::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx), int(m_tInfo.fy),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Store")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));		

		TransparentBlt(_dc,
			int(m_tEscButton_Info[0].fx), int(m_tEscButton_Info[0].fy),
			int(m_tEscButton_Info[0].fcx), int(m_tEscButton_Info[0].fcy),
			GETS(CBitMapMgr)->FindImage(L"Button_Esc")->GetMemDC(),
			0, 0,
			int(m_tEscButton_Info[0].fcx), int(m_tEscButton_Info[0].fcy),
			RGB(1, 1, 1));

		TransparentBlt(_dc,
			int(m_tScroll_Info.fx), int(m_tScroll_Info.fy),
			int(m_tScroll_Info.fcx), int(m_tScroll_Info.fcy),
			GETS(CBitMapMgr)->FindImage(L"UI_Scroll")->GetMemDC(),
			0, 0,
			int(m_tScroll_Info.fcx), int(m_tScroll_Info.fcy),
			RGB(0, 0, 0));

		TransparentBlt(_dc,
			int(m_tStoreInven_Scroll_Info.fx), int(m_tStoreInven_Scroll_Info.fy),
			int(m_tStoreInven_Scroll_Info.fcx), int(m_tStoreInven_Scroll_Info.fcy),
			GETS(CBitMapMgr)->FindImage(L"UI_Scroll")->GetMemDC(),
			0, 0,
			int(m_tStoreInven_Scroll_Info.fcx), int(m_tStoreInven_Scroll_Info.fcy),
			RGB(0, 0, 0));

		ITEMITER iter = m_Store_ItemList.begin();
		float fx = 10.f;
		float fy = 125.f;
		int iIndex = 0;
		for (iter; iter != m_Store_ItemList.end(); ++iter, ++iIndex)
		{
			if (iIndex < 9)
			{
				(*iter)->Render(_dc);
				(*iter)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
				(*iter)->SetItemDescription_Render(_dc, m_tInfo.fx + 50.f, m_tInfo.fy + 125.f + (42.5f * iIndex));
			}			
		}

		//Slot Render
		iIndex = 0;
		SLOTITER iter_Slot = m_Store_SlotList.begin();
		SLOTITER iter_Slot_End = m_Store_SlotList.end();
		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot, ++iIndex)
		{
			if (iIndex < 9)
			{
				//(*iter_Slot)->Render(_dc);
				(*iter_Slot)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
			}
		}		
		Store_InvenSlotRender(_dc);
		
		//Store Inven
		Buy_StoreItem_Render(_dc);

		//Messo Render
		Messo_Present(_dc);
	}		
}

void CStore::Release(void)
{
	ITEMITER iter_Item = m_Store_ItemList.begin();
	ITEMITER iter_Item_End = m_Store_ItemList.end();
	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
	{
		delete *iter_Item;
	}
	m_Store_ItemList.clear();

	SLOTITER iter_Slot = m_Store_SlotList.begin();
	SLOTITER iter_Slot_End = m_Store_SlotList.end();
	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		SAFE_DELETE(*iter_Slot);
	}
	m_Store_SlotList.clear();

	SLOTITER iter_Inven_Slot = m_Store_InvenSlot_List.begin();
	SLOTITER iteR_Inven_Slot_End = m_Store_InvenSlot_List.end();
	for (iter_Inven_Slot; iter_Inven_Slot != iteR_Inven_Slot_End; ++iter_Inven_Slot)
	{
		SAFE_DELETE(*iter_Inven_Slot);
	}
	m_Store_InvenSlot_List.clear();
}

#pragma region Store Scroll
void CStore::Scroll_Move(void)
{
	//���콺�� Ŭ���ϰ� ������ ������ ��ũ�� �ٰ� �����̰� �Ѵ�.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tScroll_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bScrollMove = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bScrollMove == true)
		m_bScrollMove = false;

	if (m_bScrollMove == true)
	{
		if (m_tScroll_Info.fy < m_tInfo.fy + 134.f)
		{
			m_tScroll_Info.fy = m_tInfo.fy + 134.f;
			return;
		}			
			
		if (m_tScroll_Info.fy > 559.f)
		{
			m_tScroll_Info.fy = 559.f;
			return;
		}			

		//Scroll Move
		m_tScroll_Info.fy = pt.y - m_tScroll_Info.fcx / 2.f;
	}
}

void CStore::Item_View_Control(void)
{
	/*
	Scroll �����ӿ� ���� ������ ��ġ ��ȯ
	*/

	static float fCurScrollPosY = 0.f;
	static bool bMoveUp = false;

	if (m_tScroll_Info.fy < m_tInfo.fy + 134.f)
	{
		bMoveUp = false;
		return;
	}
	else if (m_tScroll_Info.fy > m_tInfo.fy + 134.f && m_tScroll_Info.fy < 559.f)
	{
		//��ũ�ѹ� ���� Change
		if (m_bScrollMove == true && m_tScroll_Info.fy > fCurScrollPosY)
			bMoveUp = false;
		else if (m_bScrollMove == true && m_tScroll_Info.fy < fCurScrollPosY)
			bMoveUp = true;

		ITEMITER iter = m_Store_ItemList.begin();
		ITEMITER iter_End = m_Store_ItemList.end();

		SLOTITER iter_Slot = m_Store_SlotList.begin();
		SLOTITER iter_Slot_End = m_Store_SlotList.end();

		float fx = 10.f;
		float fy = 125.f;		
		int	iIndex = 0;		

		//��ũ�ѹٸ� ������ �����ÿ�
		if (bMoveUp == false)
		{
			if (m_tScroll_Info.fy >= 315 && m_tScroll_Info.fy < 396)
			{
				for (iter; iter != iter_End;)
				{
					if ((*iter)->GetItemData()->m_dwOption == 0)
					{
						m_Store_ItemList.erase(iter);

						iter = m_Store_ItemList.begin();
						iter_End = m_Store_ItemList.end();
					}
					else
						++iter;
				}
				
				for (iter_Slot; iter_Slot != iter_Slot_End;)
				{
					if ((*iter_Slot)->GetSlotNumber() == 0)
					{
						m_Store_SlotList.erase(iter_Slot);

						iter_Slot = m_Store_SlotList.begin();
						iter_Slot_End = m_Store_SlotList.end();
					}
					else
						++iter_Slot;
				}

				//������ �巡�� �� �ÿ� ��ũ�� ���ذ� ���.
				fCurScrollPosY = m_tScroll_Info.fy;
				m_bScroll_Item_Check[0] = false;
			}
			else if (m_tScroll_Info.fy >= 396 && m_tScroll_Info.fy < 477)
			{
				for (iter; iter != iter_End;)
				{
					if ((*iter)->GetItemData()->m_dwOption == 1)
					{
						m_Store_ItemList.erase(iter);

						iter = m_Store_ItemList.begin();
						iter_End = m_Store_ItemList.end();
					}
					else
						++iter;
				}

				for (iter_Slot; iter_Slot != iter_Slot_End;)
				{
					if ((*iter_Slot)->GetSlotNumber() == 1)
					{
						m_Store_SlotList.erase(iter_Slot);

						iter_Slot = m_Store_SlotList.begin();
						iter_Slot_End = m_Store_SlotList.end();
					}
					else
						++iter_Slot;
				}

				//������ �巡�� �� �ÿ� ��ũ�� ���ذ� ���.
				fCurScrollPosY = m_tScroll_Info.fy;
				m_bScroll_Item_Check[1] = false;
			}
			else if (m_tScroll_Info.fy >= 477 && m_tScroll_Info.fy < 558)
			{
				for (iter; iter != iter_End;)
				{
					if ((*iter)->GetItemData()->m_dwOption == 2)
					{
						m_Store_ItemList.erase(iter);

						iter = m_Store_ItemList.begin();
						iter_End = m_Store_ItemList.end();
					}
					else
						++iter;
				}

				for (iter_Slot; iter_Slot != iter_Slot_End;)
				{
					if ((*iter_Slot)->GetSlotNumber() == 2)
					{
						m_Store_SlotList.erase(iter_Slot);

						iter_Slot = m_Store_SlotList.begin();
						iter_Slot_End = m_Store_SlotList.end();
					}
					else
						++iter_Slot;
				}

				//������ �巡�� �� �ÿ� ��ũ�� ���ذ� ���.
				fCurScrollPosY = m_tScroll_Info.fy;
				m_bScroll_Item_Check[2] = false;
			}
			else if (m_tScroll_Info.fy >= 558 && m_tScroll_Info.fy < 559)
			{
				for (iter; iter != iter_End;)
				{
					if ((*iter)->GetItemData()->m_dwOption == 3)
					{
						m_Store_ItemList.erase(iter);

						iter = m_Store_ItemList.begin();
						iter_End = m_Store_ItemList.end();
					}
					else
						++iter;
				}

				for (iter_Slot; iter_Slot != iter_Slot_End;)
				{
					if ((*iter_Slot)->GetSlotNumber() == 3)
					{
						m_Store_SlotList.erase(iter_Slot);

						iter_Slot = m_Store_SlotList.begin();
						iter_Slot_End = m_Store_SlotList.end();
					}
					else
						++iter_Slot;
				}

				//������ �巡�� �� �ÿ� ��ũ�� ���ذ� ���.
				fCurScrollPosY = m_tScroll_Info.fy;
				m_bScroll_Item_Check[3] = false;
			}
		}		

		//��ũ�� �ٸ� ���� �ø��ÿ� 
		if (bMoveUp == true)
		{
			if (m_tScroll_Info.fy <= 315 && m_tScroll_Info.fy > 234)
			{
				for (iter; iter != iter_End; ++iter)
				{
					if (!lstrcmp((*iter)->GetItemData()->m_szName, L"Armor"))
						break;
					else
					{
						if (m_bScroll_Item_Check[0] == false)
						{
							CItem* pArmor = new CArmor(L"Armor");
							((CArmor*)pArmor)->Initialize();
							((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
							pArmor->SetItemDescription(L"�⺻ ����");
							m_Store_ItemList.push_front(pArmor);

							CSlot* pSlot = new CSlot();
							pSlot->Initialize();
							pSlot->SetSlotNumber(0);
							pSlot->SetSize(32.f, 32.f);
							m_Store_SlotList.push_front(pSlot);

							m_bScroll_Item_Check[0] = true;
						}						
					}
				}		

				fCurScrollPosY = m_tScroll_Info.fy;
			}
			else if (m_tScroll_Info.fy <= 396 && m_tScroll_Info.fy > 315)
			{
				for (iter; iter != iter_End; ++iter)
				{
					if (!lstrcmp((*iter)->GetItemData()->m_szName, L"Armor1"))
						break;
					else
					{
						if (m_bScroll_Item_Check[1] == false)
						{
							CItem* pArmor = new CArmor(L"Armor1");
							((CArmor*)pArmor)->Initialize();
							((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
							pArmor->SetItemDescription(L"��� ����");
							m_Store_ItemList.push_front(pArmor);

							CSlot* pSlot = new CSlot();
							pSlot->Initialize();
							pSlot->SetSlotNumber(1);
							pSlot->SetSize(32.f, 32.f);
							m_Store_SlotList.push_front(pSlot);

							m_bScroll_Item_Check[1] = true;
						}						
					}
				}			

				fCurScrollPosY = m_tScroll_Info.fy;
			}
			else if (m_tScroll_Info.fy <= 477 && m_tScroll_Info.fy > 396)
			{
				for (iter; iter != iter_End; ++iter)
				{
					if (!lstrcmp((*iter)->GetItemData()->m_szName, L"Weapon"))
						break;
					else
					{
						if (m_bScroll_Item_Check[2] == false)
						{
							CItem* pWeapon = new CWeapon(L"Weapon");
							((CWeapon*)pWeapon)->Initialize();
							((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
							pWeapon->SetItemDescription(L"�⺻ ����");
							m_Store_ItemList.push_front(pWeapon);

							CSlot* pSlot = new CSlot();
							pSlot->Initialize();
							pSlot->SetSlotNumber(2);
							pSlot->SetSize(32.f, 32.f);
							m_Store_SlotList.push_front(pSlot);

							m_bScroll_Item_Check[2] = true;
						}					
					}
				}				

				fCurScrollPosY = m_tScroll_Info.fy;
			}
			else if (m_tScroll_Info.fy <= 558 && m_tScroll_Info.fy > 477)
			{
				for (iter; iter != iter_End; ++iter)
				{
					if (!lstrcmp((*iter)->GetItemData()->m_szName, L"Weapon1"))
						break;
					else
					{
						if (m_bScroll_Item_Check[3] == false)
						{
							CItem* pWeapon = new CWeapon(L"Weapon1");
							((CWeapon*)pWeapon)->Initialize();
							((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
							pWeapon->SetItemDescription(L"��� ����");
							m_Store_ItemList.push_front(pWeapon);

							CSlot* pSlot = new CSlot();
							pSlot->Initialize();
							pSlot->SetSlotNumber(3);
							pSlot->SetSize(32.f, 32.f);
							m_Store_SlotList.push_front(pSlot);

							m_bScroll_Item_Check[3] = true;
						}						
					}
				}		

				fCurScrollPosY = m_tScroll_Info.fy;
			}
		}	
	}		
}
#pragma endregion
#pragma region Store_Inven Scroll
void CStore::StoreInven_Scroll_Move(void)
{
	//���콺�� Ŭ���ϰ� ������ ������ ��ũ�� �ٰ� �����̰� �Ѵ�.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tStoreInven_Scroll_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bStoreInven_ScrollMove = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bStoreInven_ScrollMove == true)
		m_bStoreInven_ScrollMove = false;

	if (m_bStoreInven_ScrollMove == true)
	{
		if (m_tStoreInven_Scroll_Info.fy < m_tInfo.fy + 134.f)
		{
			m_tStoreInven_Scroll_Info.fy = m_tInfo.fy + 134.f;
			return;
		}

		if (m_tStoreInven_Scroll_Info.fy > 559.f)
		{
			m_tStoreInven_Scroll_Info.fy = 559.f;
			return;
		}

		//Scroll Move
		m_tStoreInven_Scroll_Info.fy = pt.y - m_tStoreInven_Scroll_Info.fcx / 2.f;
	}
}

void CStore::StoreInven_ItemView_Control(void)
{
	/*	Scroll �����ӿ� ���� ������ ��ġ ��ȯ	*/

	static float fCurScrollPosY = 0.f;
	static bool bMoveUp = false;

	//Inven �� �ִ� list ��������
	OBJITER iter_Inven = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_Inven_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();
	CUi* pInven = NULL;
	for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
	{
		if (((CUi*)(*iter_Inven))->GetUiType() == UI_INVEN)
		{
			pInven = ((CUi*)(*iter_Inven));
		}
	}

	list<CItem*>* InvenList = ((CInven*)pInven)->GetInven_ItemList();
	ITEMITER iter = InvenList->begin();
	ITEMITER iter_End = InvenList->end();

	/*
	Store Inven Slot ũ�Ⱑ �ϳ��� 42.5f �̴�.
	�׷� Store Inven�� List �ִ� �������� 42.5f�� ������ ��ũ�� ��������.
	Store Inven�� ������ ǥ�� ������ 9���̴�.
	*/

	//Scroll ����.
	if (m_tStoreInven_Scroll_Info.fy < m_tInfo.fy + 134.f)
	{
		bMoveUp = false;
		return;
	}
	else if (m_tStoreInven_Scroll_Info.fy > m_tInfo.fy + 134.f && m_tStoreInven_Scroll_Info.fy < 559.f)
	{
		//��ũ�ѹ� ���� Change(���� fCurScrollPosY ���� ���ŵǰ� ���� �ʾƼ� ���� ���� ������ ����)
		if (m_bStoreInven_ScrollMove == true && m_tStoreInven_Scroll_Info.fy > fCurScrollPosY)
			bMoveUp = false;
		else if (m_bStoreInven_ScrollMove == true && m_tStoreInven_Scroll_Info.fy < fCurScrollPosY)
			bMoveUp = true;		

		//���� ��ġ 315.f & ���� ��ġ�κ��� ������ ������ ���� ������ y ��.
		float fStoreInven_LimitPosY = 315.f + (42.5f * m_iStoreInven_ItemCount);
		
		//Limit Pos Y �� ��ũ�� ���� Y ���̶� ���� ������ ��� ������ ���°�
		//LimitPosY : 558 - 315 = 42.5f : x;
		//LimitPosY * x = 558 - 315 * 42.5f;
		//x = 558 - 315 * 42.5f / LimitPosY;
		int iStoreInven_ScrollDivision = int(((558 - 315) * 42.5f) / fStoreInven_LimitPosY);

		//�������� ������ Scroll ���̸� ������ -> �������� ��ũ�� ũ�Ⱑ ����
		int iRange_StroeInven_ScrollDivision = (558 - 315) / iStoreInven_ScrollDivision;
		
		//������ 0�� ��� Min & Max ������ ���Ѵ�.
		float fStoreInven_ScrollRange_Max = 0.f;
		float fStoreInven_ScrollRange_Min = 0.f;

		if (int(m_tStoreInven_Scroll_Info.fy) % iRange_StroeInven_ScrollDivision == 0)
		{
			fStoreInven_ScrollRange_Min = m_tStoreInven_Scroll_Info.fy - 21.25f;
			fStoreInven_ScrollRange_Max = m_tStoreInven_Scroll_Info.fy + 21.25f;
		}

		//��ũ�ѹٸ� ������ �����ÿ�
		if (bMoveUp == false)
		{
			if (fStoreInven_ScrollRange_Min < m_tStoreInven_Scroll_Info.fy
				&& fStoreInven_ScrollRange_Max > m_tStoreInven_Scroll_Info.fy
				&& m_iStoreInven_ItemCount >= 9)
			{
				//������ �ϳ��� ������� �Ѵ�.  list���� pop �� �������� Templist�� �־�д�.
				if (InvenList->front() != NULL)
				{
					ITEM tItem;
					memcpy_s(&tItem, sizeof(ITEM), InvenList->front()->GetItemData(), sizeof(ITEM));
					//ITEM tItem = *InvenList->front()->GetItemData();
					m_Temp_StoreInvenList.push_back(tItem);
					InvenList->pop_front();

					--m_iStoreInven_ItemCount;
				}

				fCurScrollPosY = m_tStoreInven_Scroll_Info.fy;
			}
		}

		//��ũ�� �ٸ� ���� �ø��ÿ�
		if (bMoveUp == true)
		{
			if (fStoreInven_ScrollRange_Min < m_tStoreInven_Scroll_Info.fy
				&& fStoreInven_ScrollRange_Max > m_tStoreInven_Scroll_Info.fy
				&& m_iStoreInven_ItemCount <= 9)
			{
				if (m_Temp_StoreInvenList.empty() == true)
					return;

				ITEM tItem;
				memcpy_s(&tItem, sizeof(ITEM), &m_Temp_StoreInvenList.back(), sizeof(ITEM));
				CItem* pItem = NULL;

				//Item ���� �з�
				if (!lstrcmp(tItem.m_szDescription, L"�⺻ ����"))
				{
					pItem = new CArmor(L"Armor");
					((CArmor*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"��� ����"))
				{
					pItem = new CArmor(L"Armor1");
					((CArmor*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"�⺻ ����"))
				{
					pItem = new CWeapon(L"Weapon");
					((CWeapon*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"��� ����"))
				{
					pItem = new CWeapon(L"Weapon1");
					((CWeapon*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"�⺻ �尩"))
				{
					pItem = new CGlove(L"Glove");
					((CGlove*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"��� �尩"))
				{
					pItem = new CGlove(L"Glove1");
					((CGlove*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"����"))
				{
					pItem = new CHelmet(L"Helmet");
					((CHelmet*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"������ ����"))
				{
					pItem = new CAccessory(L"Accessory", ITEM_RING);
					((CAccessory*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"��� ����"))
				{
					pItem = new CAccessory(L"Accessory1", ITEM_RING);
					((CAccessory*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"�⺻ �Ź�"))
				{
					pItem = new CShoes(L"Shoes");
					((CShoes*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"��� �Ź�"))
				{
					pItem = new CShoes(L"Shoes1");
					((CShoes*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"����� ����"))
				{
					pItem = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
					((CPotion*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"���� ����"))
				{
					pItem = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
					((CPotion*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				
				InvenList->push_front(pItem);
				m_Temp_StoreInvenList.pop_back();

				++m_iStoreInven_ItemCount;
				
				fCurScrollPosY = m_tStoreInven_Scroll_Info.fy;
			}						
		}
	}
}
#pragma endregion
#pragma region Buy Function
void CStore::Select_StoreItem(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	SLOTITER iter_Slot = m_Store_SlotList.begin();
	SLOTITER iter_Slot_End = m_Store_SlotList.end();

	ITEMITER iter_Item = m_Store_ItemList.begin();
	ITEMITER iter_Item_End = m_Store_ItemList.end();

	for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
	{
		if (PtInRect((*iter_Slot)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		{
			//���� ��Ʈ Ŭ���� ������ �����ؼ� ����.
			for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
			{
				if ((*iter_Slot)->GetSlotNumber() == (*iter_Item)->GetItemData()->m_dwOption)
				{
					m_pSelect_Item = (*iter_Item);
					break;
				}
			}
		}
	}
}

void CStore::Buy_Button_Click(void)
{
	//��ư Ŭ���� Buy ��� ����.
	//���߿� ���� �����ÿ��� ���� �Ұ��� ǥ�ø� �ؾߵȴ�.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tBuyButton_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
	{
		if(m_pSelect_Item != NULL)
			Buy_StoreItem(m_pSelect_Item);
	}	
}

void CStore::Buy_StoreItem(CItem * pItem)
{	
	static int iCount_Hp = 0;
	static int iCount_Mp = 0;

	//Consume Item Count
	if (pItem->GetItemData()->m_dwOption == 11)
		++iCount_Hp;

	if (pItem->GetItemData()->m_dwOption == 12)
		++iCount_Mp;

	//Inven ��������.
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CUi* pInven = NULL;

	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = ((CUi*)(*iter));
			break;
		}
	}

	//Inven�� ������ push
	((CInven*)pInven)->Set_StoreCheck(true);

	//Store Inven�� Potion ���Խÿ� ��ø �ǵ���
	ITEMITER iter_Item = ((CInven*)pInven)->GetInven_ItemList()->begin();
	ITEMITER iter_Item_End = ((CInven*)pInven)->GetInven_ItemList()->end();
		
	if (m_bPotion_Check[0] == false && pItem->GetItemData()->m_dwOption == 11)
	{
		pItem->SetItem_Count(iCount_Hp);
		((CInven*)pInven)->Set_InvenItem(pItem);
		
		//Slot
		float fx = 285.f;
		float fy = 125.f;
		CSlot* pSlot = new CSlot();
		pSlot->Initialize();
		pSlot->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * ((CInven*)pInven)->GetInven_ItemList()->size()));
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetSlotNumber(pItem->GetItemData()->m_dwOption);

		//Slot Item Data(Store�� ���� ��ȣ�� Inven�� ���� ��ȣ�� ���ϱ� ���� �־��ش�.)
		SLOT tSlot;
		tSlot.tItem.m_dwInven_SlotNumber = m_iStoreInven_ItemCount;
		pSlot->SetSlotData(tSlot.tItem);
		m_Store_InvenSlot_List.push_back(pSlot);
		
		m_bPotion_Check[0] = true;
	}
	
	if (m_bPotion_Check[1] == false && pItem->GetItemData()->m_dwOption == 12)
	{
		pItem->SetItem_Count(iCount_Mp);
		((CInven*)pInven)->Set_InvenItem(pItem);

		//Slot
		float fx = 285.f;
		float fy = 125.f;
		CSlot* pSlot = new CSlot();
		pSlot->Initialize();
		pSlot->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * ((CInven*)pInven)->GetInven_ItemList()->size()));
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetSlotNumber(pItem->GetItemData()->m_dwOption);

		//Slot Item Data(Store�� ���� ��ȣ�� Inven�� ���� ��ȣ�� ���ϱ� ���� �־��ش�.)
		SLOT tSlot;
		tSlot.tItem.m_dwInven_SlotNumber = m_iStoreInven_ItemCount;
		pSlot->SetSlotData(tSlot.tItem);
		m_Store_InvenSlot_List.push_back(pSlot);
		
		m_bPotion_Check[1] = true;
	}

	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
	{
		if (pItem->GetItemData()->m_dwOption == 11)
		{
			if ((*iter_Item)->GetItemData()->m_dwOption == 11 && m_bPotion_Check[0] == true)
			{
				(*iter_Item)->SetItem_Count(iCount_Hp);
				break;
			}
		}

		if (pItem->GetItemData()->m_dwOption == 12)
		{
			if ((*iter_Item)->GetItemData()->m_dwOption == 12 && m_bPotion_Check[1] == true)
			{
				(*iter_Item)->SetItem_Count(iCount_Mp);
				break;
			}
		}
	}

	if(pItem->GetItemData()->m_dwOption != 11 && pItem->GetItemData()->m_dwOption != 12)
		((CInven*)pInven)->Set_InvenItem(pItem);
	
	//Inven Item Classification
	((CInven*)pInven)->Inven_ItemClassification(pItem);
	
	if (((CInven*)pInven)->Get_InvenItem_CreateCheck() == true)
		((CInven*)pInven)->Set_InvenItem_CreateCheck(false);

	//Store Inven Slot 
	if (pItem->GetItemData()->m_dwOption != 11 && pItem->GetItemData()->m_dwOption != 12)
	{
		float fx = 285.f;
		float fy = 125.f;
		CSlot* pSlot = new CSlot();
		pSlot->Initialize();
		pSlot->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * ((CInven*)pInven)->GetInven_ItemList()->size()));
		pSlot->SetSize(32.f, 32.f);
		pSlot->SetSlotNumber(pItem->GetItemData()->m_dwOption);

		//Slot Item Data(Store�� ���� ��ȣ�� Inven�� ���� ��ȣ�� ���ϱ� ���� �־��ش�.)
		SLOT tSlot;
		tSlot.tItem.m_dwInven_SlotNumber = m_iStoreInven_ItemCount;
		pSlot->SetSlotData(tSlot.tItem);
		m_Store_InvenSlot_List.push_back(pSlot);
	}	

	//Store Inven Item ���� ����.
	++m_iStoreInven_ItemCount;
}

void CStore::Buy_StoreItem_Render(HDC _dc)
{
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CUi* pInven = NULL;

	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = ((CUi*)(*iter));
		}
	}

	//���� ������ ���� Inven Render On
	if (m_bVisible == true)
		((CInven*)pInven)->Set_StoreCheck(true);

	//Inven Item List ��������
	if (((CInven*)pInven)->Get_StoreCheck() == true)
	{
		list<CItem*>* InvenList = ((CInven*)pInven)->GetInven_ItemList();

		ITEMITER iter_Inven = InvenList->begin();
		ITEMITER iter_Inven_End = InvenList->end();
		float fx = 285.f;
		float fy = 125.f;
		int   iIndex = 0;

		//Consume Item Count Render
		m_myConsumeItem_Font = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"����");
		HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

		TCHAR szHpPotion_Count[100] = { 0 };
		TCHAR szMpPotion_Count[100] = { 0 };

		for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven, ++iIndex)
		{
			if (iIndex < 9)
			{
				(*iter_Inven)->Render(_dc);
				(*iter_Inven)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
				(*iter_Inven)->SetSaleItemDescription_Render(_dc, m_tInfo.fx + fx + 40.f, m_tInfo.fy + fy + (42.5f * iIndex));
			
				if ((*iter_Inven)->GetItemData()->m_dwOption == 11)
				{
					_stprintf_s(szHpPotion_Count, _countof(szHpPotion_Count), L"%d", (*iter_Inven)->GetItemData()->m_iCount);
					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, int((*iter_Inven)->GetInfo()->fx + 28.f), int((*iter_Inven)->GetInfo()->fy + 23.f), szHpPotion_Count, lstrlen(szHpPotion_Count));
					SelectObject(_dc, oldFont);
				}

				if ((*iter_Inven)->GetItemData()->m_dwOption == 12)
				{
					_stprintf_s(szMpPotion_Count, _countof(szMpPotion_Count), L"%d", (*iter_Inven)->GetItemData()->m_iCount);

					SetBkMode(_dc, TRANSPARENT);
					TextOut(_dc, int((*iter_Inven)->GetInfo()->fx + 28.f), int((*iter_Inven)->GetInfo()->fy + 23.f), szMpPotion_Count, lstrlen(szMpPotion_Count));
					SelectObject(_dc, oldFont);
				}
			}
		}		
	}	
}
#pragma endregion
#pragma region Sale Function
void CStore::Select_StoreInvenItem(void)
{
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CUi* pInven = NULL;

	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = ((CUi*)(*iter));
			break;
		}
	}

	if (((CInven*)pInven)->Get_StoreCheck() == true)
	{
		list<CItem*>* InvenList = ((CInven*)pInven)->GetInven_ItemList();

		POINT pt;
		pt = CMouse::GetPos();

		SLOTITER iter_Slot = m_Store_InvenSlot_List.begin();
		SLOTITER iter_Slot_End = m_Store_InvenSlot_List.end();

		ITEMITER iter_Inven = InvenList->begin();
		ITEMITER iter_Inven_End = InvenList->end();

		for (iter_Slot; iter_Slot != iter_Slot_End; ++iter_Slot)
		{
			if (PtInRect((*iter_Slot)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
				{
					if ((*iter_Slot)->GetSlotNumber() == (*iter_Inven)->GetItemData()->m_dwOption)
					{
						m_pSelect_Item = (*iter_Inven);
						break;
					}
				}
			}
		}
	}
}

void CStore::Sale_Button_Click(void)
{
	//��ư Ŭ���� Sale ��� ����.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tSaleButton_Rect, pt) && (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON)))
	{
		if (m_pSelect_Item != NULL)
		{
			Sale_StoreInven_Item(m_pSelect_Item);
			m_bSale_Check = false;
		}
	}
}

void CStore::Sale_StoreInven_Item(CItem * pItem)
{
	/* ���� �κ����� ������ �ȶ� �κ�â�� �ִ� ������ ������� �ϴ� ��� �̿ϼ�(�߾ȵ�) */

	//Inven ��������.
	OBJITER iter = GETS(CObjMgr)->GetObjList(OBJ_UI)->begin();
	OBJITER iter_End = GETS(CObjMgr)->GetObjList(OBJ_UI)->end();

	CUi* pInven = NULL;
	CPlayer* pPlayer = NULL;

	pPlayer = ((CPlayer*)(GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->back()));

	for (iter; iter != iter_End; ++iter)
	{
		if (((CUi*)(*iter))->GetUiType() == UI_INVEN)
		{
			pInven = ((CUi*)(*iter));
		}
	}

	//Inven�� �ִ� ������ ����
	if (m_pSelect_Item->GetItemData()->m_dwOption == 0 || m_pSelect_Item->GetItemData()->m_dwOption == 1
		|| m_pSelect_Item->GetItemData()->m_dwOption == 2 || m_pSelect_Item->GetItemData()->m_dwOption == 3
		|| m_pSelect_Item->GetItemData()->m_dwOption == 4 || m_pSelect_Item->GetItemData()->m_dwOption == 5
		|| m_pSelect_Item->GetItemData()->m_dwOption == 6 || m_pSelect_Item->GetItemData()->m_dwOption == 7
		|| m_pSelect_Item->GetItemData()->m_dwOption == 8 || m_pSelect_Item->GetItemData()->m_dwOption == 9
		|| m_pSelect_Item->GetItemData()->m_dwOption == 10)
	{
		ITEMITER iter_InvenEquip = ((CInven*)pInven)->GetInevn_EquipItemList()->begin();
		ITEMITER iter_InvenEquip_End = ((CInven*)pInven)->GetInevn_EquipItemList()->end();

		SLOTITER iter_InvenSlot = ((CInven*)pInven)->GetInven_SlotList()->begin();
		SLOTITER iter_InvenSlot_End = ((CInven*)pInven)->GetInven_SlotList()->end();
		SLOTITER iter_StoreSlot = m_Store_InvenSlot_List.begin();
		SLOTITER iter_StoreSlot_End = m_Store_InvenSlot_List.end();

		//Inven�� ������ 1�� �϶�.
		if (((CInven*)pInven)->GetInevn_EquipItemList()->size() == 1)
		{
			for (iter_StoreSlot; iter_StoreSlot != iter_StoreSlot_End; ++iter_StoreSlot)
			{
				for (iter_InvenSlot; iter_InvenSlot != iter_InvenSlot_End; ++iter_InvenSlot)
				{
					//Inven�� �ִ� Slot�̶� Store�� �ִ� Slot �ѹ��� ������
					if ((*iter_StoreSlot)->GetSlotData()->m_dwInven_SlotNumber == (*iter_InvenSlot)->GetSlotNumber())
					{
						for (iter_InvenEquip; iter_InvenEquip != iter_InvenEquip_End;)
						{
							//Inven Equip�� ������ �� InvenSlotNumber�� ���� �������� �����.
							if ((*iter_InvenEquip)->GetItemData()->m_dwInven_SlotNumber == (*iter_InvenSlot)->GetSlotNumber())
							{
								((CInven*)pInven)->GetInevn_EquipItemList()->erase(iter_InvenEquip);
								iter_InvenEquip = ((CInven*)pInven)->GetInevn_EquipItemList()->begin();
								break;
							}
							else
								++iter_InvenEquip;
						}
					}
				}
			}
		}

		//�ٽ� Iter �ʱ�ȭ
		iter_StoreSlot = m_Store_InvenSlot_List.begin();
		iter_StoreSlot_End = m_Store_InvenSlot_List.end();
		iter_InvenEquip = ((CInven*)pInven)->GetInevn_EquipItemList()->begin();
		iter_InvenEquip_End = ((CInven*)pInven)->GetInevn_EquipItemList()->end();
		iter_InvenSlot = ((CInven*)pInven)->GetInven_SlotList()->begin();
		iter_InvenSlot_End = ((CInven*)pInven)->GetInven_SlotList()->end();

		//Store Inven�� ���Ե� Item ������ Inven â�� �ִ� ������ ���ؼ� ���� �͸� Invenâ���� ����� ���.
		if (m_Store_InvenSlot_List.size() > 1)
		{
			for (iter_InvenSlot; iter_InvenSlot != iter_InvenSlot_End; ++iter_InvenSlot)
			{
				//Inven�� �ִ� Slot�̶� Store�� �ִ� Slot �ѹ��� ������
				if ((*iter_StoreSlot)->GetSlotData()->m_dwInven_SlotNumber == (*iter_InvenSlot)->GetSlotNumber())
				{
					for (iter_InvenEquip; iter_InvenEquip != iter_InvenEquip_End;)
					{
						//Inven Equip�� ������ �� InvenSlotNumber�� ���� �������� �����.
						if ((*iter_InvenEquip)->GetItemData()->m_dwInven_SlotNumber == (*iter_InvenSlot)->GetSlotNumber())
						{
							//������ �������� SlotNumber�� �̸� ����.
							//DWORD dwTemp_SlotNum = (*iter_InvenEquip)->GetItemData()->m_dwInven_SlotNumber;
							
							((CInven*)pInven)->GetInevn_EquipItemList()->erase(iter_InvenEquip);
							iter_InvenEquip = ((CInven*)pInven)->GetInevn_EquipItemList()->begin();
							//(*iter_InvenEquip)->SetItem_SlotNumber(dwTemp_SlotNum);
							break;
						}
						else
							++iter_InvenEquip;
					}
				}
			}			
		}
	}
	else if (m_pSelect_Item->GetItemData()->m_dwOption == 11 || m_pSelect_Item->GetItemData()->m_dwOption == 12)
	{
		//Consume â�� �ִ� �����۵��� ������ ���̰�. ������ 1���϶� ������� ������ �ȴ�.
		//�̰͵� ���� ������ �� ������ ���� �ؾߵȴ�.
	}

	list<CItem*>* InvenItemList = ((CInven*)pInven)->GetInven_ItemList();
	ITEMITER iter_Inven = InvenItemList->begin();
	ITEMITER iter_Inven_End = InvenItemList->end();

	SLOTITER iter_Slot = m_Store_InvenSlot_List.begin();
	SLOTITER iter_Slot_End = m_Store_InvenSlot_List.end();

	//Store Inven�� ������ delete
	for (iter_Inven; iter_Inven != iter_Inven_End;)
	{
		if ((*iter_Inven)->GetItemData()->m_dwOption == m_pSelect_Item->GetItemData()->m_dwOption && m_bSale_Check == false)
		{
			//Sale Price�� Player Money�� ���� ��Ų��.
			pPlayer->SetMoney((*iter_Inven)->GetItemData()->m_iSalePrice);

			//Hp Potion �϶�
			if (m_pSelect_Item->GetItemData()->m_dwOption == 11)
			{
				if (m_pSelect_Item->GetItemData()->m_iCount > 1)
				{
					int iHp_Potion_Count = m_pSelect_Item->GetItemData()->m_iCount;
					--iHp_Potion_Count;
					m_pSelect_Item->SetItem_Count(iHp_Potion_Count);
				}
				else if (m_pSelect_Item->GetItemData()->m_iCount <= 1)
				{
					InvenItemList->erase(iter_Inven);
					iter_Inven = InvenItemList->begin();
				}
			}

			//Mp Potion �϶�
			if (m_pSelect_Item->GetItemData()->m_dwOption == 12)
			{
				if (m_pSelect_Item->GetItemData()->m_iCount > 1)
				{
					int iMp_Potion_Count = m_pSelect_Item->GetItemData()->m_iCount;
					--iMp_Potion_Count;
					m_pSelect_Item->SetItem_Count(iMp_Potion_Count);
				}
				else if (m_pSelect_Item->GetItemData()->m_iCount <= 1)
				{
					InvenItemList->erase(iter_Inven);
					iter_Inven = InvenItemList->begin();
				}
			}

			//m_pSelect_Item �� Potion�� �ƴҶ�
			if (m_pSelect_Item->GetItemData()->m_dwOption != 11 && m_pSelect_Item->GetItemData()->m_dwOption != 12)
			{
				InvenItemList->erase(iter_Inven);
				iter_Inven = InvenItemList->begin();
			}

			//Slot ����.
			for (iter_Slot; iter_Slot != iter_Slot_End;)
			{
				if ((*iter_Slot)->GetSlotNumber() == m_pSelect_Item->GetItemData()->m_dwOption)
				{
					m_Store_InvenSlot_List.erase(iter_Slot);
					iter_Slot = m_Store_InvenSlot_List.begin();
					break;
				}
				else
					++iter_Slot;
			}

			m_bSale_Check = true;
		}
		else
			++iter_Inven;
	}

	//Store Inven Item ���� ����.
	--m_iStoreInven_ItemCount;
}
#pragma endregion

#pragma region Store Slot 
void CStore::Store_InvenSlotUpdate(void)
{
	SLOTITER iter_StoreInven_Slot = m_Store_InvenSlot_List.begin();
	SLOTITER iter_StoreInven_Slot_End = m_Store_InvenSlot_List.end();
	for (iter_StoreInven_Slot; iter_StoreInven_Slot != iter_StoreInven_Slot_End; ++iter_StoreInven_Slot)
		(*iter_StoreInven_Slot)->Update();
}

void CStore::Store_InvenSlotRender(HDC _dc)
{
	//Store Inven Slot Render
	float fInven_x = 285.f;
	float fInven_y = 125.f;
	int   Inven_iIndex = 0;
	SLOTITER iter_StoreInven_Slot = m_Store_InvenSlot_List.begin();
	SLOTITER iter_StoreInven_Slot_End = m_Store_InvenSlot_List.end();
	for (iter_StoreInven_Slot; iter_StoreInven_Slot != iter_StoreInven_Slot_End; ++iter_StoreInven_Slot, ++Inven_iIndex)
	{
		if (Inven_iIndex < 9)
		{
			(*iter_StoreInven_Slot)->Render(_dc);
			(*iter_StoreInven_Slot)->SetPos(m_tInfo.fx + fInven_x, m_tInfo.fy + fInven_y + (42.5f * Inven_iIndex));
		}
	}
}
#pragma endregion

void CStore::Messo_Present(HDC _dc)
{
	CPlayer* pPlayer = NULL;
	pPlayer = ((CPlayer*)(GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->back()));

	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"����");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

	//Money
	TCHAR szMesso[128] = { 0 };
	_stprintf_s(szMesso, _countof(szMesso), L"%d", pPlayer->GetMoney());

	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, int(m_tInfo.fx + 420.f), int(m_tInfo.fy + 57.f), szMesso, lstrlen(szMesso));
	SelectObject(_dc, oldFont);
}
