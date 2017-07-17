#pragma once

class CMainGame
{
public:
	CMainGame(void);
	~CMainGame(void);

private:
	HDC		m_DC;
	DWORD   m_dwFrameTime;
	int     m_iFps;
	TCHAR   m_szFrameBuf[128];

public:
	void    Initialize(void);
	int		Update(void);
	void	Render(void);
	void	Release(void);
};