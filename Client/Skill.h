#pragma once
#include "UI.h"

class CSkill_UI : public CUi
{
public:
	CSkill_UI(void);
	virtual ~CSkill_UI(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};