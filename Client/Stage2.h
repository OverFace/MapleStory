#pragma once
#include "Scene.h"

class CStage2 : public CScene
{
public:
	CStage2(void);
	virtual ~CStage2(void);

private:
	CObj*		 m_pMap;
	CObj*		 m_pPlayer;
	bool		 m_bCollisiton_Check;

private:
	void Stage2_TileCheck(void);


public:
	virtual void Initialize(void);
	virtual int	 Update(void);
	virtual void Render(HDC _dc);
	virtual void Release(void);
};