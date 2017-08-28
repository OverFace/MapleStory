#pragma once
#include "Obj.h"

class CItem : public CObj
{
public:
	CItem(void);
	CItem(TCHAR* pName);
	virtual ~CItem(void);

protected:
	ITEM			m_tItem;

public:
	inline ITEM*	GetItemData(void) { return &m_tItem; }
	
public:
	void			SetItemDescription(TCHAR* pstr);
	void			SetItemDescription_Render(HDC _dc, float fx, float fy);

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual	void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;

protected:
	virtual void	Setting_ItemRect(void);
};