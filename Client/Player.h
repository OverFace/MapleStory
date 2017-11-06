#pragma once
#include "Obj.h"

class CPlayer : public CObj {
public:
	CPlayer(void);
	virtual ~CPlayer(void);

private:
	TCHAR*  m_pName;
	FRAME   m_tFrame;
	DWORD	m_dwState;
	DWORD	m_dwPrevState;
	DWORD	m_dwFrameTime;

private: //Scroll
	POINT	m_ptOffset;

private: //Jump
	bool	m_bJump;
	float   m_fJumpAcc;
	float	m_fOldY;
	float   m_fDownSpeed;

private:
	int		m_iMoney;

private: //Scene Change Check
	int		m_dSceneType;

private: //Collision
	bool	m_bTile_Check;			//Tile Check
	bool	m_bRope_Check;			//Rope 충돌 확인
	bool	m_bRope_ColStop;		//Rope 충돌 멈추기
	bool	m_bAnimation_Stop;		//Animation stop Check

public: //Getter
	inline int		GetMoney(void) { return m_iMoney; }

public: //Setter
	inline void		SetTile_Check(bool _bCheck) { m_bTile_Check = _bCheck; }
	inline void		SetRope_Check(bool _bCheck) { if(m_bRope_ColStop == false) m_bRope_Check = _bCheck; }
	inline void		SetRope_CollStop(bool _bcheck) { m_bRope_ColStop = _bcheck; }
	inline void		SetMoney(int _iMoney) { m_iMoney += _iMoney; }

private:
	void			Player_FrameMove(void);
	void			Player_KeyCheck(void);
	void			Scroll(void);
	void			Jump(void);
	INFO*			Rope_Ride(void);
	bool			Player_InfoCheck(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};