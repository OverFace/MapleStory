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
	list<LINE*>		m_Stage1_LineList;
	HPEN			m_Pen;

private:
	INFO			m_tRopeInfo;
	RECT			m_tRopeRect;

private:
	INFO			m_tOverTile_Info;
	RECT			m_tOverTile_Rect;

private:
	eBGType			m_eBGType;

public:
	inline eBGType  GetBgType(void) { return m_eBGType; }
	inline RECT		GetRope(void) { return m_tRopeRect; }
	inline INFO     GetRopeInfo(void) { return m_tRopeInfo; }
	inline RECT     GetOverTIleRect(void) { return m_tOverTile_Rect; }
	inline INFO     GetOverTileInfo(void) { return m_tOverTile_Info; }

public:
	inline void		SetRedner(bool _bRender) { m_bRender = _bRender; }

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