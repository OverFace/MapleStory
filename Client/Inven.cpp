#include "stdafx.h"
#include "Inven.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "Item.h"

CInven::CInven(void)
{
	m_eUiType = UI_INVEN;
	m_dwTime = 0;
	ZeroMemory(&m_tInvenMove_Rect, sizeof(RECT));

	m_bStoreInven_Check = false;
	for (int i = 0; i < INVEN_END; ++i)
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

	//Inven Move Rect
	m_tInvenMove_Rect.left = long(m_tInfo.fx + (172.f / 2.f) - 172.f / 2.f);
	m_tInvenMove_Rect.right = long(m_tInfo.fx + (172.f / 2.f) + 172.f / 2.f);
	m_tInvenMove_Rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
	m_tInvenMove_Rect.bottom = long(m_tInfo.fy+ (20.f / 2.f) - 20.f / 2.f);

	m_dwTime = GetTickCount();
}

int CInven::Update(void)
{
	//Inven Move Rect
	m_tInvenMove_Rect.left = long(m_tInfo.fx + (172.f / 2.f) - 172.f / 2.f);
	m_tInvenMove_Rect.right = long(m_tInfo.fx + (172.f / 2.f) + 172.f / 2.f);
	m_tInvenMove_Rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2.f);
	m_tInvenMove_Rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2.f);

	//Key Setting
	Inven_Key();

	//Inven Move
	Inven_Move();

	return 0;
}

void CInven::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx), int(m_tInfo.fy),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Inventory_Equip")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));

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

void CInven::Inven_ViewItem(void)
{
	if (m_bStoreInven_Check == true)
	{
		//상점 모드일때의 인벤 아이템 배치.
	}
	else
	{
		//인벤 모드에서의 인벤 아이템 배치
		if (m_bInvenMode[INVEN_EQUIP])
		{
			//장비 목록
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
}

void CInven::Save_InvenData(void)
{
}

void CInven::Load_InvenData(void)
{
}
