#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	~CSceneMgr(void);

private:
	CScene*			m_pScene;
	CScene*			m_pNextScene;
	bool			m_bChangeScene;

public:
	const CScene*	GetCurrentScene(void);

public:
	void			SetScene(eSceneType eType);
	int				Update(void);
	void			Render(HDC _dc);

private:
	void			Release(void);
};