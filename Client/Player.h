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

	bool	m_bJump;
	float   m_bJumpAcc;
	float	m_bOldY;
	float   m_fDownSpeed;

	eSceneType m_eSceneType;
private:
	void FrameMove(void);
	void KeyCheck(void);
	void Scroll(void);
	void DynamicScroll(void);
	void Jump(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};