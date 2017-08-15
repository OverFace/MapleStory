#include "StdAfx.h"
#include "Slim.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"

CSlim::CSlim(void)
{
	m_pName = NULL;
	memset(&m_tFrame, 0, sizeof(FRAME));
	m_dwFrameTime = 0;
}

CSlim::~CSlim(void)
{
	Release();
}

void CSlim::Initialize(void)
{
	m_pName = L"Slim_L";
	m_fRadius = (float)m_tInfo.fcx / 2;
	m_bRight = true;

	m_tInfo.fx = float(WINCX / 2);
	m_tInfo.fy = float(WINCY / 2);

	m_tInfo.fcx = 100.f;
	m_tInfo.fcy = 100.f;
	m_fSpeed = 4.f;

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 5;
	m_tFrame.iYIndex = 3;
	m_tFrame.dwFrameTime = 150;
	m_dwFrameTime = GetTickCount();

	m_eState = MSTATE_WALK;
	m_eRenderType = RENDER_WORLDOBJ;
}

int CSlim::Update(void)
{
	FrameMove();

	Move();
		

	CObj::Update();

	return 0;
}

void CSlim::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx + g_fScrollX),
		int(m_tInfo.fy + g_fScrollY),
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),
		CBitMapMgr::GetInstance()->FindImage(m_pName)->GetMemDC(),
		int(m_tInfo.fcx * m_tFrame.iFrameStart),
		int(m_tInfo.fcy * m_tFrame.iYIndex),
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),
		RGB(255, 0, 255));
}

void CSlim::Release(void)
{

}

void CSlim::FrameMove(void)
{
	if (m_eState != m_ePreState)
	{
		switch (m_eState)
		{
		case MSTATE_STAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iYIndex = 0;
			m_tFrame.dwFrameTime = 150;
			break;
		case MSTATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iYIndex = 3;
			m_tFrame.dwFrameTime = 150;
			break;
		case MSTATE_HIT:	//맞았을 때
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iYIndex = 1;
			m_tFrame.dwFrameTime = 150;
			break;
		case MSTATE_ATTACK:	// 때릴 때
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iYIndex = 2;
			m_tFrame.dwFrameTime = 150;
			break;
		case MSTATE_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iYIndex = 4;
			m_tFrame.dwFrameTime = 150;
			break;
		}
		m_ePreState = m_eState;
	}

	if (m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		if (m_eState != MSTATE_WALK)
		{
			m_eState = MSTATE_WALK;
		}
		m_tFrame.iFrameStart = 0;
	}
}

void CSlim::Move(void)
{
	if (m_bRight == true)
	{
		m_tInfo.fx += m_fSpeed;
	}
	else
		m_tInfo.fx -= m_fSpeed;

	if (m_tInfo.fx > WINCX / 2)
	{
		m_bRight = false;

		m_pName = L"Slim_L";
		m_eState = MSTATE_WALK;
	}		

	if (m_tInfo.fx < 50)
	{
		m_bRight = true;

		m_pName = L"Slim_R";
		m_eState = MSTATE_WALK;
	}
}

void CSlim::Attack(void)
{
}

void CSlim::Hit(void)
{
}

void CSlim::Dead(void)
{
}
