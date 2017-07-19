#pragma once
#include "Scene.h"

class CEdit : public CScene
{
public:
	CEdit(void);
	virtual ~CEdit(void);

private:
	vector<TILE*>	m_vecTile;
	vector<TILE*>	m_vecTile_Stage2;
	vector<TILE*>	m_vecTile_Stage3;
	vector<TILE*>	m_vecTile_BStage;

private: //Value
	float			m_fScrollSpeed;
	int				m_iChangeCount;
	int				m_iBoxNum;
	RECT			m_tBox;
	bool			m_bStageCheck[4];

private: //Backgroudn Point
	CObj*			m_pStage1_Back;
	CObj*			m_pStage1_Map;
	CObj*			m_pStage2_Map;
	CObj*			m_pStage3_Map;
	CObj*			m_pBStage_Back;
	CObj*			m_pBStage_Map;

private:
	TILE*			CreateTile(float _fx, float _fy, int _iCount);
	void			Picking(void);
	void			ShortCut_Key(void);
	void			Scene_Change(void);
	void			SaveData(void);
	void			LoadData(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void    Release(void);
};