#pragma once
#include "UI.h"

class CItem;
class CSlot;
class CEquip : public CUi
{
public:
	CEquip(void);
	virtual ~CEquip(void);

private:
	list<CItem*>		m_Equip_ItemList;
	list<CSlot*>		m_Equip_SlotList;
	CItem*				m_pSelect_Item;
	CSlot*				m_pSelect_Slot;
	DWORD				m_dwTime;

private: //Equip Status Check
	bool				m_bEquipMoveCheck;
	bool				m_bEquipItem_CreateCheck;
	bool				m_bEquipItem_ApplyCheck;

private: //Button
	RECT				m_tEquipMove_Rect;
	INFO				m_tEquipEscButton_Info;
	RECT				m_tEquipEscButton_Rect;

public: //Getter
	inline list<CItem*>* GetEquip_ItemList(void) { return &m_Equip_ItemList; }
	inline bool			GetEquipItem_CreateCheck(void) { return m_bEquipItem_CreateCheck; }
	inline bool			GetEquip_MoveCheck(void) { return m_bEquipMoveCheck; }

public: //Setter
	inline void			SetEquipItem_CreateCheck(bool _bCheck) { m_bEquipItem_CreateCheck = _bCheck; }

private:
	void				Equip_Key(void);
	void				Equip_Move(void);

private: //Button
	void				Equip_EscButton_Click(void);

public: //Equip Function
	void				Equip_Item(CItem* pItem);
private:
	void				Equip_Slot_ItemCheck(CItem* pItem);
	CItem*				Equip_Item_Classification(CItem* pItem);
	void				Equip_Item_SetPosition(void);
	void				Equip_Apply_To_ItemArrtibute(CItem* pItem);

private: //Slot
	void				Equip_SlotCreate(void);
	void				Equip_SlotUpdqte(void);
	void				Equip_SlotRender(HDC _dc);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};