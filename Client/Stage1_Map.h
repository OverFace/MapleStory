#pragma once
#include "Obj.h"

class CStage1_Map : public CObj
{
public:
	CStage1_Map(void);
	virtual ~CStage1_Map(void);

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