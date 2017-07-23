#pragma once
#include "Obj.h"


class CPlayer : public CObj {
private:
	TCHAR * m_pName;
	FRAME   m_tFrame;
	DWORD	m_dwState;
	DWORD	m_dwPrevState;
	DWORD	m_dwFrameTime;
	POINT	m_ptOffset;

	int m_iAlpha;
	int m_isizex;
	int m_isizey;

private:
	void	FrameMove(void);
	void KeyCheck(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};