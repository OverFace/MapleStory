#pragma once
#include "UI.h"

class CItem;
class CSlot;
class CStore : public CUi
{
public:
	CStore(void);
	virtual ~CStore(void);

private: //Font
	HFONT			 	 m_myFont;
	HFONT				 m_myConsumeItem_Font;
	
private: //Container
	list<CItem*>		 m_Store_ItemList;		
	list<ITEM>			 m_Temp_StoreInvenList;

private:
	CObj*				 m_pStore_Npc;
	CItem*				 m_pSelect_Item;
	bool				 m_bSale_Check;
	bool				 m_bPotion_Check[2];

private:
	list<CSlot*>		 m_Store_SlotList;
	list<CSlot*>		 m_Store_InvenSlot_List;

private: //Button
	INFO				 m_tEscButton_Info[2];
	RECT				 m_tEscButton_Rect[2];
	INFO				 m_tBuyButton_Info;
	RECT				 m_tBuyButton_Rect;
	INFO				 m_tSaleButton_Info;
	RECT				 m_tSaleButton_Rect;

private: //Store Scroll Status
	INFO				 m_tScroll_Info;
	RECT				 m_tScroll_Rect;
	bool				 m_bScrollMove;
	bool				 m_bScroll_Item_Check[4];

private: //Store Inven Scroll Status
	INFO				 m_tStoreInven_Scroll_Info;
	RECT				 m_tStoreInven_Scroll_Rect;
	bool				 m_bStoreInven_ScrollMove;
	int					 m_iStoreInven_ItemCount;

public: //Getter
	inline RECT*		 GetEscButton_Rect(int _iIndex) { return &m_tEscButton_Rect[_iIndex]; }
	inline list<CItem*>* GetStore_ItemList(void) { return &m_Store_ItemList; }
	inline list<CSlot*>* GetStore_InvenSlot_List(void) { return &m_Store_InvenSlot_List; }

public: //Setter
	inline void			 SetStore_InvenItemCount(int _iCount) { m_iStoreInven_ItemCount = _iCount; }

private: //Store Scroll 
	void				 Scroll_Move(void);
	void				 Item_View_Control(void);

private: //Store Inven Scroll
	void				 StoreInven_Scroll_Move(void);
	void				 StoreInven_ItemView_Control(void);

private: //Buy & Sale
	void				 Select_StoreItem(void);		
	void				 Select_StoreInvenItem(void);
	void				 Buy_Button_Click(void);		
	void				 Buy_StoreItem(CItem* pItem);  
	void				 Buy_StoreItem_Render(HDC _dc);
	void				 Sale_Button_Click(void);
	void				 Sale_StoreInven_Item(CItem* pItem);

private: //Slot
	void				 Store_InvenSlotUpdate(void);
	void				 Store_InvenSlotRender(HDC _dc);

private: //Messo Present
	void				 Messo_Present(HDC _dc);

public:
	virtual void		 Initialize(void);
	virtual	int			 Update(void);
	virtual void		 Render(HDC _dc);
	virtual void		 Release(void);
};