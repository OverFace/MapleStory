#include "stdafx.h"
#include "Obj.h"

POINT CObj::m_ptScroll;

CObj::CObj(void)
{
	m_bDead = false;
	m_fAngle = 0.f;
	m_fSpeed = 0.f;
	m_ptScroll.x = 0;
	m_ptScroll.y = 0;
	m_eRenderType = RENDER_END;

	memset(&m_tInfo, 0, sizeof(INFO));
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
