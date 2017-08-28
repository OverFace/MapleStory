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
	CItem*				 m_pSelect_Item;

private: //Button
	INFO				 m_tEscButton_Info[2];
	RECT				 m_tEscButton_Rect[2];
	INFO				 m_tBuyButton_Info;
	RECT				 m_tBuyButton_Rect;

private: //Scroll Status
	INFO				 m_tScroll_Info;
	RECT				 m_tScroll_Rect;
	bool				 m_bScrollMove;
	bool				 m_bScroll_Item_Check[4];

public:
	inline RECT*		 GetEscButton_Rect(int _iIndex) { return &m_tEscButton_Rect[_iIndex]; }
	inline list<CItem*>* GetStore_ItemList(void) { return &m_Store_ItemList; }

private: //Scroll 
	void				 Scroll_Move(void);
	void				 Item_View_Control(void);

private: //Buy & Sale
	void				 Select_SotreItem(void);
	void				 Buy_Button_Click(void);
	void				 Buy_StoreItem(CItem* pItem);

public:
	virtual void		 Initialize(void);
	virtual	int			 Update(void);
	virtual void		 Render(HDC _dc);
	virtual void		 Release(void);
};