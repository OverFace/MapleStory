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
	float   m_fJumpAcc;
	float	m_fOldY;
	float   m_fDownSpeed;
	int		m_dSceneType;

	bool	m_bTile_Check;			//Tile Check
	bool	m_bRope_Check;			//Rope 충돌 확인
	bool	m_bRope_ColStop;		//Rope 충돌 멈추기
	bool	m_bAnimation_Stop;		//Animation stop Check

public:
	inline void	SetTile_Check(bool _bCheck) { m_bTile_Check = _bCheck; }
	inline void SetRope_Check(bool _bCheck) { if(m_bRope_ColStop == false) m_bRope_Check = _bCheck; }

private:
	void FrameMove(void);
	void KeyCheck(void);
	void Scroll(void);
	void Jump(void);
	INFO* Rope_Ride(void);
	bool Player_InfoCheck(void);
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};