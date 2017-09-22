#pragma once
#include "UI.h"

class CSkill_Slot;
class CSkill_Icon;
class CSkill_UI : public CUi
{
public:
	CSkill_UI(void);
	virtual ~CSkill_UI(void);

private:
	vector<CSkill_Icon*>	m_vecSkill;
	INFO					m_tSkill_Input_Info;
	RECT					m_tSkill_Input_Rect;
	DWORD					m_dwTime;
	HFONT					m_myFont;

private: //Skill Stauts Check
	bool					m_bSkillMoveCheck;
	bool					m_bSkillPlus_Button_Visible;
	bool					m_bSkillLevel_Up_Check;

private: //Button
	RECT					m_tSkillMove_Rect;
	INFO					m_tSkill_EscButton_Info;
	RECT					m_tSkill_EscButton_Rect;

private: //Plus Button
	INFO					m_tSkill_PlusButton_Info[4];
	RECT					m_tSkill_PlusButton_Rect[4];
	int						m_iSkill_PlusButton_Option[4];

public: //Getter
	inline vector<CSkill_Icon*>* Get_Skill(void) { return &m_vecSkill; }

public: //Setter

private:
	void				Skill_Key(void);
	void				Skill_Move(void);
	void				Skill_Rect_Update(void);

private: //Button
	void				Skill_EscButton_Click(void);
	void				Skill_PlusButton_Click(void);

private: //Skill Function
	void				Skill_Icon_Create(void);
	void				Skill_Icon_Position(void);
	void				Skill_Icon_Update(void);
	void				Skill_Icon_Render(HDC _dc);
	void				Skill_Icon_InfoRender(HDC _dc);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};