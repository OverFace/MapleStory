#pragma once
#include "Scene.h"

class CLogo : public CScene
{
public:
	CLogo(void);
	virtual ~CLogo(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual	void	Render(HDC _dc);
	virtual void	Release(void);	
};