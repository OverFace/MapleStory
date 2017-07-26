#pragma once

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
public:
	~CKeyMgr(void);

private: //Before Modify
	bool		m_bPress[256];

public:  //Before Modify
	void		Update(void);
	bool		GetKeyState(int iKey);
	bool		GetKeyDown(int iKey);
	bool		GetKeyUp(int iKey);

private: //After Modify
	bool		m_bKeyDown[256];
	bool		m_bKeyUp[256];

public:  //After Modify
	bool		StayKeyDown(int iKey);		//키가 눌리고 있는지 체크
	bool		OnceKeyDown(int iKey);		//키가 한번 눌렀는지 체크
	bool		OnceKeyUp(int iKey);		//키가 한분 눌렀다가 떼어졌는지 체크
	bool		IsToggleKey(int iKey);		//한번 눌릴때마다 On Off로 바뀜.
};