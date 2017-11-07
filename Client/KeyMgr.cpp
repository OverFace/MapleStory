#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
{
	memset(m_bPress, 0, sizeof(m_bPress));
	ZeroMemory(m_bKeyDown, sizeof(m_bKeyDown));
	ZeroMemory(m_bKeyUp, sizeof(m_bKeyUp));
}

CKeyMgr::~CKeyMgr(void)
{

}

void CKeyMgr::Update(void)
{
	for (int i = 0; i < 256; ++i)
	{
		/*
		if (GetAsyncKeyState(i) && m_bPress[i] == false)
		{
			m_bPress[i] = true;
		}

		if (!GetAsyncKeyState(i) && m_bPress[i] == true)
		{
			m_bPress[i] = false;
		}
		*/

		if (!GetAsyncKeyState(i) && m_bKeyDown[i] == true)
		{
			m_bPress[i] = false;
		}

		if (!GetAsyncKeyState(i) && m_bKeyUp[i] == true)
		{
			m_bPress[i] = false;
		}
	}
}

bool CKeyMgr::GetKeyState(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8001)
		return true;

	return false;
}

bool CKeyMgr::GetKeyDown(int iKey)
{
	if (GetAsyncKeyState(iKey) && m_bPress[iKey] == false)
		return true;

	return false;
}

bool CKeyMgr::GetKeyUp(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x0001)
		return true;

	return false;
}

bool CKeyMgr::StayKeyDown(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::OnceKeyDown(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		if (m_bKeyDown[iKey] == false)
		{
			m_bKeyDown[iKey] = true;
			return true;
		}
	}
	else
	{
		m_bKeyDown[iKey] = false;
	}

	return false;
}

bool CKeyMgr::OnceKeyUp(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
	{
		m_bKeyUp[iKey] = true;
	}
	else
	{
		if (m_bKeyUp[iKey] == true)
		{
			m_bKeyUp[iKey] = false;
			return true;
		}
	}

	return false;
}

bool CKeyMgr::IsToggleKey(int iKey)
{
	if (GetKeyState(iKey) & 0x0001)
		return true;

	return false;
}
