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

	m_ptOffset.y = 200;
	m_ptOffset.x = 200;
	
	m_bJump = false;
	m_bJumpAcc = 0.f;
	m_bOldY = 0.f;
	m_fDownSpeed = 5.f;
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
	m_fSpeed = 2.f;

	m_eRenderType = RENDER_WORLDOBJ;
}

int CPlayer::Update(void) {

	KeyCheck();
	CObj::Update();
	FrameMove();

	Scroll();
	//DynamicScroll();
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
		case STATE_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iYIndex = 0;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iYIndex = 6;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iYIndex = 5;
			m_tFrame.dwFrameTime = 150;
			break;
		case STATE_SKILL:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iYIndex = 3;
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
			m_dwState = STATE_UP;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			if (m_pName == L"Player_Up") {
				m_tInfo.fy += m_fSpeed;
				g_fScrollY -= m_fSpeed;
			}
			m_dwState = STATE_DOWN;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_tInfo.fx -= m_fSpeed;
			g_fScrollX += m_fSpeed * 2;

			m_pName = L"Player_Left";
			m_dwState = STATE_WALK;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_tInfo.fx += m_fSpeed;
			g_fScrollX -= m_fSpeed * 2;

			m_pName = L"Player_Right";
			m_dwState = STATE_WALK;
		}
		if (GetAsyncKeyState(VK_CONTROL))
		{
			m_dwState = STATE_HIT;
		}

		if (GetAsyncKeyState(VK_SHIFT))
		{
			m_dwState = STATE_SKILL;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
//			m_bJump = true;
//			Jump();
			m_dwState = STATE_JUMP;
		}
	}
}
void CPlayer::Scroll(void)
{
	if (m_tInfo.fx >= 806.f)
	{
		m_fSpeed = 4.f;
		g_fScrollX = -588.f;
	}
	else
		m_fSpeed = 2.f;
	
	if (m_tInfo.fx <= 338.f)
	{
		m_fSpeed = 4.f;
		g_fScrollX = 160.f;
	}
	else
		m_fSpeed = 2.f;


	//400

	/*
	if (m_tInfo.fx > WINCX / 2.f + 300)
	{
		g_fScrollX -= m_fSpeed;
	}
	if (m_tInfo.fx < WINCX / 2.f - 300)
	{
		g_fScrollX += m_fSpeed;
	}

	
	if (m_tInfo.fx + g_fScrollX > WINCX / 2 + m_ptOffset.x)
	{
		g_fScrollX -= int(m_fSpeed);

		if (g_fScrollX < WINCX - 2048)
			g_fScrollX = WINCX - 2048;
	}

	if (m_tInfo.fx + g_fScrollX < WINCX / 2 - m_ptOffset.x)
	{
		g_fScrollX += int(m_fSpeed);

		if (g_fScrollX > 0)
			g_fScrollX = 0;
	}

	if (m_tInfo.fy + g_fScrollY > WINCY / 2 + m_ptOffset.y)
	{
		g_fScrollY -= int(m_fSpeed);

		if (g_fScrollY < WINCY - 1440)
			g_fScrollY = WINCY - 1440;
	}

	if (m_tInfo.fy + g_fScrollY < WINCY / 2 - m_ptOffset.y)
	{
		g_fScrollY += int(m_fSpeed);

		if (g_fScrollY > 0)
			g_fScrollY = 0;
	}
	*/
}

void CPlayer::DynamicScroll(void)
{
	//system("cls");
	//cout << m_tInfo.fx + g_fScrollX << endl;
	//cout << WINCX / 2 + m_ptOffset.x << endl;
	//cout << g_fScrollX << endl;

	if (m_tInfo.fx + g_fScrollX > WINCX / 2 + m_ptOffset.x)
	{
		g_fScrollX -= int(m_fSpeed);

		if (g_fScrollX < WINCX - 2048)
			g_fScrollX = WINCX - 2048;	
	}

	if (m_tInfo.fx + g_fScrollX < WINCX / 2 - m_ptOffset.x)
	{
		g_fScrollX += int(m_fSpeed);

		if (g_fScrollX > 0)
			g_fScrollX = 0;
	}

	if (m_tInfo.fy + g_fScrollY > WINCY / 2 + m_ptOffset.y)
	{
		g_fScrollY -= int(m_fSpeed);

		if (g_fScrollY < WINCY - 1440)
			g_fScrollY = WINCY - 1440;
	}

	if (m_tInfo.fy + g_fScrollY < WINCY / 2 - m_ptOffset.y)
	{
		g_fScrollY += int(m_fSpeed);

		if (g_fScrollY > 0)
			g_fScrollY = 0;
	}

	if (m_tInfo.fx + g_fScrollX > WINCX / 2)
	{
		float fSpeed = (m_tInfo.fx + g_fScrollX) - WINCX / 2;

		fSpeed /= 32.f;		

		g_fScrollX -= (int)fSpeed;

		if (g_fScrollX < WINCX - (WINCX * 2))
			g_fScrollX = WINCX - (WINCX * 2);
	}

	
	if (m_tInfo.fx + g_fScrollX < WINCX / 2)
	{
		float fSpeed = WINCX / 2 - (m_tInfo.fx + g_fScrollX);
		fSpeed /= 32.f;

		g_fScrollX += (int)fSpeed;

		if (g_fScrollX > 0)
			g_fScrollX = 0;
	}
	

	if (m_tInfo.fy + g_fScrollY > WINCY / 2)
	{
		float fSpeed = (m_tInfo.fy + g_fScrollY) - WINCY / 2;
		fSpeed /= 32.f;

		g_fScrollY -= (int)fSpeed;

		if (g_fScrollY < WINCY - (WINCY * 2))
			g_fScrollY = WINCY - (WINCY * 2);
	}

	if (m_tInfo.fy + g_fScrollY < WINCY / 2)
	{
		float fSpeed = WINCY / 2 - (m_tInfo.fy + g_fScrollY);
		fSpeed /= 32.f;

		g_fScrollY += (int)fSpeed;

		if (g_fScrollY > 0)
			g_fScrollY = 0;


	}
}

void CPlayer::Jump(void)
{

	if (m_bJump)
	{
		m_bOldY = m_tInfo.fy;
		m_bJumpAcc += 0.1f;
		m_tInfo.fy += 0.98f * m_bJumpAcc * m_bJumpAcc * 0.5f - 10.f;

	}

	if (m_tInfo.fy > m_bOldY && m_bJump == true)
	{
		m_tInfo.fy = m_bOldY;
		m_bJump = false;
		m_bJumpAcc = 0.f;
	}
}

