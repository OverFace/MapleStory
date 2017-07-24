#pragma once
#include "Scene.h"

class CStage3 : public CScene
{
public:
	CStage3(void);
	virtual ~CStage3(void);

public:
	virtual void Initialize(void);
	virtual int	 Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};