#pragma once
#include "UI.h"

class CStatus : public CUi
{
public:
	CStatus(void);
	virtual ~CStatus(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};