#pragma once
#include "UI.h"

class CSkill_Icon : public CUi
{
public:
	CSkill_Icon(void);
	virtual ~CSkill_Icon(void);

private:
	SKILL			m_tSkill;					 //Skill Icon 정보 구조체
	int				m_iSkill_Number;			 //Skill Number
	int				m_iSkill_QuickSlot_Number;	 //Quick Slot Skill Number
	bool			m_bSkill_Icon_Check;		 //Skill On Check
	bool			m_bSkill_QuickSlot_SetCheck; //Quick Slot Setting Check
	HFONT			m_myFont;


public: //Getter
	inline SKILL*	Get_Skill_Icon_Info(void) { return &m_tSkill; }
	inline int		Get_Skill_Icon_Num(void) { return m_iSkill_Number; }
	inline bool		Get_Skill_Icon_Check(void) { return m_bSkill_Icon_Check; }
	inline int		Get_Skill_Icon_QuickNumber(void) { return m_iSkill_QuickSlot_Number; }
	inline bool		Get_Skill_Icon_QuickSetCheck(void) { return m_bSkill_QuickSlot_SetCheck; }

public: //Setter
	inline void		Set_Skill_Icon_Info(SKILL _tSkill) { memcpy_s(&m_tSkill, sizeof(SKILL), &_tSkill, sizeof(SKILL)); }
	inline void		Set_Skill_Icon_Num(int _iNum) { m_iSkill_Number = _iNum; }
	inline void		Set_Skill_Icon_Check(bool _bCheck) { m_bSkill_Icon_Check = _bCheck; }
	inline void		Set_Skill_Icon_Level(int _iLevel) { m_tSkill.m_iSkill_Level = _iLevel; }
	inline void		Set_Skill_Icon_Att(float _fAtt) { m_tSkill.m_fSkill_Att = _fAtt; }
	inline void		Set_Skill_Icon_QuickNumber(int _iNumber) { m_iSkill_QuickSlot_Number = _iNumber; }
	inline void		Set_Skill_Icon_QuickSetCheck(bool _bCheck) { m_bSkill_QuickSlot_SetCheck = _bCheck; }
	inline void		Set_Skill_Icon_CoolTime(float _fTime) { m_tSkill.m_fSkill_CoolTime = _fTime; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};