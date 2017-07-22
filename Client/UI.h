#pragma once
#include "Obj.h"

class CUi : public CObj
{
public:
	CUi(void);
	virtual ~CUi(void);

protected:
	POINT			m_ptMouse;
	eUiType			m_eUiType;
	bool			m_bVisible;

public:
	inline POINT*	GetPtMouse(void) { return &m_ptMouse; }
	inline eUiType	GetUiType(void) { return m_eUiType; }

public:
	inline void		SetVisible(void) { m_bVisible = true; }
	inline void		SetUnVisible(void) { m_bVisible = false; }

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;
};