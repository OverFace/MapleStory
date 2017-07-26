#pragma once
#include "Obj.h"

class CItem : public CObj
{
public:
	CItem(void);
	virtual ~CItem(void);

protected:
	ITEM			m_tItem;

public:
	inline ITEM*	GetItemData(void) { return &m_tItem; }

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual	void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;
};