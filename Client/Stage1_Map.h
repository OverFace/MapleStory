#pragma once
#include "Obj.h"

class CStage1_Map : public CObj
{
public:
	CStage1_Map(void);
	CStage1_Map(bool bCheck);
	virtual ~CStage1_Map(void);

private:
	bool			m_bRender;
	bool			m_bRender_Tile;
	bool			m_bStage_Check;
	vector<TILE*>	m_vecStage1_Tile;
	eBackGroundType m_eBgType;

private:
	INFO			m_tRopeInfo;
	RECT			m_tRopeRect;

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

public:
	inline eBackGroundType GetBgType(void) { return m_eBgType; }

public:
	inline vector<TILE*>*	GetStage1_Tile(void) { return &m_vecStage1_Tile; }

private:
	void			LoadData(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};