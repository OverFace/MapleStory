#pragma once
#include "Npc.h"

class CStore_Npc : public CNpc
{
public: 
	CStore_Npc(void);
	CStore_Npc(CObj* pStore);
	virtual ~CStore_Npc(void);

private:
	RECT			m_tNpc_Rect;
	FRAME			m_tNpc_Frame;
	DWORD			m_dwFrameTime;
	CObj*			m_pStore;
	bool			m_bStoreOpen_Check;

private:
	void			FrameMove(void);
	void			Rect_Check(void);

private:
	void			Store_Key(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};