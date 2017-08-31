#pragma once
#include "Item.h"

class CAccessory : public CItem
{
public:
	CAccessory(void);
	CAccessory(TCHAR* pName, eItemType _eType);
	virtual ~CAccessory(void);

public:
	void			SetAccessory_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								      int _iHp, int _iMp, int _iPrice, int _iSalePrice, DWORD _dwOption);
	inline void		SetAccessory_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};