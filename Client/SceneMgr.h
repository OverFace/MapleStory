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
	eSceneType		m_eSceneType;

public:
	inline eSceneType GetSceneType(void) { return m_eSceneType; }
	const CScene*	GetCurrentScene(void);

public:
	void			SetScene(eSceneType eType);
	int				Update(void);
	void			Render(HDC _dc);

private:
	void			Release(void);
};