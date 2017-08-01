#pragma once
#include "Obj.h"

class CNpc : public CObj
{
public:
	CNpc(void);
	virtual ~CNpc(void);

protected:
	eNpcType			m_eNpcType;

public:
	inline eNpcType		GetNpcType(void) { return m_eNpcType; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Render(HDC _dc)PURE;
	virtual void		Release(void)PURE;
};