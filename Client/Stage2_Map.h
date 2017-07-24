#pragma once
#include "Obj.h"

class CStage2_Map : public CObj
{
public:
	CStage2_Map(void);
	CStage2_Map(bool bCheck);
	virtual ~CStage2_Map(void);

private:
	bool			m_bRender;
	bool			m_bRender_Tile;
	bool			m_bStage_Check;
	vector<TILE*>	m_vecStage2_Tile;

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

private:
	void			LoadDate(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};