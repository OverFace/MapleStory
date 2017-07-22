#pragma once
#include "Obj.h"

class CLogin_Back : public CObj
{
public:
	CLogin_Back(void);
	virtual ~CLogin_Back(void);

private:
	TCHAR			m_szLogin[512];

public:
	void			Input_ID_PassWord(TCHAR* pStr);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};