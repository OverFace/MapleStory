#pragma once
#include "UI.h"

class CMpBar : public CUi
{
public:
	CMpBar(void);
	virtual ~CMpBar(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};