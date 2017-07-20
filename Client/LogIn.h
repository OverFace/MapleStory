#pragma once
#include "Scene.h"

class CLogIn : public CScene
{
public:
	CLogIn(void);
	virtual ~CLogIn(void);

public:
	virtual void	Initialize(void);
	virtual int	    Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};