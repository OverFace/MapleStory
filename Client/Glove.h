#pragma once
#include "Item.h"

class CGlove : public CItem
{
public:
	CGlove(void);
	CGlove(TCHAR* pName);
	virtual ~CGlove(void);

public:
	void			SetGlove_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
							      int _iHp, int _iMp, int _iPrice, DWORD _dwOption);
	inline void		SetGlove_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};