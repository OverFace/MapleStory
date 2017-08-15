#pragma once
#include "Monster.h"

class CSlim : public CMonster {
private:
	TCHAR *			m_pName;
	FRAME			m_tFrame;
	DWORD			m_dwState;
	DWORD			m_dwPrevState;
	DWORD			m_dwFrameTime;
	POINT			m_ptOffset;

private: //AI bool 
	bool			m_bRight;		//와리가리 용도

private:
	void			FrameMove(void);

private: //AI
	void			Move(void);
	void			Attack(void);
	void			Hit(void);
	void			Dead(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);

public:
	CSlim(void);
	virtual ~CSlim(void);
};