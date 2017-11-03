#pragma once
#include "Scene.h"

class CLine_Tool : public CScene
{
public:
	CLine_Tool(void);
	virtual ~CLine_Tool(void);
	
private: //Value
	float			m_fScrollSpeed;
	int				m_iChangeCount;
	bool			m_bStageCheck[4];
	bool			m_bLineCreate_Check;
	bool			m_bLineClick_Check;
	bool			m_bLineComplete_Check;
	list<LINE*>		m_LineList_Stage1;
	list<LINE*>		m_LineList_Stage2;
	list<LINE*>		m_LineList_Stage3;
	list<LINE*>		m_LineList_BossStage;
	LINEPOINT		m_tLine_Point_Left;
	LINEPOINT		m_tLine_Point_Right;

private: //BackGrond
	CObj*			m_pStage1_Back;
	CObj*			m_pStage1_Map;
	CObj*			m_pStage2_Map;
	CObj*			m_pStage3_Map;
	CObj*			m_pBStage_Back;
	CObj*			m_pBStage_Map;

private: //Function
	void			ShortCut_Key(void);
	void			Scene_Change(void);
	void			Save_Data(void);
	void			Load_Data(void);

private: //Line
	void			Create_Line(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void    Release(void);
};