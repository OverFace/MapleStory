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
	inline void		SetITem_EquipStatus(DWORD _dwStatus) { m_tItem.m_dwEquip_Status = _dwStatus; }
	inline void		SetItem_EquipType(eEquipType _eType) { m_tItem.m_eEquip_Type = _eType; }
	inline void		SetItem_Count(int _iCount) { m_tItem.m_iCount = _iCount; }
	inline void		SetItem_SlotNumber(DWORD _dwNumber) { m_tItem.m_dwInven_SlotNumber = _dwNumber; }
	inline void		SetItemData(ITEM _tItem) { memcpy_s(&m_tItem, sizeof(ITEM), &_tItem, sizeof(ITEM)); }
	void			SetItemDescription(TCHAR* pstr);
	void			SetItemDescription_Render(HDC _dc, float fx, float fy);
	void			SetSaleItemDescription_Render(HDC _dc, float fx, float fy);

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual	void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;

protected:
	virtual void	Setting_ItemRect(void);
};