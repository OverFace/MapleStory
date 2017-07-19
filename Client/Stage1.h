#pragma once
#include "Scene.h"

class CStage1 : public CScene
{
public:
	CStage1(void);
	virtual ~CStage1(void);

public:
	virtual void Initialize(void);
	virtual int	 Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};