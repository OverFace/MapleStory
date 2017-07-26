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
	
	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&m_tButton_Info[i], sizeof(INFO));
		ZeroMemory(&m_tButton_Rect[i], sizeof(RECT));
		m_iButtonOption[i] = 0;
	}
}

CStat::~CStat(void)
{
	Release();
}

void CStat::Initialize(void)
{
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
	m_tStat.m_iHp = 100;
	m_tStat.m_iMp = 100;
	m_tStat.m_iPopularity = 0;
	lstrcpy(m_tStat.m_szName, L"최영준");
	lstrcpy(m_tStat.m_szJop, L"해적");
	lstrcpy(m_tStat.m_szGuild, L"우주 최강");

	//Load Data
	Load_Data();
}

int CStat::Update(void)
{
	//Position
	m_tInfo.fx = 509.f + g_fScrollX;
	m_tInfo.fy = 300.f + g_fScrollY;

	for (int i = 0; i < 4; ++i)
	{
		//Button Position
		m_tButton_Info[i].fx = m_tInfo.fx + 180.f;
		m_tButton_Info[i].fy = m_tInfo.fy + 263.f + (i * 18.f);
		m_tButton_Info[i].fcx = 13.f;
		m_tButton_Info[i].fcy = 12.f;

		//Rect Position
		m_tButton_Rect[i].left = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) - m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].right = long(m_tButton_Info[i].fx + (m_tButton_Info[i].fcx / 2.f) + m_tButton_Info[i].fcx / 2);
		m_tButton_Rect[i].top = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) - m_tButton_Info[i].fcy / 2);
		m_tButton_Rect[i].bottom = long(m_tButton_Info[i].fy + (m_tButton_Info[i].fcy / 2.f) + m_tButton_Info[i].fcy / 2);
	}

	//Key Setting
	Stat_Key();

	//Button
	Stat_Button();

	return 0;
}

void CStat::Render(HDC _dc)
{
	if (m_bVisible == true)
	{
		TransparentBlt(_dc,
			int(m_tInfo.fx) - g_fScrollX, int(m_tInfo.fy) - g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stat")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 0));

		//0, 1, 2, 3 * 버튼 하나의 사이즈, y값(0)
		for (int i = 0; i < 4; ++i)
		{
			TransparentBlt(_dc,
				int(m_tButton_Info[i].fx) - g_fScrollX, int(m_tButton_Info[i].fy) - g_fScrollY,
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
	if (GETS(CKeyMgr)->GetKeyDown('S') && bIsPress_Stat == false)
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
}

void CStat::Stat_Poisiton(STAT& _rStat, HDC _dc)
{
	//Stat 글자의 포지션을 정하는 함수.
	/*
	m_tStat.m_iFameValue = 1;
	m_tStat.m_iLevel = 1;
	m_tStat.m_iHonorLevel = 1;
	m_tStat.m_iExp = 0;
	m_tStat.m_iHp = 100;
	m_tStat.m_iMp = 100;
	m_tStat.m_iPopularity = 0;
	lstrcpy(m_tStat.m_szName, L"최영준");
	lstrcpy(m_tStat.m_szJop, L"해적");
	lstrcpy(m_tStat.m_szGuild, L"우주 최강");
	*/
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
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 264.f) - g_fScrollY, szSTR, lstrlen(szSTR));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 282.f) - g_fScrollY, szDEX, lstrlen(szDEX));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 300.f) - g_fScrollY, szINT, lstrlen(szINT));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 318.f) - g_fScrollY, szLUK, lstrlen(szLUK));

	//FrameValue & Level & HonorLevel & Exp & Hp & Mp & Popularity & Gulid & Name & Jop
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 32.f) - g_fScrollY, _rStat.m_szName, lstrlen(_rStat.m_szName));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 50.f) - g_fScrollY, _rStat.m_szJop, lstrlen(_rStat.m_szJop));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 68.f) - g_fScrollY, szLevel, lstrlen(szLevel));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 86.f) - g_fScrollY, szExp, lstrlen(szExp));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 104.f) - g_fScrollY, szHonorLevel, lstrlen(szHonorLevel));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 122.f) - g_fScrollY, szFrmaeValue, lstrlen(szFrmaeValue));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 140.f) - g_fScrollY, _rStat.m_szGuild, lstrlen(_rStat.m_szGuild));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 158.f) - g_fScrollY, szHp, lstrlen(szHp));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 176.f) - g_fScrollY, szMp, lstrlen(szMp));
	TextOut(_dc, int(m_tInfo.fx + 75.f) - g_fScrollX, int(m_tInfo.fy + 194.f) - g_fScrollY, szPopularity, lstrlen(szPopularity));

	SelectObject(_dc, oldFont);
}

void CStat::Stat_Button(void)
{
	//0, 1, 2, 3 * 버튼 하나의 사이즈, y값(0)
	POINT pt;
	pt = CMouse::GetPos();

	for (int i = 0; i < 4; ++i)
	{
		static bool bIsPress_Click = false;
		if (PtInRect(&m_tButton_Rect[i], pt)
			&& GETS(CKeyMgr)->GetKeyDown(VK_LBUTTON)
			&& bIsPress_Click == false)
		{
			bIsPress_Click = true;
			
			//Picking / (미완성)
			//0(꺼짐) 1(올리기)
			//0 은 평소 상태
			//1 은 Level 올랐을때. (총4번)
			++m_iButtonOption[i];
			
			if (m_iButtonOption[i] > 1)
				m_iButtonOption[i] = 0;
		}
		if (PtInRect(&m_tButton_Rect[i], pt) == false
			&& bIsPress_Click == true)
		{
			bIsPress_Click = false;
		}
	}
}

void CStat::Load_Data(void)
{
	//File 화된 플레이어 Stat 정보를 가져오는 함수.
}
