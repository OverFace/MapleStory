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

	//Esc Button / X 버튼
	m_tEscButton_Info[0].fx = m_tInfo.fx + m_tInfo.fcx / 2.f;
	m_tEscButton_Info[0].fy = m_tInfo.fy + 10.f;
	m_tEscButton_Info[0].fcx = 9.f;
	m_tEscButton_Info[0].fcy = 9.f;

	//Esc Button / 상점 나가기 버튼
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
	pArmor->SetItemDescription(L"기본 갑옷");
	m_Store_ItemList.push_back(pArmor);

	pArmor = new CArmor(L"Armor1");
	((CArmor*)pArmor)->Initialize();
	((CArmor*)pArmor)->SetArmor_Data(10, 10, 10, 10, 15, 10, 2000, 1000, 1);
	pArmor->SetItemDescription(L"고급 갑옷");
	m_Store_ItemList.push_back(pArmor);
	//----------------------------------------------------------------------------------
	//Weapon (Weapon, Weapon1)
	CItem* pWeapon = new CWeapon(L"Weapon");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(10, 2, 2, 2, 0, 0, 1000, 500, 2);
	pWeapon->SetItemDescription(L"기본 무기");
	m_Store_ItemList.push_back(pWeapon);

	pWeapon = new CWeapon(L"Weapon1");
	((CWeapon*)pWeapon)->Initialize();
	((CWeapon*)pWeapon)->SetWeapon_Data(20, 4, 4, 4, 0, 0, 2000, 1000, 3);
	pWeapon->SetItemDescription(L"고급 무기");
	m_Store_ItemList.push_back(pWeapon);
	//----------------------------------------------------------------------------------
	//Glove (Glove, Glove1)
	CItem* pGlove = new CGlove(L"Glove");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(2, 2, 2, 2, 5, 0, 500, 250, 4);
	pGlove->SetItemDescription(L"기본 장갑");
	m_Store_ItemList.push_back(pGlove);

	pGlove = new CGlove(L"Glove1");
	((CGlove*)pGlove)->Initialize();
	((CGlove*)pGlove)->SetGlove_Data(4, 4, 4, 4, 10, 0, 1000, 500, 5);
	pGlove->SetItemDescription(L"고급 장갑");
	m_Store_ItemList.push_back(pGlove);
	//----------------------------------------------------------------------------------
	//Helmet
	CItem* pHelmet = new CHelmet(L"Helmet");
	((CHelmet*)pHelmet)->Initialize();
	((CHelmet*)pHelmet)->SetHelmet_Data(4, 4, 4, 4, 5, 5, 500, 250, 6);
	pHelmet->SetItemDescription(L"투구");
	m_Store_ItemList.push_back(pHelmet);
	//----------------------------------------------------------------------------------
	//Accessory
	CItem* pAcs = new CAccessory(L"Accessory", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(2, 2, 2, 2, 3, 3, 500, 250, 7);
	pAcs->SetItemDescription(L"메이플 반지");
	m_Store_ItemList.push_back(pAcs);

	pAcs = new CAccessory(L"Accessory1", ITEM_RING);
	((CAccessory*)pAcs)->Initialize();
	((CAccessory*)pAcs)->SetAccessory_Data(4, 4, 4, 4, 6, 6, 1000, 500, 8);
	pAcs->SetItemDescription(L"고급 반지");
	m_Store_ItemList.push_back(pAcs);
	//----------------------------------------------------------------------------------
	//Shoes
	CItem* pShoes = new CShoes(L"Shoes");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(2, 2, 2, 2, 0, 0, 500, 250, 9);
	pShoes->SetItemDescription(L"기본 신발");
	m_Store_ItemList.push_back(pShoes);

	pShoes = new CShoes(L"Shoes1");
	((CShoes*)pShoes)->Initialize();
	((CShoes*)pShoes)->SetShoes_Data(4, 4, 4, 4, 2, 2, 1000, 500, 10);
	pShoes->SetItemDescription(L"고급 신발");
	m_Store_ItemList.push_back(pShoes);
	//----------------------------------------------------------------------------------
	//Potion
	CItem* pPotion = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 1000, 0, 100, 50, 11);
	pPotion->SetItemDescription(L"생명력 포션");
	m_Store_ItemList.push_back(pPotion);

	pPotion = new CPotion(L"Mp_Potion", ITEM_MP_POTION);
	((CPotion*)pPotion)->Initialize();
	((CPotion*)pPotion)->SetPotion_Data(0, 0, 0, 0, 0, 1000, 100, 50, 12);
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
	{
		(*iter_Item)->Update();
	}

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

		/*
		Rectangle(_dc,
			m_tScroll_Rect.left,
			m_tScroll_Rect.top,
			m_tScroll_Rect.right,
			m_tScroll_Rect.bottom);		

		Rectangle(_dc,
			m_tEscButton_Rect[1].left,
			m_tEscButton_Rect[1].top,
			m_tEscButton_Rect[1].right,
			m_tEscButton_Rect[1].bottom);		

		Rectangle(_dc,
			m_tSaleButton_Rect.left,
			m_tSaleButton_Rect.top,
			m_tSaleButton_Rect.right,
			m_tSaleButton_Rect.bottom);
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
}

#pragma region Store Scroll
void CStore::Scroll_Move(void)
{
	//마우스로 클릭하고 밑으로 내릴때 스크롤 바가 움직이게 한다.
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
	Scroll 움직임에 따른 아이템 위치 변환
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
		//스크롤바 상태 Change
		if (m_bScrollMove == true && m_tScroll_Info.fy > fCurScrollPosY)
			bMoveUp = false;
		else if (m_bScrollMove == true && m_tScroll_Info.fy < fCurScrollPosY)
			bMoveUp = true;

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

				//밑으로 드래그 할 시에 스크롤 기준값 담기.
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

				//밑으로 드래그 할 시에 스크롤 기준값 담기.
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

				//밑으로 드래그 할 시에 스크롤 기준값 담기.
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

				//밑으로 드래그 할 시에 스크롤 기준값 담기.
				fCurScrollPosY = m_tScroll_Info.fy;
				m_bScroll_Item_Check[3] = false;
			}
		}		

		//스크롤 바를 위로 올릴시에 
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
							pArmor->SetItemDescription(L"기본 갑옷");
							m_Store_ItemList.push_front(pArmor);

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
							pArmor->SetItemDescription(L"고급 갑옷");
							m_Store_ItemList.push_front(pArmor);

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
							pWeapon->SetItemDescription(L"기본 무기");
							m_Store_ItemList.push_front(pWeapon);

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
							pWeapon->SetItemDescription(L"고급 무기");
							m_Store_ItemList.push_front(pWeapon);

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
	//마우스로 클릭하고 밑으로 내릴때 스크롤 바가 움직이게 한다.
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
	/*	Scroll 움직임에 따른 아이템 위치 변환	*/

	static float fCurScrollPosY = 0.f;
	static bool bMoveUp = false;

	//Inven 에 있는 list 가져오기
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
	Store Inven Slot 크기가 하나당 42.5f 이다.
	그럼 Store Inven의 List 최대 개수에서 42.5f로 나누어 스크롤 조절하자.
	Store Inven의 아이템 표현 갯수는 9개이다.
	*/

	//Scroll 동작.
	if (m_tStoreInven_Scroll_Info.fy < m_tInfo.fy + 134.f)
	{
		bMoveUp = false;
		return;
	}
	else if (m_tStoreInven_Scroll_Info.fy > m_tInfo.fy + 134.f && m_tStoreInven_Scroll_Info.fy < 559.f)
	{
		//스크롤바 상태 Change(지금 fCurScrollPosY 값이 갱신되고 있지 않아서 지금 조건 통하지 않음)
		if (m_bStoreInven_ScrollMove == true && m_tStoreInven_Scroll_Info.fy > fCurScrollPosY)
			bMoveUp = false;
		else if (m_bStoreInven_ScrollMove == true && m_tStoreInven_Scroll_Info.fy < fCurScrollPosY)
			bMoveUp = true;		

		//시작 위치 315.f & 시작 위치로부터 마지막 아이템 갯수 까지의 y 값.
		float fStoreInven_LimitPosY = 315.f + (42.5f * m_iStoreInven_ItemCount);
		
		//Limit Pos Y 랑 스크롤 바의 Y 값이랑 비율 적으로 몇개로 나누어 지는가
		//LimitPosY : 558 - 315 = 42.5f : x;
		//LimitPosY * x = 558 - 315 * 42.5f;
		//x = 558 - 315 * 42.5f / LimitPosY;
		int iStoreInven_ScrollDivision = int(((558 - 315) * 42.5f) / fStoreInven_LimitPosY);

		//나누어진 갯수로 Scroll 길이를 나눈다 -> 나누어질 스크롤 크기가 나옴
		int iRange_StroeInven_ScrollDivision = (558 - 315) / iStoreInven_ScrollDivision;
		
		//나누기 0일 경우 Min & Max 범위를 구한다.
		float fStoreInven_ScrollRange_Max = 0.f;
		float fStoreInven_ScrollRange_Min = 0.f;

		if (int(m_tStoreInven_Scroll_Info.fy) % iRange_StroeInven_ScrollDivision == 0)
		{
			fStoreInven_ScrollRange_Min = m_tStoreInven_Scroll_Info.fy - 21.25f;
			fStoreInven_ScrollRange_Max = m_tStoreInven_Scroll_Info.fy + 21.25f;
		}

		//스크롤바를 밑으로 내릴시에
		if (bMoveUp == false)
		{
			if (fStoreInven_ScrollRange_Min < m_tStoreInven_Scroll_Info.fy
				&& fStoreInven_ScrollRange_Max > m_tStoreInven_Scroll_Info.fy
				&& m_iStoreInven_ItemCount >= 9)
			{
				//아이템 하나씩 사라지게 한다.  list에서 pop 한 아이템은 Templist에 넣어둔다.
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

		//스크롤 바를 위로 올릴시에
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

				//Item 종류 분류
				if (!lstrcmp(tItem.m_szDescription, L"기본 갑옷"))
				{
					pItem = new CArmor(L"Armor");
					((CArmor*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"고급 갑옷"))
				{
					pItem = new CArmor(L"Armor1");
					((CArmor*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"기본 무기"))
				{
					pItem = new CWeapon(L"Weapon");
					((CWeapon*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"고급 무기"))
				{
					pItem = new CWeapon(L"Weapon1");
					((CWeapon*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"기본 장갑"))
				{
					pItem = new CGlove(L"Glove");
					((CGlove*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"고급 장갑"))
				{
					pItem = new CGlove(L"Glove1");
					((CGlove*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"투구"))
				{
					pItem = new CHelmet(L"Helmet");
					((CHelmet*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"메이플 반지"))
				{
					pItem = new CAccessory(L"Accessory", ITEM_RING);
					((CAccessory*)pItem)->Initialize();
					pItem->SetItemData(tItem);

				}
				else if (!lstrcmp(tItem.m_szDescription, L"고급 반지"))
				{
					pItem = new CAccessory(L"Accessory1", ITEM_RING);
					((CAccessory*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"기본 신발"))
				{
					pItem = new CShoes(L"Shoes");
					((CShoes*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"고급 신발"))
				{
					pItem = new CShoes(L"Shoes1");
					((CShoes*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"생명력 포션"))
				{
					pItem = new CPotion(L"Hp_Potion", ITEM_HP_POTION);
					((CPotion*)pItem)->Initialize();
					pItem->SetItemData(tItem);
				}
				else if (!lstrcmp(tItem.m_szDescription, L"마나 포션"))
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
	ITEMITER iter_Item = m_Store_ItemList.begin();
	ITEMITER iter_Item_End = m_Store_ItemList.end();

	POINT pt;
	pt = CMouse::GetPos();
	
	for (iter_Item; iter_Item != iter_Item_End; ++iter_Item)
	{
		if (PtInRect((*iter_Item)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
		{
			//아이템 렉트 클릭시 동작
			m_pSelect_Item = (*iter_Item);			
		}
	}
}

void CStore::Buy_Button_Click(void)
{
	//버튼 클릭시 Buy 기능 수행.
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
	//Inven 가져오기.
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

	//Inven에 아이템 push
	((CInven*)pInven)->Set_StoreCheck(true);
	((CInven*)pInven)->Set_InvenItem(pItem);
	((CInven*)pInven)->Inven_ItemClassification(pItem);
	
	if (((CInven*)pInven)->Get_InvenItem_CreateCheck() == true)
		((CInven*)pInven)->Set_InvenItem_CreateCheck(false);

	//Store Inven Item 갯수 증가.
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

	//Inven Item List 가져오기
	if (((CInven*)pInven)->Get_StoreCheck() == true)
	{
		list<CItem*>* InvenList = ((CInven*)pInven)->GetInven_ItemList();

		ITEMITER iter_Inven = InvenList->begin();
		ITEMITER iter_Inven_End = InvenList->end();
		float fx = 285.f;
		float fy = 125.f;
		int   iIndex = 0;

		for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven, ++iIndex)
		{
			if (iIndex < 9)
			{
				(*iter_Inven)->Render(_dc);
				(*iter_Inven)->SetPos(m_tInfo.fx + fx, m_tInfo.fy + fy + (42.5f * iIndex));
				(*iter_Inven)->SetSaleItemDescription_Render(_dc, m_tInfo.fx + fx + 40.f, m_tInfo.fy + fy + (42.5f * iIndex));
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
		}
	}

	if (((CInven*)pInven)->Get_StoreCheck() == true)
	{
		list<CItem*>* InvenList = ((CInven*)pInven)->GetInven_ItemList();

		POINT pt;
		pt = CMouse::GetPos();

		ITEMITER iter_Inven = InvenList->begin();
		ITEMITER iter_Inven_End = InvenList->end();

		for (iter_Inven; iter_Inven != iter_Inven_End; ++iter_Inven)
		{
			if (PtInRect((*iter_Inven)->GetRect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				//아이템 렉트 클릭시 동작
				m_pSelect_Item = (*iter_Inven);				
			}			
		}				
	}
}

void CStore::Sale_Button_Click(void)
{
	//버튼 클릭시 Sale 기능 수행.
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
	//Inven 가져오기.
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

	list<CItem*>* InvenItemList = ((CInven*)pInven)->GetInven_ItemList();
	ITEMITER iter_Inven = InvenItemList->begin();
	ITEMITER iter_Inven_End = InvenItemList->end();

	//Inven에 아이템 delete
	for (iter_Inven; iter_Inven != iter_Inven_End;)
	{
		if ((*iter_Inven)->GetItemData()->m_dwOption == m_pSelect_Item->GetItemData()->m_dwOption && m_bSale_Check == false)
		{
			//Sale Price를 Player Money에 축적 시킨다.
			pPlayer->SetMoney((*iter_Inven)->GetItemData()->m_iSalePrice);

			//그다음 원래 있던 아이템 삭제
			InvenItemList->erase(iter_Inven);

			iter_Inven = InvenItemList->begin();
			iter_Inven_End = InvenItemList->end();

			m_bSale_Check = true;
		}
		else
			++iter_Inven;
	}	

	//Store Inven Item 갯수 증가.
	--m_iStoreInven_ItemCount;
}
#pragma endregion

void CStore::Messo_Present(HDC _dc)
{
	CPlayer* pPlayer = NULL;
	pPlayer = ((CPlayer*)(GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->back()));

	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

	//Money
	TCHAR szMesso[128] = { 0 };
	_stprintf_s(szMesso, _countof(szMesso), L"%d", pPlayer->GetMoney());

	SetBkMode(_dc, TRANSPARENT);
	TextOut(_dc, int(m_tInfo.fx + 420.f), int(m_tInfo.fy + 57.f), szMesso, lstrlen(szMesso));
	SelectObject(_dc, oldFont);
}
