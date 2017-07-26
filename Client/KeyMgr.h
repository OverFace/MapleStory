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
	bool		StayKeyDown(int iKey);		//Ű�� ������ �ִ��� üũ
	bool		OnceKeyDown(int iKey);		//Ű�� �ѹ� �������� üũ
	bool		OnceKeyUp(int iKey);		//Ű�� �Ѻ� �����ٰ� ���������� üũ
	bool		IsToggleKey(int iKey);		//�ѹ� ���������� On Off�� �ٲ�.
};