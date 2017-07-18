#pragma once

class CBitMap;
class CBitMapMgr
{
	DECLARE_SINGLETON(CBitMapMgr)
public:
	~CBitMapMgr(void);

private:
	map<const TCHAR*, CBitMap*>			m_MapBit;

public:
	void		Initialize(void);
	void		LoadImage(const TCHAR* pFileName, const TCHAR* pKey);
	CBitMap*	FindImage(const TCHAR* pKey);
	void		LoadImageByScene(eSceneType eType);

private:
	void		Release(void);
};