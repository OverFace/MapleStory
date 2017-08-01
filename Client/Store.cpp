#include "stdafx.h"
#include "Store.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"

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

CStore::CStore(void)
{
	m_eUiType = UI_STORE;
	ZeroMemory(&m_tEscButton_Rect, sizeof(RECT));
	ZeroMemory(&m_tEscButton_Info, sizeof(INFO));
	ZeroMemory(&m_tScroll_Rect, sizeof(RECT));
	ZeroMemory(&m_tScroll_Info, sizeof(INFO));

	m_pStore_Npc = NULL;
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

	//Esc Button
	m_tEscButton_Info.fx = m_tInfo.fx + m_tInfo.fcx / 2.f;
	m_tEscButton_Info.fy = m_tInfo.fy + 10.f;
	m_tEscButton_Info.fcx = 9.f;
	m_tEscButton_Info.fcy = 9.f;

	//Scroll 
	m_tScroll_Info.fx = m_tInfo.fx + 258.f;
	m_tScroll_Info.fy = m_tInfo.fy + 134.f;
	m_tScroll_Info.fcx = 9.f;
	m_tScroll_Info.fcy = 26.f;

#pragma region Item List
	//Store Item
	//----------------------------------------------------------------------------------
	//Armor  (Armor, Armor1)
	CItem* pArmor = new CArmor(L"Armor");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 0);	
	pArmor->SetPos(m_tInfo.fx + 10.f, m_tInfo.fy + 125.f);
	pArmor->SetItemDescription(L"기본 갑옷");
	m_Store_ItemList.push_back(pArmor);

	pArmor = new CArmor(L"Armor1");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 0);
	pArmor->SetPos(m_tInfo.fx + 10.f, m_tInfo.fy + 168.f);
	pArmor->SetItemDescription(L"고급 갑옷");
	m_Store_ItemList.push_back(pArmor);
	//----------------------------------------------------------------------------------
	//Weapon (Weapon, Weapon1)
	CItem* pWeapon = new CWeapon(L"Weapon");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 0);
	pWeapon->SetItemDescription(L"기본 무기");
	m_Store_ItemList.push_back(pWeapon);

	pWeapon = new CWeapon(L"Weapon1");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 0);
	pWeapon->SetItemDescription(L"고급 무기");
	m_Store_ItemList.push_back(pWeapon);
	//----------------------------------------------------------------------------------
	//Glove (Glove, Glove1)
	CItem* pGlove = new CGlove(L"Glove");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 0);
	pGlove->SetItemDescription(L"기본 장갑");
	m_Store_ItemList.push_back(pGlove);

	pGlove = new CGlove(L"Glove1");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 0);
	pGlove->SetItemDescription(L"고급 장갑");
	m_Store_ItemList.push_back(pGlove);
	//----------------------------------------------------------------------------------
	//Helmet
	CItem* pHelmet = new CHelmet(L"Helmet");
	((CHelmet*)pHelmet)->Initialize();
	((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 0);
	pHelmet->SetItemDescription(L"투구");
	m_Store_ItemList.push_back(pHelmet);
	//----------------------------------------------------------------------------------
	//Accessory
	CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 0);
	pAcs->SetItemDescription(L"메이플 반지");
	m_Store_ItemList.push_back(pAcs);

	pAcs = new CAccessory(L"Accessory1", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 0);
	pAcs->SetItemDescription(L"고급 반지");
	m_Store_ItemList.push_back(pAcs);
	//----------------------------------------------------------------------------------
	//Shoes
	CItem* pShoes = new CShoes(L"Shoes");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 0);
	pShoes->SetItemDescription(L"기본 신발");
	m_Store_ItemList.push_back(pShoes);

	pShoes = new CShoes(L"Shoes1");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 0);
	pShoes->SetItemDescription(L"고급 신발");
	m_Store_ItemList.push_back(pShoes);
	//----------------------------------------------------------------------------------
	//Potion
	CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 0);
	pPotion->SetItemDescription(L"생명력 포션");
	m_Store_ItemList.push_back(pPotion);

	pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 0);
	pPotion->SetItemDescription(L"마나 포션");
	m_Store_ItemList.push_back(pPotion);
	//----------------------------------------------------------------------------------

	float fx = 10.f;
	float fy = 125.f;
	int	iIndex = 0;
	ITEMITER iter = m_Store_ItemList.begin();
	for (iter; iter != m_Store_ItemList.end(); ++iter, ++iIndex)
	{
		(*iter)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
	}

	int iViewIndex = 0;
	ITEMITER iter_Item = m_Store_ItemList.begin();
	for (iter_Item; iter_Item != m_Store_ItemList.end(); ++iter_Item, ++iViewIndex)
	{
		if (iViewIndex < 9)
		{
			m_Store_ViewList.push_back((*iter_Item));
		}
	}
#pragma endregion

	m_eRenderType = RENDER_UI;
}

int CStore::Update(void)
{
	//Button Rect
	m_tEscButton_Rect.left = long(m_tEscButton_Info.fx + (m_tEscButton_Info.fcx / 2.f) - m_tEscButton_Info.fcx / 2);
	m_tEscButton_Rect.right = long(m_tEscButton_Info.fx + (m_tEscButton_Info.fcx / 2.f) + m_tEscButton_Info.fcx / 2);
	m_tEscButton_Rect.top = long(m_tEscButton_Info.fy + (m_tEscButton_Info.fcy / 2.f) - m_tEscButton_Info.fcy / 2);
	m_tEscButton_Rect.bottom = long(m_tEscButton_Info.fy + (m_tEscButton_Info.fcy / 2.f) + m_tEscButton_Info.fcy / 2);

	//Scroll Rect
	m_tScroll_Rect.left = long(m_tScroll_Info.fx + (m_tScroll_Info.fcx / 2.f) - m_tScroll_Info.fcx / 2);
	m_tScroll_Rect.right = long(m_tScroll_Info.fx + (m_tScroll_Info.fcx / 2.f) + m_tScroll_Info.fcx / 2);
	m_tScroll_Rect.top = long(m_tScroll_Info.fy + (m_tScroll_Info.fcy / 2.f) - m_tScroll_Info.fcy / 2);
	m_tScroll_Rect.bottom = long(m_tScroll_Info.fy + (m_tScroll_Info.fcy / 2.f) + m_tScroll_Info.fcy / 2);

	if (m_bVisible == true)
	{
		Scroll_Move();
		Item_View_Control();
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
			int(m_tEscButton_Info.fx), int(m_tEscButton_Info.fy),
			int(m_tEscButton_Info.fcx), int(m_tEscButton_Info.fcy),
			GETS(CBitMapMgr)->FindImage(L"Button_Esc")->GetMemDC(),
			0, 0,
			int(m_tEscButton_Info.fcx), int(m_tEscButton_Info.fcy),
			RGB(1, 1, 1));

		TransparentBlt(_dc,
			int(m_tScroll_Info.fx), int(m_tScroll_Info.fy),
			int(m_tScroll_Info.fcx), int(m_tScroll_Info.fcy),
			GETS(CBitMapMgr)->FindImage(L"UI_Scroll")->GetMemDC(),
			0, 0,
			int(m_tScroll_Info.fcx), int(m_tScroll_Info.fcy),
			RGB(0, 0, 0));

		/*
		Rectangle(_dc,
			m_tEscButton_Rect.left,
			m_tEscButton_Rect.top,
			m_tEscButton_Rect.right,
			m_tEscButton_Rect.bottom);

		Rectangle(_dc,
			m_tScroll_Rect.left,
			m_tScroll_Rect.top,
			m_tScroll_Rect.right,
			m_tScroll_Rect.bottom);		
		*/			

		/*
		list<CItem*>::iterator iter_Item = m_Store_ItemList.begin();
		list<CItem*>::iterator iter_Item_End = m_Store_ItemList.end();

		int	iIndex = 0;
		for (iter_Item; iter_Item != iter_Item_End; ++iter_Item, ++iIndex)
		{
			(*iter_Item)->Render(_dc);
			(*iter_Item)->SetItemDescription_Render(_dc, m_tInfo.fx + 50.f, m_tInfo.fy + 125.f + (42.5f * iIndex));
		}
		*/

		ITEMITER iter = m_Store_ViewList.begin();
		int iIndex = 0;
		for (iter; iter != m_Store_ViewList.end(); ++iter, ++iIndex)
		{
			(*iter)->Render(_dc);
			(*iter)->SetItemDescription_Render(_dc, m_tInfo.fx + 50.f, m_tInfo.fy + 125.f + (42.5f * iIndex));
		}
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
}

void CStore::Scroll_Move(void)
{
	//마우스로 클릭하고 밑으로 내릴때 스크롤 바가 움직이게 한다.
	static bool bMove = false;
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tScroll_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		bMove = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && bMove == true)
		bMove = false;

	if (bMove == true)
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
	if (m_tScroll_Info.fy <= m_tInfo.fy + 134.f)
	{
		return;
	}
	else if (m_tScroll_Info.fy > 559.f)
	{
		/*
		int iIndex = 0;
		ITEMITER iter = m_Store_ViewList.begin();
		ITEMITER iter_End = m_Store_ViewList.end();

		for (iter; iter != iter_End; ++iter, ++iIndex)
		{
			if (iIndex <= 3)
			{
				m_Store_ViewList.erase(iter);

				iter = m_Store_ViewList.begin();
				iter_End = m_Store_ViewList.end();
			}
			else if(iIndex > 3)
			{
				iter = m_Store_ViewList.begin();

				int iViewIndex = 0;
				for (iter; iter != m_Store_ViewList.end(); ++iter, ++iViewIndex)
				{
					(*iter)->SetPos(m_tInfo.fx + 10.f, m_tInfo.fy + 125.f + (42.5f * iViewIndex));
				}
			}
		}

		cout << iIndex << endl;
		*/
	}
	else
	{
		
	}
}
