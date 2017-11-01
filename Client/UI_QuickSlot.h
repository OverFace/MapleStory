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
	CSkill_Icon*		m_pSelect_SkillIcon;
	bool				m_bSkill_Icon_DragCheck;
	bool				m_bSkill_Icon_DropCheck;
	bool				m_bSkill_Icon_OverlapCheck;
	bool				m_bSkill_Icon_SwapCheck;
	bool				m_bSkill_Icon_EscapeCheck;

private: //Quick Slot Status Check
	bool				m_bSkill_Icon_pushCheck;

public:	//Getter
	inline list<CQuick_Slot*>* Get_QuickSlot(void) { return &m_QuickSlot_List; }
	inline bool			Get_QuickSlot_EscapeCheck(void) { return m_bSkill_Icon_EscapeCheck; }

public: //Setter
	inline void			Set_QuickSlot_EscapeCheck(bool _bCheck) { m_bSkill_Icon_EscapeCheck = _bCheck; }

private: //Quick Slot Interlock To Skill UI
	void				QuickSlot_Set_SkillIcon(void);
	void				QuickSlot_Set_SkillIcon_Position(void);
	void				QuickSlot_Set_SkillIcon_Active(void);

	/*     기능 변경 하여서 필요 없는 부분.
	void				QuickSlot_Drag_SkillIcon(void);
	void				QuickSlot_Escape_SkillIcon(void);
	void				QuickSlot_Drop_Swap_SkillIcon(void);
	void				QuickSlot_Swap_SkillIcon(void);
	*/

private: //Quick Slot Render
	void				QuickSlot_Skill_Icon_Render(HDC _dc);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};