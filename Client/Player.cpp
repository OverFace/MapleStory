#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void) {

}

CPlayer::~CPlayer(void) {
	Release();
}

void CPlayer::Initialize(void) {
	m_tInfo.fx = 100;
	m_tInfo.fy = 100;
	m_tInfo.fcx = 100;
	m_tInfo.fcy = 100;
}

int CPlayer::Update(void) {
	CObj::Update();

	if (m_tInfo.fx < 0) {
		m_tInfo.fx = 0;
	}

	if (GetAsyncKeyState(VK_RIGHT)){
		m_tInfo.fx += 10;
	}

	if (GetAsyncKeyState(VK_LEFT)){
		m_tInfo.fx -= 10;
	}

	if (GetAsyncKeyState(VK_UP)){
		m_tInfo.fy -= 10;
	}

	if (GetAsyncKeyState(VK_DOWN)){
		m_tInfo.fy += 10;
	}

	return 0;
}

void CPlayer::Render(HDC _dc) {
	Rectangle(_dc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CPlayer::Release(void) {

}