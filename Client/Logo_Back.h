#pragma once
#include "Obj.h"

class CLogo_Back : public CObj
{
public:
	CLogo_Back(void);
	virtual ~CLogo_Back(void);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};