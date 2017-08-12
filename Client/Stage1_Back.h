#pragma once
#include "Obj.h"

class CStage1_Back : public CObj
{
public:
	CStage1_Back(void);
	virtual ~CStage1_Back(void);

private:
	bool			m_bRender;

private:
	eBGType			m_eBGType;

public:
	inline eBGType  GetBgType(void) { return m_eBGType; }

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};