#pragma once
#include "Obj.h"

class CMonster : public CObj
{
protected:
	CMonster(void);
	virtual ~CMonster(void);

protected:
	eMonsterState	m_eState;
	eMonsterState	m_ePreState;

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;
};