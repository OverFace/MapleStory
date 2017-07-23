#pragma once
#include "UI.h"

class CExpBar : public CUi
{
public:
	CExpBar(void);
	virtual ~CExpBar(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};