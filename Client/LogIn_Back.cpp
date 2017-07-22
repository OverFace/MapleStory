#include "stdafx.h"
#include "LogIn_Back.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CLogin_Back::CLogin_Back(void)
{
}

CLogin_Back::~CLogin_Back(void)
{
	Release();
}

void CLogin_Back::Initialize(void)
{
	m_tInfo.fcx = 1024.f;
	m_tInfo.fcy = 720.f;

	m_eRenderType = RENDER_BACKGROUND;	

	//커서 보이게 하기
	/*
	CreateCaret(g_hWnd, NULL, 1, 15);
	ShowCaret(g_hWnd);
	SetCaretPos(512, 360);
	*/
}

int CLogin_Back::Update(void)
{
	return 0;
}

void CLogin_Back::Render(HDC _dc)
{
	TransparentBlt(_dc,
		g_fScrollX, g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Login")->GetMemDC(),
		0, 0,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(255, 255, 255));	

	/*
	static TCHAR szInput = NULL;
	static TCHAR szcmp = NULL;
	static TCHAR szResult[512] = { NULL };
	static int   count = 0;

	static bool bCheck = false;
	if (WM_KEYDOWN)
	{
		if (g_wParam != 13)
		{
			szInput = (TCHAR)g_wParam;

			if (lstrcmp(&szInput, &szcmp) == 0)
			{
				memset(&szInput, NULL, sizeof(TCHAR));
			}

			if (bCheck == false)
			{
				lstrcpy(&szResult[count], &szInput);
				++count;
				bCheck = true;
			}			
		}
	}	

	if (WM_KEYUP)
	{
		if (g_wParam != 13)
		{
			szcmp = (TCHAR)g_wParam;				
		}		
		else
		{
			memset(&szcmp, NULL, sizeof(TCHAR));
		}		
		bCheck = false;
	}
				

	system("cls");
	cout << szcmp << endl;
	cout << szInput << endl;
	cout << bCheck << endl;

	TextOut(_dc, 512, 360, szResult, lstrlen(szResult));
	*/
}

void CLogin_Back::Release(void)
{
}

void CLogin_Back::Input_ID_PassWord(TCHAR* pStr)
{
	lstrcpy(m_szLogin, pStr);
}