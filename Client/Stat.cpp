#include "stdafx.h"
#include "Stat.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"

CStat::CStat(void)
{
	m_eUiType = UI_STAT;
	m_dwTime = 0;
	m_iStat_Limit = 0;
	m_bLevelUp_Check = false;
	
	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&m_tButton_Info[i], sizeof(INFO));
		ZeroMemory(&m_tButton_Rect[i], sizeof(RECT));
		m_iButtonOption[i] = 0;
	}
	ZeroMemory(&m_tStatMove_rect, sizeof(RECT));
}

CStat::~CStat(void)
{
	Release();
}

void CStat::Initialize(void)
{
	//Stat Data Load
	Load_Data();

	//Stat Main Object Info
	m_tInfo.fx = 509.f;
	m_tInfo.fy = 300.f;
	m_tInfo.fcx = 212.f;
	m_tInfo.fcy = 373.f;
	m_eRenderType = RENDER_UI;

	//Stat Button Object Info && Button Rect
	for (int i = 0; i < 4; ++i)
	{
		m_tButton_Info[i].fx = m_tInfo.fx + 180.f;
		m_tButton_Info[i].fy = m_tInfo.fy + 263.f + (i * 18.f);
		m_tButton_Info[i].fcx = 13.f;
		m_tButton_Info[i].fcy = 12.f;

		m_tButton_Rect[i].left = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) - m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].right = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) + m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].top = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) - m_tButton_Info[i].fcy / 2);
		m_tButton_Rect[i].bottom = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) + m_tButton_Info[i].fcy / 2);
	}

	//Stat Move Rect
	m_tStatMove_rect.left = long(m_tInfo.fx + (212.f / 2.f) - 212.f / 2);
	m_tStatMove_rect.right = long(m_tInfo.fx + (212.f / 2.f) + 212.f / 2);
	m_tStatMove_rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2);
	m_tStatMove_rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2);

	//Key Timer
	m_dwTime = GetTickCount();

	//임시로 Stat 정함
	m_tStat.m_iSTR = 4;
	m_tStat.m_iDEX = 4;
	m_tStat.m_iINT = 4;
	m_tStat.m_iLUK = 4;
	m_tStat.m_iFameValue = 1;
	m_tStat.m_iLevel = 1;
	m_tStat.m_iHonorLevel = 1;
	m_tStat.m_iExp = 0;
	m_tStat.m_iHp = 90;
	m_tStat.m_iMp = 90;
	m_tStat.m_iMaxHp = 100;
	m_tStat.m_iMaxMp = 100;
	m_tStat.m_iPopularity = 0;
	lstrcpy(m_tStat.m_szName, L"최영준");
	lstrcpy(m_tStat.m_szJop, L"해적");
	lstrcpy(m_tStat.m_szGuild, L"우주 최강");

	//Load Data
	Load_Data();
}

int CStat::Update(void)
{
	//Image & Rect Position
	for (int i = 0; i < 4; ++i)
	{
		//Button Position
		m_tButton_Info[i].fx = m_tInfo.fx + 180.f;
		m_tButton_Info[i].fy = m_tInfo.fy + 263.f + (i * 18.f);

		//Rect Position
		m_tButton_Rect[i].left = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) - m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].right = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) + m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].top = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) - m_tButton_Info[i].fcy / 2);
		m_tButton_Rect[i].bottom = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) + m_tButton_Info[i].fcy / 2);
	}

	//Stat Move Rect Position
	m_tStatMove_rect.left = long(m_tInfo.fx + (212.f / 2.f) - 212.f / 2);
	m_tStatMove_rect.right = long(m_tInfo.fx + (212.f / 2.f) + 212.f / 2);
	m_tStatMove_rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2);
	m_tStatMove_rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2);

	//Key Setting
	Stat_Key();

	//Buttongit 
	Stat_Button();

	//Stat Move
	Stat_Move();

	//Level Up Check Initialize
	if (m_iStat_Limit <= 0 && m_bLevelUp_Check == true)
		m_bLevelUp_Check = false;

	system("cls");
	cout << "Hp : " << m_tStat.m_iHp << endl;
	cout << "MaxHp : " << m_tStat.m_iMaxHp << endl;
	cout << "Mp : " << m_tStat.m_iMp << endl;
	cout << "MaxMp : " << m_tStat.m_iMaxMp << endl;

	return 0;
}

void CStat::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx), int(m_tInfo.fy),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stat")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));

		//0, 1, 2, 3 * 버튼 하나의 사이즈, y값(0)
		for (int i = 0; i < 4; ++i)
		{
			TransparentBlt(_dc,
				int(m_tButton_Info[i].fx), int(m_tButton_Info[i].fy),
				int(m_tButton_Info[i].fcx), int(m_tButton_Info[i].fcy),
				GETS(CBitMapMgr)->FindImage(L"Button_Plus")->GetMemDC(),
				int(m_iButtonOption[i] * m_tButton_Info[i].fcx), 0,
				int(m_tButton_Info[i].fcx), int(m_tButton_Info[i].fcy),
				RGB(255, 255, 255));

			/*
			Rectangle(_dc,
				m_tButton_Rect[i].left - g_fScrollX,
				m_tButton_Rect[i].top - g_fScrollY,
				m_tButton_Rect[i].right - g_fScrollX,
				m_tButton_Rect[i].bottom - g_fScrollY);
			
			Rectangle(_dc,
				m_tStatMove_rect.left - g_fScrollX,
				m_tStatMove_rect.top - g_fScrollY,
				m_tStatMove_rect.right - g_fScrollX,
				m_tStatMove_rect.bottom - g_fScrollY);
			*/
		}		

		Stat_Poisiton(m_tStat, _dc);
	}	
}

void CStat::Release(void)
{
	DeleteObject(m_myFont);
}

void CStat::Stat_Key(void)
{
	static bool bIsPress_Stat = false;
	if (GETS(CKeyMgr)->OnceKeyDown('S') && bIsPress_Stat == false)
	{
		if (m_bVisible == true)
			m_bVisible = false;
		else
			m_bVisible = true;
		
		bIsPress_Stat = true;
	}

	if (m_dwTime + 200 < GetTickCount())
	{
		m_dwTime = GetTickCount();

		if (bIsPress_Stat == true)
			bIsPress_Stat = false;
	}	

	//Level Up System(임시) : 나중에 경험치가 오르면 Level이 오르는 식으로 바꾸어야 한다.
	static int iLevel = 0;
	
	if (iLevel > 0 && m_iStat_Limit <= 0)
	{
		iLevel = 0;

		//임시로 Save를 여기서 한다.
		Save_Data();
	}

	static bool bIsPress_Level = false;
	if (GETS(CKeyMgr)->OnceKeyDown('7') && bIsPress_Level == false)
	{
		++iLevel;

		m_tStat.m_iLevel += iLevel;
		m_tStat.m_iSkillPoint = 10;
		m_iStat_Limit = iLevel * 4;

		bIsPress_Level = true;
	}
	else if (!GETS(CKeyMgr)->OnceKeyDown('7') && bIsPress_Level == true)
		bIsPress_Level = false;
}

void CStat::Stat_Poisiton(STAT& _rStat, HDC _dc)
{
	//Stat 글자의 포지션을 정하는 함수.	
	m_myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"굴림");
	HFONT oldFont = (HFONT)SelectObject(_dc, m_myFont);

	//STR & DEX & INT & LUK
	TCHAR szSTR[100] = { 0 }; TCHAR szDEX[100] = { 0 }; TCHAR szINT[100] = { 0 }; TCHAR szLUK[100] = { 0 };
	//FrameValue & Level & HonorLevel & Exp & Hp & Mp & Popularity
	TCHAR szFrmaeValue[100] = { 0 }; TCHAR szHonorLevel[100] = { 0 }; TCHAR szExp[100] = { 0 }; 
	TCHAR szHp[100] = { 0 }; TCHAR szMp[100] = { 0 }; TCHAR szPopularity[100] = { 0 };
	TCHAR szLevel[100] = { 0 };

	_stprintf_s(szSTR, _countof(szSTR), L"%d", _rStat.m_iSTR);
	_stprintf_s(szDEX, _countof(szDEX), L"%d", _rStat.m_iDEX);
	_stprintf_s(szINT, _countof(szINT), L"%d", _rStat.m_iINT);
	_stprintf_s(szLUK, _countof(szLUK), L"%d", _rStat.m_iLUK);
	_stprintf_s(szFrmaeValue, _countof(szFrmaeValue), L"%d", _rStat.m_iFameValue);
	_stprintf_s(szHonorLevel, _countof(szHonorLevel), L"%d", _rStat.m_iHonorLevel);
	_stprintf_s(szExp, _countof(szExp), L"%d", _rStat.m_iExp);
	_stprintf_s(szHp, _countof(szHp), L"%d", _rStat.m_iHp);
	_stprintf_s(szMp, _countof(szMp), L"%d", _rStat.m_iMp);
	_stprintf_s(szPopularity, _countof(szPopularity), L"%d", _rStat.m_iPopularity);
	_stprintf_s(szLevel, _countof(szLevel), L"%d", _rStat.m_iLevel);
	
	SetBkMode(_dc, TRANSPARENT);
	//STR & DEX & INT & LUK
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 264.f), szSTR, lstrlen(szSTR));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 282.f), szDEX, lstrlen(szDEX));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 300.f), szINT, lstrlen(szINT));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 318.f), szLUK, lstrlen(szLUK));

	//FrameValue & Level & HonorLevel & Exp & Hp & Mp & Popularity & Gulid & Name & Jop
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 32.f), _rStat.m_szName, lstrlen(_rStat.m_szName));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 50.f), _rStat.m_szJop, lstrlen(_rStat.m_szJop));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 68.f), szLevel, lstrlen(szLevel));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 86.f), szExp, lstrlen(szExp));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 104.f), szHonorLevel, lstrlen(szHonorLevel));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 122.f), szFrmaeValue, lstrlen(szFrmaeValue));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 140.f), _rStat.m_szGuild, lstrlen(_rStat.m_szGuild));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 158.f), szHp, lstrlen(szHp));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 176.f), szMp, lstrlen(szMp));
	TextOut(_dc, int(m_tInfo.fx + 75.f), int(m_tInfo.fy + 194.f), szPopularity, lstrlen(szPopularity));

	SelectObject(_dc, oldFont);
}

void CStat::Stat_Button(void)
{
	//Level Up
	if (m_iStat_Limit > 0)
	{
		m_bLevelUp_Check = true;

		for (int i = 0; i < 4; ++i)
		{
			m_iButtonOption[i] = 1;
		}
	}
	else if (m_iStat_Limit <= 0)
	{
		for (int i = 0; i < 4; ++i)
		{
			//Button Off
			m_iButtonOption[i] = 0;
		}
	}

	//0, 1, 2, 3 * 버튼 하나의 사이즈, y값(0)
	if (m_bLevelUp_Check == true && m_bVisible == true)
	{
		POINT pt;
		pt = CMouse::GetPos();

		static bool bIsPress_Click = false;
		if (PtInRect(&m_tButton_Rect[0], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bIsPress_Click == false)
		{
			//STR
			--m_iStat_Limit;
			++m_tStat.m_iSTR;

			bIsPress_Click = true;
		}
		else if (PtInRect(&m_tButton_Rect[1], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bIsPress_Click == false)
		{
			//Dex
			--m_iStat_Limit;
			++m_tStat.m_iDEX;

			bIsPress_Click = true;
		}
		else if (PtInRect(&m_tButton_Rect[2], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bIsPress_Click == false)
		{
			//INT
			--m_iStat_Limit;
			++m_tStat.m_iINT;

			bIsPress_Click = true;
		}
		else if (PtInRect(&m_tButton_Rect[3], pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && bIsPress_Click == false)
		{
			//LUK
			--m_iStat_Limit;
			++m_tStat.m_iLUK;

			bIsPress_Click = true;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (PtInRect(&m_tButton_Rect[i], pt) == false && bIsPress_Click == true)
			{
				bIsPress_Click = false;
			}
		}		
	}	
}

void CStat::Stat_Move(void)
{
	//Stat창을 마우스로 움직이게 만드는 함수.
	static bool bMove = false;
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tStatMove_rect, pt) && GETS(CKeyMgr)->GetKeyState(VK_LBUTTON))
	{
		bMove = true;
	}

	if (!GETS(CKeyMgr)->GetKeyState(VK_LBUTTON) && bMove == true)
	{
		bMove = false;				
	}

	if (bMove == true)
	{
		m_tInfo.fx = (pt.x - m_tInfo.fcx / 2.f);
		m_tInfo.fy = (pt.y - 10.f);

		//Rect Position
		for (int i = 0; i < 4; ++i)
		{
			//Button Position
			m_tButton_Info[i].fx = m_tInfo.fx + 180.f;
			m_tButton_Info[i].fy = m_tInfo.fy + 263.f + (i * 18.f);

			//Rect Position
			m_tButton_Rect[i].left = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) - m_tButton_Info[i].fcx / 2);
			m_tButton_Rect[i].right = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) + m_tButton_Info[i].fcx / 2);
			m_tButton_Rect[i].top = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) - m_tButton_Info[i].fcy / 2);
			m_tButton_Rect[i].bottom = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) + m_tButton_Info[i].fcy / 2);
		}

		//Stat Move Rect Position
		m_tStatMove_rect.left = long(m_tInfo.fx + (212.f / 2.f) - 212.f / 2);
		m_tStatMove_rect.right = long(m_tInfo.fx + (212.f / 2.f) + 212.f / 2);
		m_tStatMove_rect.top = long(m_tInfo.fy + (20.f / 2.f) - 20.f / 2);
		m_tStatMove_rect.bottom = long(m_tInfo.fy + (20.f / 2.f) + 20.f / 2);
	}
}

void CStat::Save_Data(void)
{
	//File 화된 플레이어 Stat 정보를 저장하는 함수. 
	//저장이 시작되는 시점은 게임이 종료 되거나, 스테이지가 넘어갈때 저장되는 식으로 바꿔야됨.
	//지금은 임시적으로 스텟을 다 찍을때 저장되는 식으로 함.
	
	DWORD dwByte;
	HANDLE hFile = CreateFile(L"../Data/Player_Stat.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(hFile, &m_tStat, sizeof(STAT), &dwByte, NULL);

	CloseHandle(hFile);
}

void CStat::Load_Data(void)
{
	//File 화된 플레이어 Stat 정보를 가져오는 함수.
	ZeroMemory(&m_tStat, sizeof(STAT));

	DWORD dwByte;
	HANDLE hFile = CreateFile(L"../Data/Player_Stat.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	while (true)
	{
		ReadFile(hFile, &m_tStat, sizeof(STAT), &dwByte, NULL);

		if (m_tStat.m_iLevel == 0)
		{
			//임시로 넣어줌.
			m_tStat.m_iSTR = 4;
			m_tStat.m_iDEX = 4;
			m_tStat.m_iINT = 4;
			m_tStat.m_iLUK = 4;
			m_tStat.m_iFameValue = 1;
			m_tStat.m_iLevel = 1;
			m_tStat.m_iHonorLevel = 1;
			m_tStat.m_iExp = 0;
			m_tStat.m_iHp = 100;
			m_tStat.m_iMaxHp = 100;
			m_tStat.m_iMp = 100;
			m_tStat.m_iMaxMp = 100;
			m_tStat.m_iPopularity = 0;
			lstrcpy(m_tStat.m_szName, L"최영준");
			lstrcpy(m_tStat.m_szJop, L"해적");
			lstrcpy(m_tStat.m_szGuild, L"우주 최강");
		}

		if (dwByte == 0)
			break;
	}

	CloseHandle(hFile);
}
