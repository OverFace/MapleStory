#pragma once
#include "UI.h"

class CSkill_Input : public CUi
{
public:
	CSkill_Input(void);
	CSkill_Input(INFO& _rInfo);
	virtual ~CSkill_Input(void);

private:
	float				m_fx;
	float				m_fy;
	DWORD				m_dwTime;
	INFO				m_tSkill_Info;

private:
	void				Skill_Key(void);

public:
	inline  void		SetSkillPos(INFO& rInfo) { m_tInfo = rInfo; }

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};