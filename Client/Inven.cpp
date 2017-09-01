#include "stdafx.h"
#include "Inven.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"

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
	m_bInvenMode[INVEN_EQUIP] = true;
	for (int i = 1; i < INVEN_END; ++i)
		m_bInvenMode[i] = false;
}

CInven::~CInven(void)
{
	Release();
}

void CInven::Initialize(void)
{
	m_tInfo.fx = 460.f;
	m_tInfo.fy = 160.f;
	m_tInfo.fcx = 172.f;
	m_tInfo.fcy = 335.f;
	m_eRenderType = RENDER_UI;

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

	m_dwTime = GetTickCount();
}

int CInven::Update(void)
{
	//Inven Move Rect
	m_tInvenMove_Rect.left		= long(m_tInfo.fx + (172.f / 2.f) - 172.f / 2.f);
	m_tInvenMove_Rect.right		= long(m_tInfo.fx + (172.f / 2.f) + 172.f / 2.f);
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
		Inven_EscButton_Click();
	}

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

		/*
		Rectangle(_dc,
			m_tInvenMove_Rect.left,
			m_tInvenMove_Rect.top,
			m_tInvenMove_Rect.right,
			m_tInvenMove_Rect.bottom);		
		*/				
	}	
}

void CInven::Release(void)
{	
	ITEMITER iter_Equip = m_Inven_EquipList.begin();
	ITEMITER iter_Consume = m_Inven_ConsumeList.begin();
	ITEMITER iter_Etc = m_Inven_EtcList.begin();

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
	static bool bMove = false;
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tInvenMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		bMove = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && bMove == true)
		bMove = false;

	if (bMove == true)
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

void CInven::Inven_SelectMenu(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tInvenEquip_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
	{
		m_bInvenMode[INVEN_EQUIP] = true;
		m_bInvenMode[INVEN_CONSUME] = false;
		m_bInvenMode[INVEN_ETC] = false;
	}
	else if (PtInRect(&m_tInvenConsume_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
	{
		m_bInvenMode[INVEN_CONSUME] = true;
		m_bInvenMode[INVEN_EQUIP] = false;
		m_bInvenMode[INVEN_ETC] = false;
	}
	else if (PtInRect(&m_tInvenEtc_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
	{
		m_bInvenMode[INVEN_ETC] = true;
		m_bInvenMode[INVEN_CONSUME] = false;
		m_bInvenMode[INVEN_EQUIP] = false;
	}
}

void CInven::Inven_ItemClassification(void)
{
	//아이템을 종류별로 구별 한다.
	ITEMITER iter = m_Inven_ItemList.begin();
	ITEMITER iter_End = m_Inven_ItemList.end();

	for (iter; iter != iter_End; ++iter)
	{
		if ((*iter)->GetItemData()->m_dwOption == 0 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pArmor = new CArmor(L"Armor");
			((CArmor*)pArmor)->Initialize();
			((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 500, 0);
			pArmor->SetItemDescription(L"기본 갑옷");
			m_Inven_EquipList.push_back(pArmor);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 1 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pArmor = new CArmor(L"Armor1");
			((CArmor*)pArmor)->Initialize();
			((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
			pArmor->SetItemDescription(L"고급 갑옷");
			m_Inven_EquipList.push_back(pArmor);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 2 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pWeapon = new CWeapon(L"Weapon");
			((CWeapon*)pWeapon)->Initialize();
			((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
			pWeapon->SetItemDescription(L"기본 무기");
			m_Inven_EquipList.push_back(pWeapon);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 3 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pWeapon = new CWeapon(L"Weapon1");
			((CWeapon*)pWeapon)->Initialize();
			((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
			pWeapon->SetItemDescription(L"고급 무기");
			m_Inven_EquipList.push_back(pWeapon);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 4 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pGlove = new CGlove(L"Glove");
			((CGlove*)pGlove)->Initialize();
			((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
			pGlove->SetItemDescription(L"기본 장갑");
			m_Inven_EquipList.push_back(pGlove);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 5 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pGlove = new CGlove(L"Glove1");
			((CGlove*)pGlove)->Initialize();
			((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
			pGlove->SetItemDescription(L"고급 장갑");
			m_Inven_EquipList.push_back(pGlove);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 6 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pHelmet = new CHelmet(L"Helmet");
			((CHelmet*)pHelmet)->Initialize();
			((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
			pHelmet->SetItemDescription(L"투구");
			m_Inven_EquipList.push_back(pHelmet);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 7 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
			((CAccessory*)pAcs)->Initialize();
			((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
			pAcs->SetItemDescription(L"메이플 반지");
			m_Inven_EquipList.push_back(pAcs);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 8 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pAcs = new CAccessory(L"Accessory1", ITEM_RING);
			((CAccessory*)pAcs)->Initialize();
			((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
			pAcs->SetItemDescription(L"고급 반지");
			m_Inven_EquipList.push_back((*iter));

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 9 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pShoes = new CShoes(L"Shoes");
			((CShoes*)pShoes)->Initialize();
			((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
			pShoes->SetItemDescription(L"기본 신발");
			m_Inven_EquipList.push_back(pShoes);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 10 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pShoes = new CShoes(L"Shoes1");
			((CShoes*)pShoes)->Initialize();
			((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
			pShoes->SetItemDescription(L"고급 신발");
			m_Inven_EquipList.push_back((*iter));

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 11 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
			((CPotion*)pPotion)->Initialize();
			((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
			pPotion->SetItemDescription(L"생명력 포션");
			m_Inven_ConsumeList.push_back(pPotion);

			m_bInvenItem_CreateCheck = true;
		}
		else if ((*iter)->GetItemData()->m_dwOption == 12 && m_bInvenItem_CreateCheck == false)
		{
			CItem* pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
			((CPotion*)pPotion)->Initialize();
			((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
			pPotion->SetItemDescription(L"마나 포션");
			m_Inven_ConsumeList.push_back(pPotion);

			m_bInvenItem_CreateCheck = true;
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
			if (iSize % 4 == 0)
				fOffsetPosY = fOffsetPosY + 42.5f;
			
			(*iter_Equip)->Render(_dc);
			(*iter_Equip)->SetPos(m_tInfo.fx + 9.f + (38.f * iIndex), m_tInfo.fy + 52.f + (fOffsetPosY));
		}

		system("cls");
		cout << m_Inven_EquipList.size() << endl;
		cout << iSize % 4 << endl;
	}
	else if (m_bInvenMode[INVEN_CONSUME])
	{
		//소비 목록
	}
	else if (m_bInvenMode[INVEN_ETC])
	{
		//기타 목록
	}	
}

void CInven::Save_InvenData(void)
{
}

void CInven::Load_InvenData(void)
{
}
