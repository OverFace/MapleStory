#pragma once
#include "Obj.h"

class CBstage_Map : public CObj
{
public:
	CBstage_Map(void);
	CBstage_Map(bool bCheck);
	virtual ~CBstage_Map(void);

private:
	bool			m_bRender;
	bool			m_bRender_Tile;
	bool			m_bStage_Check;
	vector<TILE*>	m_vecBtage_Tile;
	list<LINE*>		m_StageBoss_LineList;
	HPEN			m_Pen;

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