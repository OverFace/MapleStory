#pragma once
#include "Obj.h"

class CBstage_Map : public CObj
{
public:
	CBstage_Map(void);
	virtual ~CBstage_Map(void);

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