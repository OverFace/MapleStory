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

	for(int i = 0; i < 4; ++i)
		m_bStageCheck[i] = false;
	m_bLineCreate_Check = false;
	m_bLineClick_Check = false;
	m_bLineComplete_Check = false;

	m_pStage1_Back = NULL;
	m_pStage1_Map = NULL;
	m_pStage2_Map = NULL;
	m_pStage3_Map = NULL;
	m_pBStage_Back = NULL;
	m_pBStage_Map = NULL;

	ZeroMemory(&m_tLine_Point_Left, sizeof(LINEPOINT));
	ZeroMemory(&m_tLine_Point_Right, sizeof(LINEPOINT));
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
	//Line Render
	if (m_bStageCheck[0] == true)
	{
		//Stage 1
		if (m_LineList_Stage1.empty() == false)
		{
			MoveToEx(_dc, (int)m_LineList_Stage1.front()->tLeft_Point.fx, (int)m_LineList_Stage1.front()->tLeft_Point.fy, NULL);

			LINEITER iter = m_LineList_Stage1.begin();
			LINEITER iter_End = m_LineList_Stage1.end();
			for (iter; iter != iter_End; ++iter)
				LineTo(_dc, (int)(*iter)->tRight_Point.fx, (int)(*iter)->tRight_Point.fy);
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

	//Obj Mgr Render
	GETS(CObjMgr)->Render(_dc);
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
	}
#pragma endregion
#pragma region Line Create Key
	if (GETS(CKeyMgr)->OnceKeyDown('S'))
	{
		//Line Create Start
		m_bLineCreate_Check = true;
	}
	if (m_bLineCreate_Check == true && GETS(CKeyMgr)->OnceKeyDown('S'))
	{
		//Line Create Stop
		m_bLineCreate_Check = false;
	}
#pragma endregion
#pragma region Save & Load Key
	if (GETS(CKeyMgr)->OnceKeyDown('5'))
	{
		//Save Data
	}
	else if (GETS(CKeyMgr)->OnceKeyDown('6'))
	{
		//Load Data
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

}

void CLine_Tool::Load_Data(void)
{

}
#pragma endregion

#pragma region Line
void CLine_Tool::Create_Line(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (m_bLineCreate_Check == true)
	{
		if (m_bStageCheck[0] == true)
		{
			//Stage1
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bLineClick_Check == false)
			{
				m_tLine_Point_Left.fx = (float)pt.x;
				m_tLine_Point_Left.fy = (float)pt.y;
				m_bLineClick_Check = true;
			}
			
			//�� �κ��� �ȵȴ�.. ����???
			if (GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bLineClick_Check == true)
			{
				if (m_bLineComplete_Check == false)
				{
					m_tLine_Point_Right.fx = (float)pt.x;
					m_tLine_Point_Right.fy = (float)pt.y;

					m_bLineClick_Check = false;
					m_bLineComplete_Check = true;
				}
			}

			if (m_bLineComplete_Check == true)
			{
				m_LineList_Stage1.push_back(new LINE(m_tLine_Point_Left, m_tLine_Point_Right));
				m_bLineComplete_Check = false;
			}

			system("cls");
			cout << m_bLineClick_Check << endl;
			cout << m_bLineComplete_Check << endl;
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
}
#pragma endregion