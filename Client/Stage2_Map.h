#pragma once
#include "Obj.h"

class CStage2_Map : public CObj
{
public:
	CStage2_Map(void);
	virtual ~CStage2_Map(void);

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