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
	pArmor->SetItemDescription(L"기본 갑옷");
	m_Store_ItemList.push_back(pArmor);

	pArmor = new CArmor(L"Armor1");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1);
	pArmor->SetItemDescription(L"고급 갑옷");
	m_Store_ItemList.push_back(pArmor);
	//----------------------------------------------------------------------------------
	//Weapon (Weapon, Weapon1)
	CItem* pWeapon = new CWeapon(L"Weapon");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 2);
	pWeapon->SetItemDescription(L"기본 무기");
	m_Store_ItemList.push_back(pWeapon);

	pWeapon = new CWeapon(L"Weapon1");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 3);
	pWeapon->SetItemDescription(L"고급 무기");
	m_Store_ItemList.push_back(pWeapon);
	//----------------------------------------------------------------------------------
	//Glove (Glove, Glove1)
	CItem* pGlove = new CGlove(L"Glove");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 4);
	pGlove->SetItemDescription(L"기본 장갑");
	m_Store_ItemList.push_back(pGlove);

	pGlove = new CGlove(L"Glove1");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 5);
	pGlove->SetItemDescription(L"고급 장갑");
	m_Store_ItemList.push_back(pGlove);
	//----------------------------------------------------------------------------------
	//Helmet
	CItem* pHelmet = new CHelmet(L"Helmet");
	((CHelmet*)pHelmet)->Initialize();
	((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 6);
	pHelmet->SetItemDescription(L"투구");
	m_Store_ItemList.push_back(pHelmet);
	//----------------------------------------------------------------------------------
	//Accessory
	CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 7);
	pAcs->SetItemDescription(L"메이플 반지");
	m_Store_ItemList.push_back(pAcs);

	pAcs = new CAccessory(L"Accessory1", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 8);
	pAcs->SetItemDescription(L"고급 반지");
	m_Store_ItemList.push_back(pAcs);
	//----------------------------------------------------------------------------------
	//Shoes
	CItem* pShoes = new CShoes(L"Shoes");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 9);
	pShoes->SetItemDescription(L"기본 신발");
	m_Store_ItemList.push_back(pShoes);

	pShoes = new CShoes(L"Shoes1");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 10);
	pShoes->SetItemDescription(L"고급 신발");
	m_Store_ItemList.push_back(pShoes);
	//----------------------------------------------------------------------------------
	//Potion
	CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 11);
	pPotion->SetItemDescription(L"생명력 포션");
	m_Store_ItemList.push_back(pPotion);

	pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 12);
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
	/*
	아이템 리스트에서 스크롤이 될 경우에 리스트의 맨 앞에 있는 것이 빠지고
	그 밑에 있는 것들이 위로 올라오는 식으로 보여 주어야 한다.
	지금 상태는 미리 13개 아이템을 다 넣어논 상태이고 지금 13개 다 보여주고 있다.

	기준은 스크롤 바의 좌표 값을 기준으로 잡아보자.
	*/

	static bool bMoveUp = false;
	if (m_tScroll_Info.fy < m_tInfo.fy + 134.f)
	{
		bMoveUp = false;
		return;
	}
	else if (m_tScroll_Info.fy > m_tInfo.fy + 134.f && m_tScroll_Info.fy < 559.f)
	{
		ITEMITER iter = m_Store_ItemList.begin();
		ITEMITER iter_End = m_Store_ItemList.end();

		float fx = 10.f;
		float fy = 125.f;		
		int	iIndex = 0;		

		//스크롤바를 밑으로 내릴시에
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
			}
		}		

		//스크롤 바를 위로 올릴시에 
		if (bMoveUp == true)
		{
			if (m_tScroll_Info.fy <= 315 && m_tScroll_Info.fy > 234)
			{
				CItem* pArmor = new CArmor(L"Armor");
				((CArmor*)pArmor)->Initialize();
				((CArmor*)pArmor)->SetArmor_Data(5, 5, 5, 5, 10, 5, 1000, 0);
				pArmor->SetItemDescription(L"기본 갑옷");
				m_Store_ItemList.push_front(pArmor);				
			}
			else if (m_tScroll_Info.fy <= 396 && m_tScroll_Info.fy > 315)
			{
				CItem* pArmor = new CArmor(L"Armor1");
				((CArmor*)pArmor)->Initialize();
				((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1);
				pArmor->SetItemDescription(L"고급 갑옷");
				m_Store_ItemList.push_front(pArmor);
			}
			else if (m_tScroll_Info.fy <= 477 && m_tScroll_Info.fy > 396)
			{
				CItem* pWeapon = new CWeapon(L"Weapon");
				((CWeapon*)pWeapon)->Initialize();
				((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 2);
				pWeapon->SetItemDescription(L"기본 무기");
				m_Store_ItemList.push_front(pWeapon);
			}
			else if (m_tScroll_Info.fy <= 558 && m_tScroll_Info.fy > 477)
			{
				CItem* pWeapon = new CWeapon(L"Weapon1");
				((CWeapon*)pWeapon)->Initialize();
				((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 3);
				pWeapon->SetItemDescription(L"고급 무기");
				m_Store_ItemList.push_front(pWeapon);
			}
		}

		/*
		system("cls");
		cout << m_tScroll_Info.fy << endl;
		cout << m_tScroll_Rect.top << endl;
		cout << m_tScroll_Rect.bottom << endl;
		*/	
	}		
}
