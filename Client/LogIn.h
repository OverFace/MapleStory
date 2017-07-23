#pragma once
#include "Scene.h"

class CLogIn : public CScene
{
public:
	CLogIn(void);
	virtual ~CLogIn(void);

private:
	bool			m_bLogin_Check;
	CObj*			m_pLogin;

public: 
	inline bool		GetLogin_Check(void) { return m_bLogin_Check; }
	
public:
	virtual void	Initialize(void);
	virtual int	    Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};