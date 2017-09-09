#pragma once
#include "UI.h"

class CStat : public CUi
{
public:
	CStat(void);
	virtual ~CStat(void);

private:
	HFONT				m_myFont;
	DWORD				m_dwTime;
	STAT				m_tStat;
	int					m_iStat_Limit;								//스텟 증가 한계치
	bool				m_bLevelUp_Check;

private: //Button
	INFO				m_tButton_Info[4];
	RECT				m_tButton_Rect[4];
	int					m_iButtonOption[4];
	RECT				m_tStatMove_rect;

public: //Getter
	inline STAT*		Get_PlayerStat(void) { return &m_tStat; }

public: //Setter
	inline void			Set_PlayerStat(STAT _tStat) { memcpy_s(&m_tStat, sizeof(STAT), &_tStat, sizeof(STAT)); }

private:
	void				Stat_Key(void);
	void				Stat_Poisiton(STAT& _rStat, HDC _dc);
	void				Stat_Button(void);
	void				Stat_Move(void);

private:
	void				Save_Data(void);
	void				Load_Data(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};