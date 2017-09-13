#pragma once
#include "UI.h"

class CSlot : public CUi
{
public:
	CSlot(void);
	virtual ~CSlot(void);

private:
	eEquipType		m_eEquip_Type;
	bool			m_bEquip_SlotCheck;
	DWORD			m_dwEquip_Status;		//Equip Slot에 아이템이 장착되있는지 판단.

private:
	ITEM			m_tSlot_ItemData;
	int				m_iSlotNumber;

public: //Getter
	inline ITEM*    GetSlotData(void) { return &m_tSlot_ItemData; }
	inline int		GetSlotNumber(void) { return m_iSlotNumber; }
	inline eEquipType GetEquipType(void) { return m_eEquip_Type; }
	inline bool		GetEquipSlot_Check(void) { return m_bEquip_SlotCheck; }
	inline DWORD	GetEquip_Status(void) { return m_dwEquip_Status; }

public: //Setter
	inline void		SetSlotData(ITEM& _rSlot) { memcpy_s(&m_tSlot_ItemData, sizeof(ITEM), &_rSlot, sizeof(ITEM)); }
	inline void		SetSlotNumber(int _iNumber) { m_iSlotNumber = _iNumber; }
	inline void		SetEquipType(DWORD _dwType) { m_eEquip_Type = eEquipType(_dwType); }
	inline void		SetEquipSlot_Check(bool _bCheck) { m_bEquip_SlotCheck = _bCheck; }
	inline void		SetEquip_Status(DWORD _dwStatus) { m_dwEquip_Status = _dwStatus; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};