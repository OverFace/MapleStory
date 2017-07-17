#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr(void)
{
	memset(m_bPress, 0, sizeof(m_bPress));
}

CKeyMgr::~CKeyMgr(void)
{

}

void CKeyMgr::Update(void)
{
	for (int i = 0; i < 256; ++i)
	{
		if (GetAsyncKeyState(i) && m_bPress[i] == false)
		{
			m_bPress[i] = true;
		}

		if (!GetAsyncKeyState(i) && m_bPress[i] == true)
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
