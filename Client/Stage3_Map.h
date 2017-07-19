#pragma once
#include "Obj.h"

class CStage3_Map : public CObj
{
public:
	CStage3_Map(void);
	virtual ~CStage3_Map(void);

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