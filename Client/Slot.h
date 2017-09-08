#pragma once
#include "UI.h"

enum eEquipType
{
	EQUIP_RING,
	EQUIP_HELMET,
	EQUIP_ARMOR,
	EQUIP_PANTS,
	EQUIP_GLOVES,
	EQUIP_SHOES,
	EQUIP_WEAPON,
	EQUIP_END
};

class CSlot : public CUi
{
public:
	CSlot(void);
	virtual ~CSlot(void);

private:
	eEquipType		m_eEquip_Type;
	ITEM			m_tSlot_ItemData;
	int				m_iSlotNumber;

public: //Getter
	inline ITEM*    GetSlotData(void) { return &m_tSlot_ItemData; }
	inline int		GetSlotNumber(void) { return m_iSlotNumber; }
	inline eEquipType GetEquipType(void) { return m_eEquip_Type; }

public: //Setter
	inline void		SetSlotData(ITEM& _rSlot) { memcpy_s(&m_tSlot_ItemData, sizeof(ITEM), &_rSlot, sizeof(ITEM)); }
	inline void		SetSlotNumber(int _iNumber) { m_iSlotNumber = _iNumber; }
	inline void		SetEquipType(DWORD _dwType) { m_eEquip_Type = eEquipType(_dwType); }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};