#pragma once
#include "Item.h"

class CMesso : public CItem
{
public:
	CMesso(void);
	CMesso(TCHAR* pName);
	virtual ~CMesso(void);

private:
	int				m_iMesso_XIndex;
	int				m_iMesso_YIndex;

public:
	void			SetMesso_Data(int _iStr, int _iDex, int _iInt, int _iLuk,
								  int _iHp, int _iMp, int _iPrice, DWORD _dwOption);
	inline void		SetMesso_Pos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }

public:
	virtual void	Initalize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};