#pragma once
#include "Obj.h"
#include "SceneMgr.h"

class CPlayer : public CObj {
private:
	TCHAR * m_pName;
	FRAME   m_tFrame;
	DWORD	m_dwState;
	DWORD	m_dwPrevState;
	DWORD	m_dwFrameTime;
	POINT	m_ptOffset;

	bool	m_bJump;
	float   m_fJumpAcc;
	float	m_fOldY;
	float   m_fDownSpeed;
	int		m_dSceneType;

	bool	m_bTile_Check;
	bool	m_bRope_Check;

public:
	void	SetLineList(list<LINE*>	pLine);
	inline void	SetTile_Check(bool _bCheck) { m_bTile_Check = _bCheck; }
	inline void SetRope_Check(bool _bCheck) { m_bRope_Check = _bCheck; }

private:
	void FrameMove(void);
	void KeyCheck(void);
	void Scroll(void);
	void DynamicScroll(void);
	void Jump(void);
	void Rope_Ride(void);

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};