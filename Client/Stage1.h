#pragma once
#include "Scene.h"

class CStage1 : public CScene
{
public:
	CStage1(void);
	virtual ~CStage1(void);

private:
	CObj*		 m_pMap;
	CObj*		 m_pPlayer;
	bool		 m_bCollisiton_Check;

private:
	void		 Stage1_TileCheck(void);
	void		 Rope_Check(void);


public:
	virtual void Initialize(void);
	virtual int	 Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};