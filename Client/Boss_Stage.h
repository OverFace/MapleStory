#pragma once
#include "Scene.h"

class CBoss_Stage : public CScene
{
public:
	CBoss_Stage(void);
	virtual ~CBoss_Stage(void);

public:
	virtual void Initialize(void);
	virtual int	 Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};