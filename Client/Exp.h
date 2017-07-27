#pragma once
#include "Item.h"

class CExp : public CItem
{
public:
	CExp(void);
	CExp(TCHAR* pName);
	virtual ~CExp(void);

public:
	void			SetExp_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								int _iHp, int _iMp, int _iPrice, DWORD _dwOption);
	inline void		SetExp_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initalize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};