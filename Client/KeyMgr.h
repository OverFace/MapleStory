#pragma once

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
public:
	~CKeyMgr(void);

private:
	bool		m_bPress[256];

public:
	void		Update(void);
	bool		GetKeyState(int iKey);
	bool		GetKeyDown(int iKey);
	bool		GetKeyUp(int iKey);
};