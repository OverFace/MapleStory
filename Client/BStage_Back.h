#pragma once
#include "Obj.h"

class CBstage_Back : public CObj
{
public:
	CBstage_Back(void);
	virtual ~CBstage_Back(void);

private:
	bool			m_bRender;

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};