#include "stdafx.h"
#include "Quick_Slot.h"

CQuick_Slot::CQuick_Slot(void)
{
	m_eCutDonwKey = CK_END;
	m_iSlotNumber = 0;
}

CQuick_Slot::~CQuick_Slot(void)
{
	Release();
}

void CQuick_Slot::Initialize(void)
{
}

int CQuick_Slot::Update(void)
{
	m_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) - m_tInfo.fcx / 2);
	m_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) + m_tInfo.fcx / 2);
	m_Rect.top = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) - m_tInfo.fcy / 2);
	m_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) + m_tInfo.fcy / 2);

	return 0;
}

void CQuick_Slot::Render(HDC _dc)
{
	Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CQuick_Slot::Release(void)
{
}
