#pragma once
#include "UI.h"

class CSkill_Slot : public CUi
{
public:
	CSkill_Slot(void);
	virtual ~CSkill_Slot(void);

private:
	SKILL		m_tSkill;
	int			m_iSlotNumber;

public: //Getter

public: //Setter

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};