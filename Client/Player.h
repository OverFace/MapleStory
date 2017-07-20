#pragma once
#include "Obj.h"


class CPlayer : public CObj {
private:
	int m_isizex;
	int m_isizey;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};