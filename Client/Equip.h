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

private: //Button
	RECT				m_tEquipMove_Rect;
	INFO				m_tEquipEscButton_Info;
	RECT				m_tEquipEscButton_Rect;

public: //Getter
	inline list<CItem*>* GetEquip_ItemList(void) { return &m_Equip_ItemList; }
	
public: //Setter

private:
	void				Equip_Key(void);
	void				Equip_Move(void);

private: //Button
	void				Equip_EscButton_Click(void);

private: //Equip Function

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