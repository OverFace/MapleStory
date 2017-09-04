#pragma once
#include "UI.h"

class CSlot : public CUi
{
public:
	CSlot(void);
	virtual ~CSlot(void);

private:
	ITEM			m_tSlot_ItemData;
	int				m_iSlotNumber;

public: //Getter
	inline ITEM*    GetSlotData(void) { return &m_tSlot_ItemData; }
	inline int		GetSlotNumber(void) { return m_iSlotNumber; }

public: //Setter
	inline void		SetSlotData(ITEM& _rSlot) { memcpy_s(&m_tSlot_ItemData, sizeof(ITEM), &_rSlot, sizeof(ITEM)); }
	inline void		SetSlotNumber(int _iNumber) { m_iSlotNumber = _iNumber; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};