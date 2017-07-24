#pragma once
#include "UI.h"

class CEquip : public CUi
{
public:
	CEquip(void);
	virtual ~CEquip(void);

private:
	DWORD				m_dwTime;

private:
	void				Equip_Key(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};