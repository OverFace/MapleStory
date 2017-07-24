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

private: //Button
	INFO				m_tButton_Info[4];
	RECT				m_tButton_Rect[4];
	int					m_iButtonOption[4];

private:
	void				Stat_Key(void);
	void				Stat_Poisiton(STAT& _rStat, HDC _dc);
	void				Stat_Button(void);

private:
	void				Load_Data(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};