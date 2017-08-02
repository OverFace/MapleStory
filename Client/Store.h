#pragma once
#include "UI.h"

class CItem;
class CStore : public CUi
{
public:
	CStore(void);
	virtual ~CStore(void);

private:
	list<CItem*>		 m_Store_ItemList;			
	CObj*				 m_pStore_Npc;
	INFO				 m_tScroll_Info;
	RECT				 m_tScroll_Rect;
	INFO				 m_tEscButton_Info;
	RECT				 m_tEscButton_Rect;

public:
	inline RECT*		 GetEscButton_Rect(void) { return &m_tEscButton_Rect; }
	inline list<CItem*>* GetStore_ItemList(void) { return &m_Store_ItemList; }

private:
	void				 Scroll_Move(void);
	void				 Item_View_Control(void);

public:
	virtual void		 Initialize(void);
	virtual	int			 Update(void);
	virtual void		 Render(HDC _dc);
	virtual void		 Release(void);
};