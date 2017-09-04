#include "stdafx.h"
#include "Slot.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"

//UI
#include "Inven.h"
#include "Equip.h"
#include "Skill.h"

CSlot::CSlot(void)
{
	ZeroMemory(&m_tSlot_ItemData, sizeof(ITEM));
	m_iSlotNumber = 0;
}

CSlot::~CSlot(void)
{
	Release();
}

void CSlot::Initialize(void)
{
}

int CSlot::Update(void)
{
	m_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) - m_tInfo.fcx / 2);
	m_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) + m_tInfo.fcx / 2);
	m_Rect.top = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) - m_tInfo.fcy / 2);
	m_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) + m_tInfo.fcy / 2);

	return 0;
}

void CSlot::Render(HDC _dc)
{
	Rectangle(_dc,
		m_Rect.left,
		m_Rect.top,
		m_Rect.right,
		m_Rect.bottom);
}

void CSlot::Release(void)
{
}
