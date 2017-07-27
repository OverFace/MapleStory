#pragma once
#include "UI.h"

class CStore : public CUi
{
public:
	CStore(void);
	virtual ~CStore(void);

public:
	inline RECT*		GetEscButton_Rect(void) { return &m_tEscButton_Rect; }

private:
	INFO				m_tEscButton_Info;
	RECT				m_tEscButton_Rect;

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};