#include "StdAfx.h"
#include "Player.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Stage1_Map.h"

CPlayer::CPlayer(void) {

	m_pName = NULL;
	memset(&m_tFrame, 0, sizeof(FRAME));
	m_dwFrameTime = 0;
	m_iMoney = 0;

	m_ptOffset.y = 200;
	m_ptOffset.x = 200;

	m_bJump = false;
	m_bAnimation_Stop = false;
	m_bRope_ColStop = false;
	m_fJumpAcc = 0.f;
	m_fOldY = 0.f;
}

CPlayer::~CPlayer(void) {
	Release();
}

void CPlayer::Initialize(void) {

	m_pName = L"Player_Right";
	m_tInfo.fx = float(WINCX / 2);
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE1) {
		m_tInfo.fy = 512.f;
	}
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE2) {
		g_fScrollY = -650.f;
		m_tInfo.fy = 560.f;
	}
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE3) {
		m_tInfo.fy = 454.f;
	}
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_BOSS) {
		m_tInfo.fy = 530.f;
	}

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

int CPlayer::Update() {

	KeyCheck();
	Jump();
	Player_InfoCheck();

	FrameMove();
	Scroll();

	CObj::Update();

	//Rope랑 충돌 안될시에 바로 스텐드 자세로 돌아가도록 만들어야 된다.
	m_Rect.left = long(m_tInfo.fx - (m_tInfo.fcx - 30) / 2);
	m_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx - 30) / 2);
	m_Rect.top = long(m_tInfo.fy - (m_tInfo.fcy - 40) / 2);
	m_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy - 40) / 2);

	return 0;
}

void CPlayer::Render(HDC _dc) {

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
			m_tFrame.iFrameEnd = 1;
			m_tFrame.iYIndex = 0;
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

		//로프를 탈때 애니메이션 멈추게 하기 위해서
		//제대로 안됨. 바닥에서 스케이트 탐.
		if (m_bAnimation_Stop == false) {
			++m_tFrame.iFrameStart;
		}
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		if (m_dwState != STATE_STAND && m_bRope_Check == false)
		{
			m_dwState = STATE_STAND;
		}
		m_tFrame.iFrameStart = 0;
	}
}

void CPlayer::KeyCheck(void)
{
	if (m_dwState != STATE_ATT) {
		//로프 타다가 점프 할때
		if ((m_bRope_Check == true && GETS(CKeyMgr)->OnceKeyDown(VK_SPACE))
			&& (GETS(CKeyMgr)->StayKeyDown(VK_LEFT) || GETS(CKeyMgr)->StayKeyDown(VK_RIGHT)))
		{
			m_bRope_Check = false;
			m_bJump = true;
			m_dwState = STATE_JUMP;

			//Rope 충돌 체크 안함.
			m_bRope_ColStop = true;
		}

		//일반 점프시 로프 충돌 막기(수정해야됨)
		//if (GETS(CKeyMgr)->OnceKeyDown(VK_SPACE) && GETS(CKeyMgr)->OnceKeyUp(VK_UP) && m_bJump == true)
			//m_bRope_ColStop = true;

		if (GETS(CKeyMgr)->StayKeyDown(VK_UP))
		{
			if (m_bRope_Check == true)
			{
				m_bAnimation_Stop = false;			//Animation 진행
				m_tInfo.fx = Rope_Ride()->fx + g_fScrollX;
				m_tInfo.fy -= m_fSpeed;
				g_fScrollY += m_fSpeed;

				m_pName = L"Player_Up";
				m_dwState = STATE_UP;
			}
		}
		else if (GETS(CKeyMgr)->OnceKeyUp(VK_UP))
		{
			if (m_bRope_Check == true)
			{
				m_bAnimation_Stop = true;
			}
		}

		if (GETS(CKeyMgr)->StayKeyDown(VK_DOWN))
		{
			if (m_bRope_Check == true) {
				m_bAnimation_Stop = false;
				m_pName = L"Player_Up";
				m_tInfo.fy += m_fSpeed;
				g_fScrollY -= m_fSpeed;
			}

			m_dwState = STATE_DOWN;
		}
		else if (GETS(CKeyMgr)->OnceKeyUp(VK_DOWN))
		{
			if (m_bRope_Check == true)
			{
				m_bAnimation_Stop = true;
			}
		}

		if (GETS(CKeyMgr)->StayKeyDown(VK_LEFT) && m_bRope_Check == false)
		{
			if (GETS(CSceneMgr)->GetSceneType() != SCENE_STAGE2) {
				m_tInfo.fx -= m_fSpeed;
			}
			g_fScrollX += m_fSpeed * 2;

			m_pName = L"Player_Left";
			m_dwState = STATE_WALK;
		}
		else if (GETS(CKeyMgr)->StayKeyDown(VK_RIGHT) && m_bRope_Check == false)
		{
			if (GETS(CSceneMgr)->GetSceneType() != SCENE_STAGE2) {
				m_tInfo.fx += m_fSpeed;
			}
			g_fScrollX -= m_fSpeed * 2;
			m_pName = L"Player_Right";
			m_dwState = STATE_WALK;
		}
		else if (GETS(CKeyMgr)->OnceKeyUp(VK_UP)
			|| GETS(CKeyMgr)->OnceKeyUp(VK_DOWN)
			|| GETS(CKeyMgr)->OnceKeyUp(VK_LEFT)
			|| GETS(CKeyMgr)->OnceKeyUp(VK_RIGHT))
		{
			if (m_bRope_Check == false)
			{
				m_dwState = STATE_STAND;
			}
			else
			{
				m_dwState = STATE_UP;
			}
		}

		if (GETS(CKeyMgr)->OnceKeyDown(VK_SPACE) && m_bJump == false)
		{
			//Jump
			m_bJump = true;
			m_fOldY = m_tInfo.fy;
			m_dwState = STATE_JUMP;
		}
		if (GETS(CKeyMgr)->StayKeyDown(VK_CONTROL))
		{
			m_dwState = STATE_HIT;
		}

		if (GETS(CKeyMgr)->StayKeyDown(VK_SHIFT))
		{
			m_dwState = STATE_SKILL;
		}
	}
}

void CPlayer::Scroll()
{
#pragma region 스테이지1
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE1) {
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
	}


#pragma endregion	
#pragma region 스테이지2
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE2) {
		if (g_fScrollX >= -4.f)
		{
			m_fSpeed = 4.f;
			g_fScrollX = 0;

			if (GETS(CKeyMgr)->StayKeyDown(VK_LEFT))
			{
				m_tInfo.fx -= m_fSpeed;
			}
			if (GETS(CKeyMgr)->StayKeyDown(VK_RIGHT))
			{
				m_tInfo.fx += m_fSpeed * 2;
			}
		}
		if (g_fScrollX <= -1972.f)
		{
			m_fSpeed = 4.f;
			g_fScrollX = -1972.f;

			if (GETS(CKeyMgr)->StayKeyDown(VK_LEFT))
			{
				m_tInfo.fx -= m_fSpeed * 2;
			}
			if (GETS(CKeyMgr)->StayKeyDown(VK_RIGHT))
			{
				m_tInfo.fx += m_fSpeed;
			}
		}
		/* 원래 기존의 방식 스크롤 방법.
		if (m_tInfo.fx >= 2910.f)
		{
			m_fSpeed = 4.f;
			g_fScrollX = -112.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy <= 95.f)
		{
		m_fSpeed = 4.f;
			g_fScrollY = 152.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy >= 1200.f)
		{
			m_fSpeed = 4.f;
			g_fScrollY = -408.f;
		}
		else
			m_fSpeed = 2.f;*/
	}
#pragma endregion
#pragma region 스테이지3
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE3) {
		if (m_tInfo.fx <= 516.f)
		{
			m_fSpeed = 4.f;
			g_fScrollX = -8.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fx >= 684.f)
		{
			m_fSpeed = 4.f;
			g_fScrollX = -344.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy <= -8.f)
		{
			m_fSpeed = 4.f;
			g_fScrollY = -88.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy <= 570.f)
		{
			m_fSpeed = 4.f;
			g_fScrollY = -38.f;
		}
		else
			m_fSpeed = 2.f;
	}
#pragma endregion
#pragma region 보스스테이지
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_BOSS) {
		if (m_tInfo.fx <= 526.f)	//왼
		{
			m_fSpeed = 4.f;
			g_fScrollX = -28.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fx >= 900.f)	//오
		{
			m_fSpeed = 4.f;
			g_fScrollX = -776.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy <= 260.f)	//위
		{
			m_fSpeed = 4.f;
			g_fScrollY = -252.f;
		}
		else
			m_fSpeed = 2.f;

		if (m_tInfo.fy >= 574.f)	//아래
		{
			m_fSpeed = 4.f;
			g_fScrollY = -8.f;
		}
		else
			m_fSpeed = 2.f;
	}
#pragma endregion
}

void CPlayer::Jump(void)
{
	//y = 중력가속도 * 시간 * 시간 * 0.5f + 시간 * 점프속도 + 점프파워
	if (m_bJump && m_bRope_Check == false)
	{
		//점프 시작으로부터 흐른 시간...
		m_fJumpAcc += 0.2f;
		m_tInfo.fy += 0.98f * m_fJumpAcc * m_fJumpAcc * 1.5f - 8.f;
	}

	if (m_tInfo.fy > m_fOldY && m_bJump == true)
	{
		m_fJumpAcc = 0.f;
		m_tInfo.fy = m_fOldY;
		m_bJump = false;
		m_bRope_ColStop = false;
	}
}

INFO* CPlayer::Rope_Ride(void)
{
	CObj* pMap = NULL;

	OBJITER iter_map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_map_end = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();

	for (iter_map; iter_map != iter_map_end; ++iter_map)
	{
		if (((CStage1_Map*)(*iter_map))->GetBgType() == BG_MAP)
		{
			pMap = (*iter_map);
		}
	}

	return &((CStage1_Map*)pMap)->GetRopeInfo();
}

bool CPlayer::Player_InfoCheck(void)
{
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE1) {
		if (24.f < m_tInfo.fx && m_tInfo.fx < 992.f) {
			return true;
		}
		else if (24.f > m_tInfo.fx) {
			m_tInfo.fx += m_fSpeed;
		}
		else if (992.f < m_tInfo.fx) {
			m_tInfo.fx -= m_fSpeed;
		}
	}
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE2) {
		if (24.f < m_tInfo.fx && m_tInfo.fx < 1000.f) {
			return true;
		}
		else if (24.f > m_tInfo.fx) {
			m_tInfo.fx += m_fSpeed;
		}
		else if (1000.f < m_tInfo.fx) {
			m_tInfo.fx -= m_fSpeed;
		}
	}
	if (GETS(CSceneMgr)->GetSceneType() == SCENE_STAGE3) {
		if (24.f < m_tInfo.fx && m_tInfo.fx < 454.f) {
			return true;
		}
		else if (24.f > m_tInfo.fx) {
			m_tInfo.fx += m_fSpeed;
		}
		else if (454.f < m_tInfo.fx) {
			m_tInfo.fx -= m_fSpeed;
		}
	}

	if (GETS(CSceneMgr)->GetSceneType() == SCENE_BOSS) {
		if (24.f < m_tInfo.fx && m_tInfo.fx < 998) {
			return true;
		}
		else if (24.f > m_tInfo.fx) {
			m_tInfo.fx += m_fSpeed;
		}
		else if (998.f < m_tInfo.fx) {
			m_tInfo.fx -= m_fSpeed;
		}
	}

	return false;
}

