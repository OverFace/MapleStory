#pragma once
#include "Item.h"

class CHelmet : public CItem
{
public:
	CHelmet(void);
	CHelmet(TCHAR* pName);
	virtual ~CHelmet(void);

public:
public:
	void			SetHelmet_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								   int _iHp, int _iMp, int _iPrice, int _iSalePrice, DWORD _dwOption);
	inline void		SetHelmet_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};