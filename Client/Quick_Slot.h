#pragma once
#include "UI.h"

class CQuick_Slot : public CUi
{
public:
	CQuick_Slot(void);
	virtual ~CQuick_Slot(void);

private:
	int				m_iSlotNumber;
	eCutDown_Key	m_eCutDonwKey;

public: //Getter
	inline int		Get_SlotNumber(void) { return m_iSlotNumber; }
	inline eCutDown_Key Get_SlotCutDown_Key(void) { return m_eCutDonwKey; }

public: //Setter
	inline void		Set_SlotNumber(int _iNum) { m_iSlotNumber = _iNum; }
	inline void		Set_Slot_CutDpwn_Key(eCutDown_Key eType) { m_eCutDonwKey = eType; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};