#pragma once
#include "UI.h"

class CSkill_Slot : public CUi
{
public:
	CSkill_Slot(void);
	virtual ~CSkill_Slot(void);

private:
	int			m_iSlotNumber;

public: //Getter
	inline int		Get_SlotNumber(void) { return m_iSlotNumber; }

public: //Setter
	inline void		Set_SlotNumber(int _iNum) { m_iSlotNumber = _iNum; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};