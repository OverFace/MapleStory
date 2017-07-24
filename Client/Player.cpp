#include "StdAfx.h"
#include "Player.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
CPlayer::CPlayer(void) {

	m_pName = NULL;
	memset(&m_tFrame, 0, sizeof(FRAME));
	m_dwFrameTime = 0;

//	m_ptOffset.y = 200;
//	m_ptOffset.x = 100;
}

CPlayer::~CPlayer(void) {
	Release();
}

void CPlayer::Initialize(void) {
	m_pName = L"Player_Right";

	m_tInfo.fx = float(WINCX / 2);
	m_tInfo.fy = float(WINCY / 2);
	m_tInfo.fcx = 100.f;
	m_tInfo.fcy = 100.f;

	m_tFrame = FRAME(0, 3, 0, 150);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();
	m_fSpeed = 15.f;

	m_eRenderType = RENDER_WORLDOBJ;
}

int CPlayer::Update(void) {

	KeyCheck();
	CObj::Update();
	FrameMove();

	return 0;
}

void CPlayer::Render(HDC _dc) {
	//Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	TransparentBlt(_dc,
		int(m_tInfo.fx - m_tInfo.fcx / 2.f),
		int(m_tInfo.fy - m_tInfo.fcy / 2.f),
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),
		CBitMapMgr::GetInstance()->FindImage(m_pName)->GetMemDC(),				
		int(m_tInfo.fcx * m_tFrame.iFrameStart),
		int(m_tInfo.fcy * m_tFrame.iYIndex),
		int(m_tInfo.fcx),
		int(m_tInfo.fcy),														
		RGB(71, 0, 60));

}

void CPlayer::Release(void) {

}

void CPlayer::FrameMove(void)
{
	if (m_dwState != m_dwPrevState)
	{
		switch (m_dwState)
		{
		case STATE_STAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iYIndex = 0;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iYIndex = 1;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iYIndex = 2;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iYIndex = 2;
			m_tFrame.dwFrameTime = 150;
			break;
		}
		m_dwPrevState = m_dwState;
	}

	if (m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		if (m_dwState != STATE_STAND)
		{
			m_dwState = STATE_STAND;
		}
		m_tFrame.iFrameStart = 0;
	}
}

void CPlayer::KeyCheck(void)
{
	if (m_dwState != STATE_ATT)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_tInfo.fy -= m_fSpeed;
			g_fScrollY += m_fSpeed;

			m_pName = L"Player_Up";
			m_dwState = STATE_WALK;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			m_tInfo.fy += m_fSpeed;
			g_fScrollY -= m_fSpeed;

			m_pName = L"Player_Up";
			m_dwState = STATE_WALK;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fx -= m_fSpeed;
			g_fScrollX += m_fSpeed;

			m_pName = L"Player_Left";
			m_dwState = STATE_WALK;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fx += m_fSpeed;
			g_fScrollX -= m_fSpeed;

			m_pName = L"Player_Right";
			m_dwState = STATE_WALK;
		}
		}

	}
