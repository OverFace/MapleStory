#pragma once
#include "UI.h"

class CHpBar : public CUi
{
public:
	CHpBar(void);
	virtual ~CHpBar(void);

public:
	virtual	void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};
