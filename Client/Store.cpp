#include "stdafx.h"
#include "Store.h"
#include "BitMapMgr.h"
#include "BitMap.h"

//Item----------------------------
#include "Item.h"
#include "Armor.h"
#include "Glove.h"
#include "Accessory.h"
#include "Helmet.h"
#include "Shoes.h"
#include "Potion.h"
#include "Weapon.h"
//--------------------------------

CStore::CStore(void)
{
	m_eUiType = UI_STORE;
	ZeroMemory(&m_tEscButton_Rect, sizeof(RECT));
	ZeroMemory(&m_tEscButton_Info, sizeof(INFO));
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

	m_tEscButton_Info.fx = m_tInfo.fx + m_tInfo.fcx / 2.f;
	m_tEscButton_Info.fy = m_tInfo.fy + 10.f;
	m_tEscButton_Info.fcx = 9.f;
	m_tEscButton_Info.fcy = 9.f;

	m_eRenderType = RENDER_UI;
}

int CStore::Update(void)
{
	//Button Rect
	m_tEscButton_Rect.left = long(m_tEscButton_Info.fx + (m_tEscButton_Info.fcx / 2.f) - m_tEscButton_Info.fcx / 2);
	m_tEscButton_Rect.right = long(m_tEscButton_Info.fx + (m_tEscButton_Info.fcx / 2.f) + m_tEscButton_Info.fcx / 2);
	m_tEscButton_Rect.top = long(m_tEscButton_Info.fy + (m_tEscButton_Info.fcy / 2.f) - m_tEscButton_Info.fcy / 2);
	m_tEscButton_Rect.bottom = long(m_tEscButton_Info.fy + (m_tEscButton_Info.fcy / 2.f) + m_tEscButton_Info.fcy / 2);

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

		/*
		Rectangle(_dc,
			m_tEscButton_Rect.left,
			m_tEscButton_Rect.top,
			m_tEscButton_Rect.right,
			m_tEscButton_Rect.bottom);
		*/
	}		
}

void CStore::Release(void)
{
}
