#include "stdafx.h"
#include "Equip.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "Slot.h"

typedef list<CItem*>::iterator ITEMITER;
typedef list<CSlot*>::iterator SLOTITER;

CEquip::CEquip(void)
{
	m_eUiType = UI_EQUIP;
	m_dwTime = 0;

	m_pSelect_Item = NULL;
	m_pSelect_Slot = NULL;

	m_bEquipMoveCheck = false;

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

		Equip_SlotRender(_dc);

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
}

void CEquip::Equip_Move(void)
{
	//Equip 창을 마우스로 움직이게 만드는 함수.
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tEquipMove_Rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
		m_bEquipMoveCheck = true;

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && m_bEquipMoveCheck == true)
		m_bEquipMoveCheck = false;

	if (m_bEquipMoveCheck == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);    //10.f 는 Rect의 y의 / 2 한 값.

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
		}
		//Armor
		else if (i == 2)
		{
			pSlot->SetEquipType(i);
		}
		//Pants
		else if (i == 3)
		{
			pSlot->SetEquipType(i);
		}
		//Gloves
		else if (i == 4)
		{
			pSlot->SetEquipType(i);
		}
		//Shoes
		else if (i == 5)
		{
			pSlot->SetEquipType(i);
		}
		//Weapon
		else if (i == 6)
		{
			pSlot->SetEquipType(i);
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

		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_ARMOR)
		{

		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_PANTS)
		{

		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_GLOVES)
		{

		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_SHOES)
		{

		}
		else if ((*iter_Slot)->GetEquipType() == EQUIP_WEAPON)
		{

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
