#pragma once
#include "Obj.h"

class CStage3_Map : public CObj
{
public:
	CStage3_Map(void);
	CStage3_Map(bool bCheck);
	virtual ~CStage3_Map(void);

private:
	bool			m_bRender;
	bool			m_bRender_Tile;
	bool			m_bStage_Check;
	vector<TILE*>	m_vecStage3_Tile;

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

private:
	void			LoadData(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};