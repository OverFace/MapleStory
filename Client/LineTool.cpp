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
	m_bLineBlank_Check = false;

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
	Display_CutDownKey_Redner(_dc);

	//Line Render
	LINEPOINT tMousePos;
	tMousePos.fx = (float)CMouse::GetPos().x;
	tMousePos.fy = (float)CMouse::GetPos().y;

	HPEN old_pen;
	m_Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	old_pen = (HPEN)SelectObject(_dc, m_Pen);

#pragma region Render Stage Line
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
				if ((*iter)->tLeft_Point.fx == 0 && (*iter)->tLeft_Point.fy == 0)
					continue;
				if ((*iter)->tRight_Point.fx == 0 && (*iter)->tRight_Point.fy == 0)
					continue;

				MoveToEx(_dc, int((*iter)->tLeft_Point.fx), int((*iter)->tLeft_Point.fy), NULL);
				LineTo(_dc, int((*iter)->tRight_Point.fx + g_fScrollX), int((*iter)->tRight_Point.fy));
			}
		}
	}
	else if (m_bStageCheck[1] == true)
	{
		//Stage 2
		if (m_bLineCreate_Check == true)
		{
			if (m_LineList_Stage2.size() <= 0)
			{
				MoveToEx(_dc, int(m_tLine_StartPoint.fx), int(m_tLine_StartPoint.fy), NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
			else
			{
				MoveToEx(_dc, (int)(m_LineList_Stage2.back()->tRight_Point.fx + g_fScrollX), (int)m_LineList_Stage2.back()->tRight_Point.fy, NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
		}

		if (m_LineList_Stage2.size() != 0)
		{
			MoveToEx(_dc, int(m_LineList_Stage2.front()->tLeft_Point.fx), int(m_LineList_Stage2.front()->tLeft_Point.fy), NULL);

			LINEITER iter = m_LineList_Stage2.begin();
			LINEITER iter_End = m_LineList_Stage2.end();
			for (iter; iter != iter_End; ++iter)
			{
				if ((*iter)->tLeft_Point.fx == 0 && (*iter)->tLeft_Point.fy == 0)
					continue;
				if ((*iter)->tRight_Point.fx == 0 && (*iter)->tRight_Point.fy == 0)
					continue;

				MoveToEx(_dc, int((*iter)->tLeft_Point.fx), int((*iter)->tLeft_Point.fy), NULL);
				LineTo(_dc, int((*iter)->tRight_Point.fx + g_fScrollX), int((*iter)->tRight_Point.fy));
			}
		}
	}
	else if (m_bStageCheck[2] == true)
	{
		//Stage 3
		if (m_bLineCreate_Check == true)
		{
			if (m_LineList_Stage3.size() <= 0)
			{
				MoveToEx(_dc, int(m_tLine_StartPoint.fx), int(m_tLine_StartPoint.fy), NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
			else
			{
				MoveToEx(_dc, (int)(m_LineList_Stage3.back()->tRight_Point.fx + g_fScrollX), (int)m_LineList_Stage3.back()->tRight_Point.fy, NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
		}

		if (m_LineList_Stage2.size() != 0)
		{
			MoveToEx(_dc, int(m_LineList_Stage3.front()->tLeft_Point.fx), int(m_LineList_Stage3.front()->tLeft_Point.fy), NULL);

			LINEITER iter = m_LineList_Stage3.begin();
			LINEITER iter_End = m_LineList_Stage3.end();
			for (iter; iter != iter_End; ++iter)
			{
				if ((*iter)->tLeft_Point.fx == 0 && (*iter)->tLeft_Point.fy == 0)
					continue;
				if ((*iter)->tRight_Point.fx == 0 && (*iter)->tRight_Point.fy == 0)
					continue;

				MoveToEx(_dc, int((*iter)->tLeft_Point.fx), int((*iter)->tLeft_Point.fy), NULL);
				LineTo(_dc, int((*iter)->tRight_Point.fx + g_fScrollX), int((*iter)->tRight_Point.fy));
			}
		}
	}
	else if (m_bStageCheck[3] == true)
	{
		//Boss Stage
		if (m_bLineCreate_Check == true)
		{
			if (m_LineList_BossStage.size() <= 0)
			{
				MoveToEx(_dc, int(m_tLine_StartPoint.fx), int(m_tLine_StartPoint.fy), NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
			else
			{
				MoveToEx(_dc, (int)(m_LineList_BossStage.back()->tRight_Point.fx + g_fScrollX), (int)m_LineList_BossStage.back()->tRight_Point.fy, NULL);
				LineTo(_dc, int(tMousePos.fx), int(tMousePos.fy));
			}
		}

		if (m_LineList_BossStage.size() != 0)
		{
			MoveToEx(_dc, int(m_LineList_BossStage.front()->tLeft_Point.fx), int(m_LineList_BossStage.front()->tLeft_Point.fy), NULL);

			LINEITER iter = m_LineList_BossStage.begin();
			LINEITER iter_End = m_LineList_BossStage.end();
			for (iter; iter != iter_End; ++iter)
			{
				if ((*iter)->tLeft_Point.fx == 0 && (*iter)->tLeft_Point.fy == 0)
					continue;
				if ((*iter)->tRight_Point.fx == 0 && (*iter)->tRight_Point.fy == 0)
					continue;

				MoveToEx(_dc, int((*iter)->tLeft_Point.fx), int((*iter)->tLeft_Point.fy), NULL);
				LineTo(_dc, int((*iter)->tRight_Point.fx + g_fScrollX), int((*iter)->tRight_Point.fy));
			}
		}
	}
#pragma endregion
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
	//Line 시작 키
	if (GETS(CKeyMgr)->OnceKeyDown('S') && m_bLineReStart_Check == false)
	{
		//Line Create Start
		m_tLine_StartPoint.fx = (float)CMouse::GetPos().x;
		m_tLine_StartPoint.fy = (float)CMouse::GetPos().y;

		m_bLineCreate_Check = true;
	}
	
	//Line 끊어주는 키.
	if (GETS(CKeyMgr)->StayKeyDown('D'))
	{
		if (m_bLineBlank_Check == false)
		{
			//Start Point 0으로 초기화
			ZeroMemory(&m_tLine_StartPoint, sizeof(m_tLine_StartPoint));

			//0으로 초기화 된 값을 넣어준다.
			m_LineList_Stage1.push_back(new LINE(m_tLine_StartPoint, m_tLine_StartPoint));
			m_bLineBlank_Check = true;
		}

		if (GETS(CKeyMgr)->OnceKeyDown('R'))
		{
			//다시 시작할 포인트 받기.
			m_tLine_StartPoint.fx = float(CMouse::GetPos().x);
			m_tLine_StartPoint.fy = float(CMouse::GetPos().y);
		}
	
		m_bLineReStart_Check = true;
	}
	else if (!GETS(CKeyMgr)->StayKeyDown('D'))
	{
		m_bLineBlank_Check = false;
		m_bLineReStart_Check = false;
	}

	//이전의 Line 삭제 해주는 키.
	if (GETS(CKeyMgr)->OnceKeyDown('C'))
	{
		Delete_Line();
	}
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
	/*
	S키 누를 시에 StartPoint가 찍히고 그다음 마우스 클릭시
	그다음 Point가 찍힌다.

	D키 누를 시에 선을 끊고 그 다음 번째에서 시작하게 해야된다.
	그러기 위해서 중간에 NULL 값을 넣어서 한번 선을 끊기게 만들자.
	*/

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
				{
					//LineList의 Size가 0일때 경우
					m_LineList_Stage1.push_back(new LINE(m_tLine_StartPoint, tMousePos));
				}
				else
				{
					//LineList의 Size가 0이 아닐 경우
					//선을 계속해서 이어 갈 때.
					if (m_bLineReStart_Check == true)
						m_LineList_Stage1.push_back(new LINE(m_tLine_StartPoint, tMousePos));
					else
						m_LineList_Stage1.push_back(new LINE(m_LineList_Stage1.back()->tRight_Point, tMousePos));
				}
			}
		}
	}
	else if (m_bStageCheck[1] == true)
	{
		//Stage2
		if (m_bLineCreate_Check == true)
		{
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				if (m_LineList_Stage2.size() <= 0)
				{
					//LineList의 Size가 0일때 경우
					m_LineList_Stage2.push_back(new LINE(m_tLine_StartPoint, tMousePos));
				}
				else
				{
					//LineList의 Size가 0이 아닐 경우
					//선을 계속해서 이어 갈 때.
					if (m_bLineReStart_Check == true)
						m_LineList_Stage2.push_back(new LINE(m_tLine_StartPoint, tMousePos));
					else
						m_LineList_Stage2.push_back(new LINE(m_LineList_Stage2.back()->tRight_Point, tMousePos));
				}
			}
		}
	}
	else if (m_bStageCheck[2] == true)
	{
		//Stage3
		if (m_bLineCreate_Check == true)
		{
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				if (m_LineList_Stage3.size() <= 0)
				{
					//LineList의 Size가 0일때 경우
					m_LineList_Stage3.push_back(new LINE(m_tLine_StartPoint, tMousePos));
				}
				else
				{
					//LineList의 Size가 0이 아닐 경우
					//선을 계속해서 이어 갈 때.
					if (m_bLineReStart_Check == true)
						m_LineList_Stage3.push_back(new LINE(m_tLine_StartPoint, tMousePos));
					else
						m_LineList_Stage3.push_back(new LINE(m_LineList_Stage3.back()->tRight_Point, tMousePos));
				}
			}
		}
	}
	else if (m_bStageCheck[3] == true)
	{
		//Boss Stage
		if (m_bLineCreate_Check == true)
		{
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON))
			{
				if (m_LineList_BossStage.size() <= 0)
				{
					//LineList의 Size가 0일때 경우
					m_LineList_BossStage.push_back(new LINE(m_tLine_StartPoint, tMousePos));
				}
				else
				{
					//LineList의 Size가 0이 아닐 경우
					//선을 계속해서 이어 갈 때.
					if (m_bLineReStart_Check == true)
						m_LineList_BossStage.push_back(new LINE(m_tLine_StartPoint, tMousePos));
					else
						m_LineList_BossStage.push_back(new LINE(m_LineList_BossStage.back()->tRight_Point, tMousePos));
				}
			}
		}
	}
}

void CLine_Tool::Delete_Line(void)
{
	if (m_bStageCheck[0] == true)
	{
		//Stage 1
		if (m_LineList_Stage1.size() <= 0)
			return;

		if (m_LineList_Stage1.size() > 0)
			m_LineList_Stage1.pop_back();
	}
	else if (m_bStageCheck[1] == true)
	{
		//Stage 2
		if (m_LineList_Stage2.size() <= 0)
			return;

		if (m_LineList_Stage2.size() > 0)
			m_LineList_Stage2.pop_back();
	}
	else if (m_bStageCheck[2] == true)
	{
		//Stage 3
		if (m_LineList_Stage3.size() <= 0)
			return;

		if (m_LineList_Stage3.size() > 0)
			m_LineList_Stage3.pop_back();
	}
	else if (m_bStageCheck[3] == true)
	{
		//Boss Stage
		if (m_LineList_BossStage.size() <= 0)
			return;

		if (m_LineList_BossStage.size() > 0)
			m_LineList_BossStage.pop_back();
	}
}
#pragma endregion

#pragma region Line Tool Ext Render
void CLine_Tool::Display_CutDownKey_Redner(HDC _dc)
{
	TCHAR szF1[128] = L"F1 : 설명 보기";
	TextOut(_dc, 10, 35, szF1, lstrlen(szF1));

	static bool bPress = false;
	if (GETS(CKeyMgr)->StayKeyDown(VK_F1))
		bPress = true;
	if (!GETS(CKeyMgr)->StayKeyDown(VK_F1))
		bPress = false;

	if (bPress == true)
	{
		TCHAR szKeyExplanation[128] = L"Number1: Stage1  Number2: Stage2  Number3: Stage3  Number4: Boss Stage";
		TCHAR szSaveLoad[126] = L"Number5: Save     Number6: Load";
		TCHAR szEx[128] = L" (해당되는 스테이지에서 눌러야 그 스테이지가 저장됨)";
		TCHAR szTile[128] = L"1.S키 : Line 그리기 시작  2.D키 : Line 재시작  3.R키 : Line 다시 시작 포인트  4.C키 : 이전 Line 지우기";

		TextOut(_dc, 10, 50, szKeyExplanation, lstrlen(szKeyExplanation));
		TextOut(_dc, 10, 65, szSaveLoad, lstrlen(szSaveLoad));
		TextOut(_dc, 10, 80, szEx, lstrlen(szEx));
		TextOut(_dc, 10, 105, szTile, lstrlen(szTile));
	}
}
#pragma endregion