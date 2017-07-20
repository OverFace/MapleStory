#pragma once
#include "Obj.h"

class CLogin_Back : public CObj
{
public:
	CLogin_Back(void);
	virtual ~CLogin_Back(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};