#pragma once
#include "UI.h"

class CQuick_Slot;
class CSkill_Icon;
class CUi_QuickSlot : public CUi
{
public:
	CUi_QuickSlot(void);
	virtual ~CUi_QuickSlot(void);

private:
	list<CQuick_Slot*>	m_QuickSlot_List;
	list<CSkill_Icon*>	m_QuickSlot_SkillList;

private: //Quick Slot Status Check

public:	//Getter
	inline list<CQuick_Slot*>* Get_QuickSlot(void) { return &m_QuickSlot_List; }

public: //Setter

public: //Quick Slot Interlock To Skill UI
	void				QuickSlot_Set_SkillIcon(void);
	void				QuickSlot_Set_Position(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};