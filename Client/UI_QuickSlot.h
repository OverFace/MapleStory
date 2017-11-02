#pragma once
#include "UI.h"

class CQuick_Slot;
class CSkill_Icon;
class CItem;
class CUi_QuickSlot : public CUi
{
public:
	CUi_QuickSlot(void);
	virtual ~CUi_QuickSlot(void);

private:
	list<CQuick_Slot*>	m_QuickSlot_List;
	list<CSkill_Icon*>	m_QuickSlot_SkillList;
	list<CItem*>		m_QuickSlot_ItemList;
	CSkill_Icon*		m_pSelect_SkillIcon;

private: //Quick Slot Status Check
	bool				m_bSkill_Icon_pushCheck;
	bool				m_bItem_Icon_pushCheck;
	bool				m_bSkill_CutDownKey_check[CK_END];
	bool				m_bSkill_Cool_TimeCheck[4];

public:	//Getter
	inline list<CQuick_Slot*>* Get_QuickSlot(void) { return &m_QuickSlot_List; }

public: //Setter
	void				Set_QuickSlot_SkillIcon_CoolTime(float _fTime, int _iSkillNum);

private: //Quick Slot Interlock To Skill UI
	void				QuickSlot_Set_SkillIcon(void);
	void				QuickSlot_Set_SkillIcon_Position(void);
	void				QuickSlot_Set_SkillIcon_Active(void);
	void				QuickSlot_Set_SkillIcon_CutDownKey(void);
	void				QuickSlot_SkillIcon_CoolTime(void);

private: //Quick Slot Interlock To Inven UI
	void				QuickSlot_Set_ItemIcon(void);
	void				QuickSlot_Set_ItemIcon_Position(void);
	void				QuickSlot_Set_ItemIcon_CutDownKey(void);

private: //Quick Slot Render
	void				QuickSlot_Skill_Icon_Render(HDC _dc);
	void				QuickSlot_Item_Icon_Render(HDC _dc);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};