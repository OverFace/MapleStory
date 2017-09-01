#pragma once
#include "UI.h"

enum eInvenMode
{
	INVEN_EQUIP,
	INVEN_CONSUME,
	INVEN_ETC,
	INVEN_END
};

class CItem;
class CInven : public CUi
{
public:
	CInven(void);
	virtual	~CInven(void);

private:
	list<CItem*>	m_Inven_ItemList;			//Store Inven List
	list<CItem*>	m_Inven_EquipList;	
	list<CItem*>	m_Inven_ConsumeList;
	list<CItem*>	m_Inven_EtcList;
	DWORD			m_dwTime;

private: //Invne Stauts Check
	bool			m_bStoreInven_Check;
	bool			m_bInvenMode[INVEN_END];
	bool			m_bInvenItem_CreateCheck;

private: //Button
	RECT			m_tInvenMove_Rect;
	RECT			m_tInvenEquip_Rect;
	RECT			m_tInvenConsume_Rect;
	RECT			m_tInvenEtc_Rect;
	INFO			m_tInvenSelect_Info[3];
	RECT			m_tInven_EscButton_Rect;
	INFO			m_tInven_EscButton_Info;

public: //Getter
	inline list<CItem*>* GetInven_ItemList(void) { return &m_Inven_ItemList; }
	inline bool		Get_StoreCheck(void) { return m_bStoreInven_Check; }
	inline bool		Get_InvenItem_CreateCheck(void) { return m_bInvenItem_CreateCheck; }

public: //Setter
	inline void		Set_InvenItem(CItem* pItem) { m_Inven_ItemList.push_back(pItem); }
	inline void		Set_StoreCheck(bool _bCheck) { m_bStoreInven_Check = _bCheck; }
	inline void		Set_InvenItem_CreateCheck(bool _bCheck) { m_bInvenItem_CreateCheck = _bCheck; }

private:
	void			Inven_Key(void);
	void			Inven_Move(void);

private: //Button
	void			Inven_EscButton_Click(void);

private: //Inven Function
	void			Inven_SelectMenu(void);	
	void			Inven_Item_Render(HDC _dc);

public:	 //Classification
	void			Inven_ItemClassification(void);

private: //Save & Load
	void			Save_InvenData(void);
	void			Load_InvenData(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};