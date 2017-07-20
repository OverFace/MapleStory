#include "StdAfx.h"
#include "Player.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "ObjMgr.h"
CPlayer::CPlayer(void) {
	m_isizex = 90.f;
	m_isizey = 100.f;
}

CPlayer::~CPlayer(void) {
	Release();
}

void CPlayer::Initialize(void) {
	m_fAngle = 90.f;
	m_tInfo.fx = (float)WINCX / 2;
	m_tInfo.fy = 400.f;
	m_tInfo.fcx = 100.f;
	m_tInfo.fcy = 100.f;

	m_eRenderType = RENDER_WORLDOBJ;
}

int CPlayer::Update(void) {

	if (m_tInfo.fx < 0) {
		m_tInfo.fx = 0.f;
	}

	if (GetAsyncKeyState(VK_RIGHT)){
		m_tInfo.fx += 10.f;
	}

	if (GetAsyncKeyState(VK_LEFT)){
		m_tInfo.fx -= 10.f;
	}

	if (GetAsyncKeyState(VK_UP)){
		m_tInfo.fy -= 10.f;
	}

	if (GetAsyncKeyState(VK_DOWN)){
		m_tInfo.fy += 10.f;
	}
	CObj::Update();
	return 0;
}

void CPlayer::Render(HDC _dc) {
	//Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);

	TransparentBlt(_dc, int(m_tInfo.fx) - m_isizex / 2, int(m_tInfo.fy) - m_isizey / 2,
		m_isizex, m_isizey, CBitMapMgr::GetInstance()->FindImage(L"Player_Left")->GetMemDC(),
		0, 0, m_isizex, m_isizey
		, RGB(71, 0, 60));
}

void CPlayer::Release(void) {

}