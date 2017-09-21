#pragma once
#include "UI.h"

class CSkill_Icon : public CUi
{
public:
	CSkill_Icon(void);
	virtual ~CSkill_Icon(void);

private:
	SKILL			m_tSkill;		 //Skill Icon 정보 구조체
	int				m_iSkill_Number; //Skill Number

public: //Getter
	inline SKILL*	Get_Skill_Icon_Info(void) { return &m_tSkill; }
	inline int		Get_Skill_Icon_Num(void) { return m_iSkill_Number; }

public: //Setter
	inline void		Set_Skill_Icon_Info(SKILL _tSkill) { memcpy_s(&m_tSkill, sizeof(SKILL), &_tSkill, sizeof(SKILL)); }
	inline void		Set_Skill_Icon_Num(int _iNum) { m_iSkill_Number = _iNum; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};