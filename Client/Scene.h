#pragma once

class CScene
{
public:
	CScene(void);
	virtual ~CScene(void);

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual	void	Render(HDC _dc)PURE;
	virtual void	Release(void)PURE;
};