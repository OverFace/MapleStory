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
	m_fJumpAcc = 0.f;
	m_fOldY = 0.f;
}

CPlayer::~CPlayer(void) {
	Release();
}

void CPlayer::Initialize(void) {

	m_pName = L"Player_Right";

	m_tInfo.fx = float(WINCX / 2);
	m_tInfo.fy = 504.f;
	m_tInfo.fcx = 100.f;
	m_tInfo.fcy = 100.f;
	m_fDownSpeed = 5.f;

	//OldY 
	m_fOldY = m_tInfo.fy;

	m_tFrame = FRAME(0, 3, 0, 150);

	m_dwState = STATE_STAND;

	m_dwFrameTime = GetTickCount();
	m_fSpeed = 2.f;

	m_eRenderType = RENDER_WORLDOBJ;
}
 
int CPlayer::Update(void) {

	KeyCheck();	
	Jump();
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
	/*
	Rectangle(_dc,
		m_Rect.left,
		m_Rect.top,
		m_Rect.right,
		m_Rect.bottom);
	*/
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
		if (GETS(CKeyMgr)->StayKeyDown(VK_UP))
		{
			m_tInfo.fy -= m_fSpeed;
			g_fScrollY += m_fSpeed;

			m_pName = L"Player_Up";
			m_dwState = STATE_UP;
		}
		else if (GETS(CKeyMgr)->StayKeyDown(VK_DOWN))
		{
			
			if (m_pName == L"Player_Up") {
				m_tInfo.fy += m_fSpeed;
				g_fScrollY -= m_fSpeed;
			}
			
			m_dwState = STATE_DOWN;
		}
		else if (GETS(CKeyMgr)->StayKeyDown(VK_LEFT))
		{
			m_tInfo.fx -= m_fSpeed;
			g_fScrollX += m_fSpeed * 2;

			m_pName = L"Player_Left";
			m_dwState = STATE_WALK;
		}
		else if (GETS(CKeyMgr)->StayKeyDown(VK_RIGHT))
		{
			m_tInfo.fx += m_fSpeed;
			g_fScrollX -= m_fSpeed * 2;

			m_pName = L"Player_Right";
			m_dwState = STATE_WALK;
		}
		else if (GETS(CKeyMgr)->OnceKeyUp(VK_UP)
				|| GETS(CKeyMgr)->OnceKeyUp(VK_DOWN)
				|| GETS(CKeyMgr)->OnceKeyUp(VK_LEFT)
				|| GETS(CKeyMgr)->OnceKeyUp(VK_RIGHT))
		{
			m_dwState = STATE_STAND;
		}
				
		if (GETS(CKeyMgr)->StayKeyDown(VK_CONTROL))
		{
			m_dwState = STATE_HIT;
		}

		if (GETS(CKeyMgr)->StayKeyDown(VK_SHIFT))
		{
			m_dwState = STATE_SKILL;
		}
		if (GETS(CKeyMgr)->StayKeyDown(VK_SPACE) && m_bJump == false)
		{
			//Jump
			m_bJump = true;
			m_fOldY = m_tInfo.fy;
			m_dwState = STATE_JUMP;			
		}
	}
}
void CPlayer::Scroll(void)
{
#pragma region ��������1
	if (m_tInfo.fx <= 516.f)
	{
		m_fSpeed = 4.f;
		g_fScrollX = -8.f;
	}
	else
		m_fSpeed = 2.f;

	if (m_tInfo.fx >= 808.f)
	{
		m_fSpeed = 4.f;
		g_fScrollX = -592.f;
	}
	else
		m_fSpeed = 2.f;

	if (m_tInfo.fy <= 116.f)
	{
		m_fSpeed = 4.f;
		g_fScrollY = -88.f;
	}
	else
		m_fSpeed = 2.f;

	if (m_tInfo.fy >= 268.f)
	{
		m_fSpeed = 4.f;
		g_fScrollY = -240.f;
	}
	else
		m_fSpeed = 2.f;
#pragma endregion

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
	//y = �߷°��ӵ� * �ð� * �ð� * 0.5f + �ð� * �����ӵ� + �����Ŀ�
	
	if(m_bJump)
	{
		//���� �������κ��� �帥 �ð�...
		m_fJumpAcc += 0.2f;
		m_tInfo.fy += 0.98f * m_fJumpAcc * m_fJumpAcc * 1.5f - 8.f;
	}

	if (m_tInfo.fy > m_fOldY && m_bJump == true)
	{
		m_tInfo.fy = m_fOldY;
		m_bJump = false;
		m_fJumpAcc = 0.f;
	}
}


