#pragma once
#include "Obj.h"


class CPlayer : public CObj {
private:
	list<LINE*>	m_pLineList;

	TCHAR * m_pName;
	FRAME   m_tFrame;
	DWORD	m_dwState;
	DWORD	m_dwPrevState;
	DWORD	m_dwFrameTime;
	POINT	m_ptOffset;

	bool	m_bJump;
	float  m_fJumpAcc;
	float	m_fOldY;
	float  m_fDownSpeed;

	eSceneType m_eSceneType;
public:
	void	SetLineList(list<LINE*>	pLine);
private:
	void FrameMove(void);
	void KeyCheck(void);
	void Scroll(void);
	void DynamicScroll(void);
	//void Jump(void);
	void LineCollision(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};