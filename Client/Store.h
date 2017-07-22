#pragma once
#include "UI.h"

class CStore : public CUi
{
public:
	CStore(void);
	virtual ~CStore(void);

public:
	virtual void		Initialize(void);
	virtual	int			Update(void);
	virtual void		Render(HDC _dc);
	virtual void		Release(void);
};