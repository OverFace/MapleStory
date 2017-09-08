#include "stdafx.h"
#include "Equip.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"

CEquip::CEquip(void)
{
	m_eUiType = UI_EQUIP;
	m_dwTime = 0;

	m_pSelect_Item = NULL;
	m_pSelect_Slot = NULL;

	m_bEquipMoveCheck = false;

	ZeroMemory(&m_tEquipMove_Rect, sizeof(RECT));
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

	m_dwTime = GetTickCount();
}

int CEquip::Update(void)
{
	//Position
	m_tInfo.fx = 173.f + g_fScrollX;
	m_tInfo.fy = 0.f + g_fScrollY;

	//Key Setting
	Equip_Key();

	return 0;
}

void CEquip::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Equipment")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));
	}
}

void CEquip::Release(void)
{
}

void CEquip::Equip_Key(void)
{
	static bool bIsPress_Equip = false;
	if (GETS(CKeyMgr)->GetKeyDown('E') && bIsPress_Equip == false)
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
}

void CEquip::Equip_EscButton_Click(void)
{
}

void CEquip::Equip_SlotCreate(void)
{
}

void CEquip::Equip_SlotUpdqte(void)
{
}

void CEquip::Equip_SlotRender(HDC _dc)
{
}
