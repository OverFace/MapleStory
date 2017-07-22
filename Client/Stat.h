#pragma once
#include "UI.h"

class CStat : public CUi
{
public:
	CStat(void);
	virtual ~CStat(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};