#include "stdafx.h"
#include "Obj.h"

POINT CObj::m_ptScroll;

CObj::CObj(void)
{
}

CObj::~CObj(void)
{
}

int CObj::Update(void)
{
	m_Rect.left   = long(m_tInfo.fx - m_tInfo.fcx / 2);
	m_Rect.right  = long(m_tInfo.fx + m_tInfo.fcx / 2);
	m_Rect.top    = long(m_tInfo.fy - m_tInfo.fcy / 2);
	m_Rect.bottom = long(m_tInfo.fy + m_tInfo.fcy / 2);

	if (m_bDead == true)
		return 1;

	return 0;
}
