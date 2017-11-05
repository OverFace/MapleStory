#include "stdafx.h"
#include "LineTool.h"
#include "BitMap.h"
#include "BitMapMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

//Background
#include "Stage1_Back.h"
#include "Stage1_Map.h"
#include "Stage2_Map.h"
#include "Stage3_Map.h"
#include "BStage_Back.h"
#include "BStage_Map.h"

typedef list<LINE*>::iterator LINEITER;

CLine_Tool::CLine_Tool(void)
{
	m_fScrollSpeed = 10.f;
	m_iChangeCount = 0;

	for (int i = 0; i < 4; ++i)
		m_bStageCheck[i] = false;
	m_bLineCreate_Check = false;
	m_bLineClick_Check = false;
	m_bLineReStart_Check = false;

	m_pStage1_Back = NULL;
	m_pStage1_Map = NULL;
	m_pStage2_Map = NULL;
	m_pStage3_Map = NULL;
	m_pBStage_Back = NULL;
	m_pBStage_Map = NULL;

	ZeroMemory(&m_tLine_StartPoint, sizeof(LINEPOINT));
}

CLine_Tool::~CLine_Tool(void)
{
	Release();
}

void CLine_Tool::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_EDIT_LINE);

	//Stage1 Background & Map Object Create
	m_pStage1_Back = new CStage1_Back();
	m_pStage1_Back->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pStage1_Back);
	m_pStage1_Map = new CStage1_Map(true);
	m_pStage1_Map->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pStage1_Map);

	//Stage1 Render On
	((CStage1_Back*)(m_pStage1_Back))->SetRedner(true);
	((CStage1_Map*)(m_pStage1_Map))->SetRedner(true);

	//Stage2 Map Object Create
	m_pStage2_Map = new CStage2_Map(true);
	m_pStage2_Map->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pStage2_Map);

	//Stage3 Map Object Create
	m_pStage3_Map = new CStage3_Map(true);
	m_pStage3_Map->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pStage3_Map);

	//Boss Stage Map & Background Create
	m_pBStage_Back = new CBstage_Back();
	m_pBStage_Back->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pBStage_Back);

	m_pBStage_Map = new CBstage_Map(true);
	m_pBStage_Map->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pBStage_Map);
}

int CLine_Tool::Update(void)
{
	//Obj Mgr Update
	GETS(CObjMgr)->Update();

	//Scroll Setting
	if (GETS(CKeyMgr)->GetKeyState(VK_LEFT))
	{
		g_fScrollX += m_fScrollSpeed;
	}
	if (GETS(CKeyMgr)->GetKeyState(VK_RIGHT))
	{
		g_fScrollX -= m_fScrollSpeed;
	}
	if (GETS(CKeyMgr)->GetKeyState(VK_UP))
	{
		g_fScrollY += m_fScrollSpeed;
	}
	if (GETS(CKeyMgr)->GetKeyState(VK_DOWN))
	{
		g_fScrollY -= m_fScrollSpeed;
	}

	//Short Cut Key & Scene Change
	ShortCut_Key();
	Scene_Change();

	//Line
	Create_Line();

	return 0;
}

void CLine_Tool::Render(HDC _dc)
{
	//Obj Mgr Render
	GETS(CObjMgr)->Render(_dc);

	//Line Render
	LINEPOINT tMousePos;
	tMousePos.fx = (float)CMouse::GetPos().x;
	tMousePos.fy = (float)CMouse::GetPos().y;

	HPEN old_pen;
	m_Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	old_pen = (HPEN)SelectObject(_dc, m_Pen);

	if (m_bStageCheck[0] == true)
	{
		//Stage 1
		if (m_bLineCreate_Check == true)
		{
			if (m_LineList_Stage1.size() <= 0)
			{
				MoveToEx(_dc, int(m_tLine_StartPoint.fx), int(m_tLine_StartPoint.fy), NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
			else
			{
				MoveToEx(_dc, (int)(m_LineList_Stage1.back()->tRight_Point.fx + g_fScrollX), (int)m_LineList_Stage1.back()->tRight_Point.fy, NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
		}

		if (m_LineList_Stage1.size() != 0)
		{
			MoveToEx(_dc, int(m_LineList_Stage1.front()->tLeft_Point.fx), int(m_LineList_Stage1.front()->tLeft_Point.fy), NULL);

			LINEITER iter = m_LineList_Stage1.begin();
			LINEITER iter_End = m_LineList_Stage1.end();
			for (iter; iter != iter_End; ++iter)
			{
				LineTo(_dc, int((*iter)->tRight_Point.fx + g_fScrollX), int((*iter)->tRight_Point.fy));
			}
		}
	}
	else if (m_bStageCheck[1] == true)
	{
		//Stage 2
	}
	else if (m_bStageCheck[2] == true)
	{
		//Stage 3
	}
	else if (m_bStageCheck[3] == true)
	{
		//Boss Stage
	}

	SelectObject(_dc, old_pen);
}

void CLine_Tool::Release(void)
{
	LINEITER iter_Stage1 = m_LineList_Stage1.begin();
	LINEITER iter_Stage1_End = m_LineList_Stage1.end();
	for (iter_Stage1; iter_Stage1 != iter_Stage1_End; ++iter_Stage1)
		SAFE_DELETE(*iter_Stage1);

	LINEITER iter_Stage2 = m_LineList_Stage2.begin();
	LINEITER iter_Stage2_End = m_LineList_Stage2.end();
	for (iter_Stage2; iter_Stage2 != iter_Stage2_End; ++iter_Stage2)
		SAFE_DELETE(*iter_Stage2);

	LINEITER iter_Stage3 = m_LineList_Stage3.begin();
	LINEITER iter_Stage3_End = m_LineList_Stage3.end();
	for (iter_Stage3; iter_Stage3 != iter_Stage3_End; ++iter_Stage3)
		SAFE_DELETE(*iter_Stage3);

	LINEITER iter_Boss = m_LineList_BossStage.begin();
	LINEITER iter_Boss_End = m_LineList_BossStage.end();
	for (iter_Boss; iter_Boss != iter_Boss_End; ++iter_Boss)
		SAFE_DELETE(*iter_Boss);

	DeleteObject(m_Pen);
}

#pragma region Function
void CLine_Tool::ShortCut_Key(void)
{
#pragma region Scene Chage Key
	if (GETS(CKeyMgr)->OnceKeyDown('1'))
	{
		m_iChangeCount = 0;

		g_fScrollX = 0;
		g_fScrollY = 0;

		((CStage1_Back*)(m_pStage1_Back))->SetRedner(true);
		((CStage1_Map*)(m_pStage1_Map))->SetRedner(true);
		((CStage2_Map*)(m_pStage2_Map))->SetRedner(false);
		((CStage3_Map*)(m_pStage3_Map))->SetRedner(false);
		((CBstage_Back*)(m_pBStage_Back))->SetRedner(false);
		((CBstage_Map*)(m_pBStage_Map))->SetRedner(false);
		m_bLineClick_Check = false;
		m_bLineCreate_Check = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown('2'))
	{
		m_iChangeCount = 1;

		g_fScrollX = 0;
		g_fScrollY = 0;

		((CStage1_Back*)(m_pStage1_Back))->SetRedner(false);
		((CStage1_Map*)(m_pStage1_Map))->SetRedner(false);
		((CStage2_Map*)(m_pStage2_Map))->SetRedner(true);
		((CStage3_Map*)(m_pStage3_Map))->SetRedner(false);
		((CBstage_Back*)(m_pBStage_Back))->SetRedner(false);
		((CBstage_Map*)(m_pBStage_Map))->SetRedner(false);
		m_bLineClick_Check = false;
		m_bLineCreate_Check = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown('3'))
	{
		m_iChangeCount = 2;

		g_fScrollX = 0;
		g_fScrollY = 0;

		((CStage1_Back*)(m_pStage1_Back))->SetRedner(false);
		((CStage1_Map*)(m_pStage1_Map))->SetRedner(false);
		((CStage2_Map*)(m_pStage2_Map))->SetRedner(false);
		((CStage3_Map*)(m_pStage3_Map))->SetRedner(true);
		((CBstage_Back*)(m_pBStage_Back))->SetRedner(false);
		((CBstage_Map*)(m_pBStage_Map))->SetRedner(false);
		m_bLineClick_Check = false;
		m_bLineCreate_Check = false;
	}

	if (GETS(CKeyMgr)->OnceKeyDown('4'))
	{
		m_iChangeCount = 3;

		g_fScrollX = 0;
		g_fScrollY = 0;

		((CStage1_Back*)(m_pStage1_Back))->SetRedner(false);
		((CStage1_Map*)(m_pStage1_Map))->SetRedner(false);
		((CStage2_Map*)(m_pStage2_Map))->SetRedner(false);
		((CStage3_Map*)(m_pStage3_Map))->SetRedner(false);
		((CBstage_Back*)(m_pBStage_Back))->SetRedner(true);
		((CBstage_Map*)(m_pBStage_Map))->SetRedner(true);
		m_bLineClick_Check = false;
		m_bLineCreate_Check = false;
	}
#pragma endregion
#pragma region Line Create Key
	if (GETS(CKeyMgr)->OnceKeyDown('S'))
	{
		//Line Create Start
		m_tLine_StartPoint.fx = (float)CMouse::GetPos().x;
		m_tLine_StartPoint.fy = (float)CMouse::GetPos().y;

		m_bLineCreate_Check = true;
	}
	if (GETS(CKeyMgr)->StayKeyDown('D'))
	{
		m_bLineCreate_Check = false;
		m_bLineReStart_Check = true;
	}

	system("cls");
	cout << m_bLineCreate_Check << endl;

#pragma endregion
#pragma region Save & Load Key
	if (GETS(CKeyMgr)->OnceKeyDown('5'))
	{
		Save_Data();
	}
	else if (GETS(CKeyMgr)->OnceKeyDown('6'))
	{
		//Load Data
		Load_Data();
	}
#pragma endregion
}

void CLine_Tool::Scene_Change(void)
{
	switch (m_iChangeCount)
	{
	case 0:	//Stage1
		m_bStageCheck[0] = true;
		m_bStageCheck[1] = false;
		m_bStageCheck[2] = false;
		m_bStageCheck[3] = false;
		break;
	case 1:	//Stage2
		m_bStageCheck[0] = false;
		m_bStageCheck[1] = true;
		m_bStageCheck[2] = false;
		m_bStageCheck[3] = false;
		break;
	case 2: //Stage3
		m_bStageCheck[0] = false;
		m_bStageCheck[1] = false;
		m_bStageCheck[2] = true;
		m_bStageCheck[3] = false;
		break;
	case 3: //Boss Stage
		m_bStageCheck[0] = false;
		m_bStageCheck[1] = false;
		m_bStageCheck[2] = false;
		m_bStageCheck[3] = true;
		break;
	}
}

void CLine_Tool::Save_Data(void)
{
	if (m_bStageCheck[0] == true)
	{
		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage1.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		LINEITER iter = m_LineList_Stage1.begin();
		LINEITER iter_End = m_LineList_Stage1.end();
		for (iter; iter != iter_End; ++iter)
		{
			WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[1] == true)
	{
		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage2.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		LINEITER iter = m_LineList_Stage2.begin();
		LINEITER iter_End = m_LineList_Stage2.end();
		for (iter; iter != iter_End; ++iter)
		{
			WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[2] == true)
	{
		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage3.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		LINEITER iter = m_LineList_Stage3.begin();
		LINEITER iter_End = m_LineList_Stage3.end();
		for (iter; iter != iter_End; ++iter)
		{
			WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[3] == true)
	{
		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Boss.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		LINEITER iter = m_LineList_BossStage.begin();
		LINEITER iter_End = m_LineList_BossStage.end();
		for (iter; iter != iter_End; ++iter)
		{
			WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
		}

		CloseHandle(hFile);
	}
}

void CLine_Tool::Load_Data(void)
{
	if (m_bStageCheck[0] == true)
	{
		LINEITER iter = m_LineList_Stage1.begin();
		LINEITER iter_End = m_LineList_Stage1.end();
		if (m_LineList_Stage1.size() > 0)
		{
			for (iter; iter != iter_End; ++iter)
			{
				SAFE_DELETE(*iter);
			}
			m_LineList_Stage1.clear();
		}

		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage1.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		while (true)
		{
			LINE* pLine = new LINE;
			ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

			if (dwByte == 0)
			{
				SAFE_DELETE(pLine);
				break;
			}

			m_LineList_Stage1.push_back(pLine);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[1] == true)
	{
		LINEITER iter = m_LineList_Stage2.begin();
		LINEITER iter_End = m_LineList_Stage2.end();
		if (m_LineList_Stage2.size() > 0)
		{
			for (iter; iter != iter_End; ++iter)
			{
				SAFE_DELETE(*iter);
			}
			m_LineList_Stage2.clear();
		}

		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage2.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		while (true)
		{
			LINE* pLine = new LINE;
			ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

			if (dwByte == 0)
			{
				SAFE_DELETE(pLine);
				break;
			}

			m_LineList_Stage2.push_back(pLine);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[2] == true)
	{
		LINEITER iter = m_LineList_Stage3.begin();
		LINEITER iter_End = m_LineList_Stage3.end();
		if (m_LineList_Stage3.size() > 0)
		{
			for (iter; iter != iter_End; ++iter)
			{
				SAFE_DELETE(*iter);
			}
			m_LineList_Stage3.clear();
		}

		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Stage3.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		while (true)
		{
			LINE* pLine = new LINE;
			ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

			if (dwByte == 0)
			{
				SAFE_DELETE(pLine);
				break;
			}

			m_LineList_Stage3.push_back(pLine);
		}

		CloseHandle(hFile);
	}
	else if (m_bStageCheck[3] == true)
	{
		LINEITER iter = m_LineList_BossStage.begin();
		LINEITER iter_End = m_LineList_BossStage.end();
		if (m_LineList_BossStage.size() > 0)
		{
			for (iter; iter != iter_End; ++iter)
			{
				SAFE_DELETE(*iter);
			}
			m_LineList_BossStage.clear();
		}

		DWORD dwByte;
		HANDLE hFile = CreateFile(L"../Data/Line_Boss.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		while (true)
		{
			LINE* pLine = new LINE;
			ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

			if (dwByte == 0)
			{
				SAFE_DELETE(pLine);
				break;
			}

			m_LineList_BossStage.push_back(pLine);
		}

		CloseHandle(hFile);
	}
}
#pragma endregion

#pragma region Line
void CLine_Tool::Create_Line(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	LINEPOINT tMousePos;
	tMousePos.fx = (float)pt.x - g_fScrollX;
	tMousePos.fy = (float)pt.y;

	if (m_bStageCheck[0] == true)
	{
		//Stage1
		if (m_bLineCreate_Check == true)
		{
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				if (m_LineList_Stage1.size() <= 0)
					m_LineList_Stage1.push_back(new LINE(m_tLine_StartPoint, tMousePos));
				else
				{
					m_tLine_ReStart_Point.fx = (float)CMouse::GetPos().x;
					m_tLine_ReStart_Point.fy = (float)CMouse::GetPos().y;

					if(m_bLineReStart_Check == false)
						m_LineList_Stage1.push_back(new LINE(m_LineList_Stage1.back()->tRight_Point, tMousePos));
					else if (m_bLineReStart_Check == true)
						m_LineList_Stage1.push_back(new LINE(m_tLine_ReStart_Point, tMousePos));
				}
			}
		}
	}
	else if (m_bStageCheck[1] == true)
	{
		//Stage2
	}
	else if (m_bStageCheck[2] == true)
	{
		//Stage3
	}
	else if (m_bStageCheck[3] == true)
	{
		//Boss Stage
	}
}
#pragma endregion