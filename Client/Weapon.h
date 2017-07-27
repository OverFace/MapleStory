#pragma once
#include "Item.h"

class CWeapon : public CItem
{
public:
	CWeapon(void);
	CWeapon(TCHAR* pName);
	virtual ~CWeapon(void);

public:
	void			SetWeapon_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								   int _iHp, int _iMp, int _iPrice, DWORD _dwOption);
	inline void		SetWeapon_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initalize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};