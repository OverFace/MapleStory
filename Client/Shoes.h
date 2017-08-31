#pragma once
#include "Item.h"

class CShoes : public CItem
{
public:
	CShoes(void);
	CShoes(TCHAR* pName);
	virtual ~CShoes(void);

public:
	void			SetShoes_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								  int _iHp, int _iMp, int _iPrice, int _iSalePrice, DWORD _dwOption);
	inline void		SetShoes_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};