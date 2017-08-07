#include "stdafx.h"
#include "Edit.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"

#include "Stage1_Back.h"
#include "Stage1_Map.h"
#include "Stage2_Map.h"
#include "Stage3_Map.h"
#include "BStage_Back.h"
#include "BStage_Map.h"

CEdit::CEdit(void)
{
	m_pStage1_Back = NULL;
	m_pStage1_Map = NULL;
	m_pStage2_Map = NULL;
	m_pStage3_Map = NULL;
	m_pBStage_Back = NULL;
	m_pBStage_Map = NULL;

	m_fScrollSpeed = 10.f;
	m_iChangeCount = 0;
	m_iBoxNum = 0;

	memset(&m_tBox, 0, sizeof(RECT));
	for (int i = 0; i < 4; ++i)
	{
		m_bStageCheck[i] = false;
	}
}

CEdit::~CEdit(void)
{
	Release();
}

void CEdit::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_EDIT);

	//Stage1
	for (int i = 0; i < STAGE1_TILECNTY; ++i)
	{
		for (int j = 0; j < STAGE1_TILECNTX; ++j)
		{
			float fx = (float)(STAGE1_TILESIZEX * j) + STAGE1_TILESIZEX / 2;
			float fy = (float)(STAGE1_TILESIZEY * i) + STAGE1_TILESIZEY / 2;

			m_vecTile.push_back(CreateTile(fx, fy, 0));
		}
	}

	//Stage2
	for (int i = 0; i < STAGE2_TILECNTY; ++i)
	{
		for (int j = 0; j < STAGE2_TILECNTX; ++j)
		{
			float fx = (float)(STAGE2_TILESIZEX * j) + STAGE2_TILESIZEX / 2;
			float fy = (float)(STAGE2_TILESIZEY * i) + STAGE2_TILESIZEY / 2;

			m_vecTile_Stage2.push_back(CreateTile(fx, fy, 1));
		}
	}

	//Stage3
	for (int i = 0; i < STAGE3_TILECNTY; ++i)
	{
		for (int j = 0; j < STAGE3_TILECNTX; ++j)
		{
			float fx = (float)(STAGE3_TILESIZEX * j) + STAGE3_TILESIZEX / 2;
			float fy = (float)(STAGE3_TILESIZEY * i) + STAGE3_TILESIZEY / 2;

			m_vecTile_Stage3.push_back(CreateTile(fx, fy, 2));
		}
	}

	//Boss Stage
	for (int i = 0; i < BSTAGE_TILECNTY; ++i)
	{
		for (int j = 0; j < BSTAGE_TILECNTX; ++j)
		{
			float fx = (float)(BSTAGE_TILESIZEX * j) + BSTAGE_TILESIZEX / 2;
			float fy = (float)(BSTAGE_TILESIZEY * i) + BSTAGE_TILESIZEY / 2;

			m_vecTile_BStage.push_back(CreateTile(fx, fy, 3));
		}
	}

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

int CEdit::Update(void)
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

	//Mouse Click
	static bool bIsPress = false;
	if (GETS(CKeyMgr)->GetKeyDown(VK_LBUTTON) && bIsPress == false)
	{
		bIsPress = true;
		Picking();
	}
	if (!GETS(CKeyMgr)->GetKeyDown(VK_LBUTTON) && bIsPress == true)
		bIsPress = false;

	//Short Cut Key & Scene Change
	ShortCut_Key();
	Scene_Change();

	//Save & Load
	SaveData();
	LoadData();

	return 0;
}

void CEdit::Render(HDC _dc)
{
	//Obj Mgr Render
	GETS(CObjMgr)->Render(_dc);

	int iMapSizeX, iMapSizeY, iTileSizeX, iTileSizeY, iCullX, iCullY, iCullEndX, iCullEndY;
	
	/*
	system("cls");
	cout << "Map Size X : " << iMapSizeX << endl;
	cout << "Map Size Y : " << iMapSizeY << endl;
	cout << "Tile Size X : " << iTileSizeX << endl;
	cout << "Tile Size Y : " << iTileSizeY << endl;
	cout << "Cull X : " << iCullX << endl;
	cout << "Cull Y : " << iCullY << endl;
	cout << "Cull End X : " << iCullEndX << endl;
	cout << "Cull End Y : " << iCullEndY << endl;
	*/

	if (m_iChangeCount == 0)
	{
		//Stage1
		iMapSizeX = STAGE1_MAPSIZEX;
		iMapSizeY = STAGE1_MAPSIZEY;
		iTileSizeX = STAGE1_TILESIZEX;
		iTileSizeY = STAGE1_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE1_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE1_TILESIZEY;
		iCullEndX = WINCX / STAGE1_TILESIZEX + 2;
		iCullEndY = WINCY / STAGE1_TILESIZEY + 2;
	}
	else if (m_iChangeCount == 1)
	{
		//Stage2
		iMapSizeX = STAGE2_MAPSIZEX;
		iMapSizeY = STAGE2_MAPSIZEY;
		iTileSizeX = STAGE2_TILESIZEX;
		iTileSizeY = STAGE2_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE2_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE2_TILESIZEY;
		iCullEndX = STAGE2_MAPSIZEX / STAGE2_TILESIZEX + 2;
		iCullEndY = STAGE2_MAPSIZEY / STAGE2_TILESIZEY + 2;
	}
	else if (m_iChangeCount == 2)
	{
		//Stage3
		iMapSizeX = STAGE3_MAPSIZEX;
		iMapSizeY = STAGE3_MAPSIZEY;
		iTileSizeX = STAGE3_TILESIZEX;
		iTileSizeY = STAGE3_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE3_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE3_TILESIZEY;
		iCullEndX = STAGE3_MAPSIZEX / STAGE3_TILESIZEX + 2;
		iCullEndY = STAGE3_MAPSIZEY / STAGE3_TILESIZEY + 2;
	}
	else if (m_iChangeCount == 3)
	{
		//Boss Stage
		iMapSizeX = BSTAGE_MAPSIZEX;
		iMapSizeY = BSTAGE_MAPSIZEY;
		iTileSizeX = BSTAGE_TILESIZEX;
		iTileSizeY = BSTAGE_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / BSTAGE_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / BSTAGE_TILESIZEY;
		iCullEndX = BSTAGE_MAPSIZEX / BSTAGE_TILESIZEX + 2;
		iCullEndY = BSTAGE_MAPSIZEY / BSTAGE_TILESIZEY + 2;
	}	

	for (int i = iCullY; i < iCullY + iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullX + iCullEndX; ++j)
		{
			int iIndex = i * (iMapSizeX / iTileSizeX) + j;

			if (iIndex < 0 || (iMapSizeX / iTileSizeX)  * (iMapSizeY / iTileSizeY) - 2  < iIndex)
				continue;

			if (m_iChangeCount == 0)
			{
				TransparentBlt(_dc,
					(int)m_vecTile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
					(int)m_vecTile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
					iTileSizeX,
					iTileSizeY,
					GETS(CBitMapMgr)->FindImage(L"Tile1")->GetMemDC(),
					m_vecTile[iIndex]->iDrawID * iTileSizeX, 0,
					iTileSizeX, iTileSizeY,
					RGB(255, 255, 255));
			}
			else if (m_iChangeCount == 1)
			{
				TransparentBlt(_dc,
					(int)m_vecTile_Stage2[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
					(int)m_vecTile_Stage2[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
					iTileSizeX,
					iTileSizeY,
					GETS(CBitMapMgr)->FindImage(L"Tile_62")->GetMemDC(),
					m_vecTile_Stage2[iIndex]->iDrawID * iTileSizeX, 0,
					iTileSizeX, iTileSizeY,
					RGB(255, 255, 255));
			}
			else if (m_iChangeCount == 2)
			{
				TransparentBlt(_dc,
					(int)m_vecTile_Stage3[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
					(int)m_vecTile_Stage3[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
					iTileSizeX,
					iTileSizeY,
					GETS(CBitMapMgr)->FindImage(L"Tile_58")->GetMemDC(),
					m_vecTile_Stage3[iIndex]->iDrawID * iTileSizeX, 0,
					iTileSizeX, iTileSizeY,
					RGB(255, 255, 255));
			}
			else if (m_iChangeCount == 3)
			{
				TransparentBlt(_dc,
					(int)m_vecTile_BStage[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
					(int)m_vecTile_BStage[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
					iTileSizeX,
					iTileSizeY,
					GETS(CBitMapMgr)->FindImage(L"Tile_63")->GetMemDC(),
					m_vecTile_BStage[iIndex]->iDrawID * iTileSizeX, 0,
					iTileSizeX, iTileSizeY,
					RGB(255, 255, 255));
			}
		}
	}	

	//Display ShortCut Key
	TCHAR szF1[128] = L"F1 : 설명 보기";
	TextOut(_dc, 10, 35, szF1, lstrlen(szF1));
	
	static bool bIsPress_F1 = false;
	if (GETS(CKeyMgr)->GetKeyDown(VK_F1) && bIsPress_F1 == false)
	{
		bIsPress_F1 = true;		
	}
	if (!GETS(CKeyMgr)->GetKeyDown(VK_F1) && bIsPress_F1 == true)
		bIsPress_F1 = false;

	if (bIsPress_F1 == true)
	{
		TCHAR szKeyExplanation[128] = L"Number1: Stage1  Number2: Stage2  Number3: Stage3  Number4: Boss Stage";
		TCHAR szSaveLoad[126] = L"Number5: Save     Number6: Load";
		TCHAR szEx[128] = L" (해당되는 스테이지에서 눌러야 그 스테이지가 저장됨)";
		TCHAR szTile[128] = L"1.Green_Tile: 통과 O    2.Red_Tile: 통과 X    3.Yellow_Tile: 탈수있는 지형";

		TextOut(_dc, 10, 50, szKeyExplanation, lstrlen(szKeyExplanation));
		TextOut(_dc, 10, 65, szSaveLoad, lstrlen(szSaveLoad));
		TextOut(_dc, 10, 80, szEx, lstrlen(szEx));
		TextOut(_dc, 10, 105, szTile, lstrlen(szTile));
	}	
}

void CEdit::Release(void)
{
	//Obj Mgr Release
	GETS(CObjMgr)->DestroyInstance();

	vector<TILE*>::iterator iter = m_vecTile.begin();
	for (iter; iter != m_vecTile.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecTile.clear();

	vector<TILE*>::iterator iter_Stage2 = m_vecTile_Stage2.begin();
	for (iter_Stage2; iter_Stage2 != m_vecTile_Stage2.end(); ++iter_Stage2)
	{
		SAFE_DELETE(*iter_Stage2);
	}
	m_vecTile_Stage2.clear();

	vector<TILE*>::iterator iter_Stage3 = m_vecTile_Stage3.begin();
	for (iter_Stage3; iter_Stage3 != m_vecTile_Stage3.end(); ++iter_Stage3)
	{
		SAFE_DELETE(*iter_Stage3);
	}
	m_vecTile_Stage3.clear();

	vector<TILE*>::iterator iter_Boss = m_vecTile_BStage.begin();
	for (iter_Boss; iter_Boss != m_vecTile_BStage.end(); ++iter_Boss)
	{
		SAFE_DELETE(*iter_Boss);
	}
	m_vecTile_BStage.clear();
}

TILE * CEdit::CreateTile(float _fx, float _fy, int _iCount)
{
	TILE* pTile = new TILE;

	pTile->fx  = _fx;
	pTile->fy  = _fy;	
	pTile->iDrawID = 0;
	pTile->iOption = 0;

	switch (_iCount)
	{
	case 0:
		pTile->fcx = STAGE1_TILESIZEX;
		pTile->fcy = STAGE1_TILESIZEY;
		break;
	case 1:
		pTile->fcx = STAGE2_TILESIZEX;
		pTile->fcy = STAGE2_TILESIZEY;
		break;
	case 2:
		pTile->fcx = STAGE3_TILESIZEX;
		pTile->fcy = STAGE3_TILESIZEY;
		break;
	case 3:
		pTile->fcx = BSTAGE_TILESIZEX;
		pTile->fcy = BSTAGE_TILESIZEY;
		break;
	}

	return pTile;
}

void CEdit::Picking(void)
{
	/*
	iOption 
	0 : 갈수 있는 타일
	1 : 못가는 타일
	2 : 땅 위에 떠 있는 지형.
	3 : 기타(나중에 더 생각해보기)
	*/

	POINT pt;
	pt = CMouse::GetPos();

	int iIndex = 0;	

	/*
	system("cls");
	cout << pt.x << endl;
	cout << pt.y << endl;
	*/

	if (m_iChangeCount == 0)
	{
		int iX = (pt.x - (int)g_fScrollX) / STAGE1_TILESIZEX;
		int iY = (pt.y - (int)g_fScrollY) / STAGE1_TILESIZEY;
		iIndex = iY * (STAGE1_MAPSIZEX / STAGE1_TILESIZEX) + iX;	

		/*
		cout << "--------------------------------" << endl;
		cout << "Index : " << iIndex << endl;
		cout << "fx : " << m_vecTile[iIndex]->fx << endl;
		cout << "fy : " << m_vecTile[iIndex]->fy << endl;
		*/

		++m_vecTile[iIndex]->iDrawID;

		if (m_vecTile[iIndex]->iDrawID == 0)
		{ 
			m_vecTile[iIndex]->iOption = 0;
		}
		else if (m_vecTile[iIndex]->iDrawID == 1)
		{
			m_vecTile[iIndex]->iOption = 1;
		}
		else if (m_vecTile[iIndex]->iDrawID == 2)
		{
			m_vecTile[iIndex]->iOption = 2;
		}
		else if (m_vecTile[iIndex]->iDrawID == 3)
		{
			m_vecTile[iIndex]->iOption = 3;
		}

		if (m_vecTile[iIndex]->iDrawID > 3)
		{
			m_vecTile[iIndex]->iDrawID = 0;
			m_vecTile[iIndex]->iOption = 0;
		}		
	}	
	else if (m_iChangeCount == 1)
	{
		int iX = (pt.x - (int)g_fScrollX) / STAGE2_TILESIZEX;
		int iY = (pt.y - (int)g_fScrollY) / STAGE2_TILESIZEY;
		iIndex = iY * (STAGE2_MAPSIZEX / STAGE2_TILESIZEX) + iX + iY;

		++m_vecTile_Stage2[iIndex]->iDrawID;

		if (m_vecTile_Stage2[iIndex]->iDrawID == 0)
		{
			m_vecTile_Stage2[iIndex]->iOption = 0;
		}
		else if (m_vecTile_Stage2[iIndex]->iDrawID == 1)
		{
			m_vecTile_Stage2[iIndex]->iOption = 1;
		}
		else if (m_vecTile_Stage2[iIndex]->iDrawID == 2)
		{
			m_vecTile_Stage2[iIndex]->iOption = 2;
		}
		else if (m_vecTile_Stage2[iIndex]->iDrawID == 3)
		{
			m_vecTile_Stage2[iIndex]->iOption = 3;
		}

		if (m_vecTile_Stage2[iIndex]->iDrawID > 3)
		{
			m_vecTile_Stage2[iIndex]->iDrawID = 0;
			m_vecTile_Stage2[iIndex]->iOption = 0;
		}
	}
	else if (m_iChangeCount == 2)
	{
		int iX = (pt.x - (int)g_fScrollX) / STAGE3_TILESIZEX;
		int iY = (pt.y - (int)g_fScrollY) / STAGE3_TILESIZEY;
		iIndex = iY * (STAGE3_MAPSIZEX / STAGE3_TILESIZEX) + iX;

		++m_vecTile_Stage3[iIndex]->iDrawID;

		if (m_vecTile_Stage3[iIndex]->iDrawID == 0)
		{
			m_vecTile_Stage3[iIndex]->iOption = 0;
		}
		else if (m_vecTile_Stage3[iIndex]->iDrawID == 1)
		{
			m_vecTile_Stage3[iIndex]->iOption = 1;
		}
		else if (m_vecTile_Stage3[iIndex]->iDrawID == 2)
		{
			m_vecTile_Stage3[iIndex]->iOption = 2;
		}
		else if (m_vecTile_Stage3[iIndex]->iDrawID == 3)
		{
			m_vecTile_Stage3[iIndex]->iOption = 3;
		}

		if (m_vecTile_Stage3[iIndex]->iDrawID > 3)
		{
			m_vecTile_Stage3[iIndex]->iDrawID = 0;
			m_vecTile_Stage3[iIndex]->iOption = 0;
		}
	}
	else if (m_iChangeCount == 3)
	{
		int iX = (pt.x - (int)g_fScrollX) / BSTAGE_TILESIZEX;
		int iY = (pt.y - (int)g_fScrollY) / BSTAGE_TILESIZEY;
		iIndex = iY * (BSTAGE_MAPSIZEX / BSTAGE_TILESIZEX) + iX + iY;

		++m_vecTile_BStage[iIndex]->iDrawID;

		if (m_vecTile_BStage[iIndex]->iDrawID == 0)
		{
			m_vecTile_BStage[iIndex]->iOption = 0;
		}
		else if (m_vecTile_BStage[iIndex]->iDrawID == 1)
		{
			m_vecTile_BStage[iIndex]->iOption = 1;
		}
		else if (m_vecTile_BStage[iIndex]->iDrawID == 2)
		{
			m_vecTile_BStage[iIndex]->iOption = 2;
		}
		else if (m_vecTile_BStage[iIndex]->iDrawID == 3)
		{
			m_vecTile_BStage[iIndex]->iOption = 3;
		}

		if (m_vecTile_BStage[iIndex]->iDrawID > 3)
		{
			m_vecTile_BStage[iIndex]->iDrawID = 0;
			m_vecTile_BStage[iIndex]->iOption = 0;
		}
	}
}

void CEdit::ShortCut_Key(void)
{
	static bool bIsPress_One = false;
	if (GetAsyncKeyState('1') && bIsPress_One == false)
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
		
		bIsPress_One = true;
	}
	if (!GetAsyncKeyState('1') && bIsPress_One == true)
		bIsPress_One = false;

	static bool bIsPress_Two = false;
	if (GetAsyncKeyState('2') && bIsPress_Two == false)
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

		bIsPress_Two = true;
	}
	if (!GetAsyncKeyState('2') && bIsPress_Two == true)
		bIsPress_Two = false;

	static bool bIsPress_Three = false;
	if (GetAsyncKeyState('3') && bIsPress_Three == false)
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

		bIsPress_Three = true;
	}
	if (!GetAsyncKeyState('3') && bIsPress_Three == true)
		bIsPress_Three = false;

	static bool bIsPress_Fore = false;
	if (GetAsyncKeyState('4') && bIsPress_Fore == false)
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

		bIsPress_Fore = true;
	}
	if (!GetAsyncKeyState('4') && bIsPress_Fore == true)
		bIsPress_Fore = false;
}

void CEdit::Scene_Change(void)
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

void CEdit::SaveData(void)
{
	static bool bIsPress_Save = false;
	if (GetAsyncKeyState('5') && bIsPress_Save == false)
	{
		if (m_iChangeCount == 0)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage1_Tile.dat", "wb");

			int iTileX = STAGE1_TILECNTX;
			int iTileY = STAGE1_TILECNTY;

			fwrite(&iTileX, sizeof(int), 1, pFile);
			fwrite(&iTileY, sizeof(int), 1, pFile);

			int iCnt = m_vecTile.size();

			for (int i = 0; i < iCnt; ++i)
			{
				fwrite(m_vecTile[i], sizeof(TILE), 1, pFile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 1)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage2_Tile.dat", "wb");

			int iTileX = STAGE2_TILECNTX;
			int iTileY = STAGE2_TILECNTY;

			fwrite(&iTileX, sizeof(int), 1, pFile);
			fwrite(&iTileY, sizeof(int), 1, pFile);

			int iCnt = m_vecTile_Stage2.size();

			for (int i = 0; i < iCnt; ++i)
			{
				fwrite(m_vecTile_Stage2[i], sizeof(TILE), 1, pFile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 2)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage3_Tile.dat", "wb");

			int iTileX = STAGE3_TILECNTX;
			int iTileY = STAGE3_TILECNTY;

			fwrite(&iTileX, sizeof(int), 1, pFile);
			fwrite(&iTileY, sizeof(int), 1, pFile);

			int iCnt = m_vecTile_Stage3.size();

			for (int i = 0; i < iCnt; ++i)
			{
				fwrite(m_vecTile_Stage3[i], sizeof(TILE), 1, pFile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 3)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/BStage_Tile.dat", "wb");

			int iTileX = BSTAGE_TILECNTX;
			int iTileY = BSTAGE_TILECNTY;

			fwrite(&iTileX, sizeof(int), 1, pFile);
			fwrite(&iTileY, sizeof(int), 1, pFile);

			int iCnt = m_vecTile_BStage.size();

			for (int i = 0; i < iCnt; ++i)
			{
				fwrite(m_vecTile_BStage[i], sizeof(TILE), 1, pFile);
			}

			fclose(pFile);
		}
		MessageBox(g_hWnd, L"Save Complete", L"System", MB_OK);	
		bIsPress_Save = true;
	}
	if (!GetAsyncKeyState('5') && bIsPress_Save == true)
		bIsPress_Save = false;
}

void CEdit::LoadData(void)
{
	static bool bIsPress_Load = false;
	if (GetAsyncKeyState('6') && bIsPress_Load == false)
	{
		if (m_iChangeCount == 0)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage1_Tile.dat", "rb");

			int iTileX = 0;
			int iTileY = 0;

			fread(&iTileX, sizeof(int), 1, pFile);
			fread(&iTileY, sizeof(int), 1, pFile);

			if (m_vecTile.empty() != true)
			{
				for (size_t i = 0; i < m_vecTile.size(); ++i)
				{
					SAFE_DELETE(m_vecTile[i]);
				}
				m_vecTile.clear();
			}

			m_vecTile.reserve(iTileX * iTileY);

			for (int i = 0; i < iTileX * iTileY; ++i)
			{
				TILE* pTile = new TILE;
				fread(pTile, sizeof(TILE), 1, pFile);
				m_vecTile.push_back(pTile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 1)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage2_Tile.dat", "rb");

			int iTileX = 0;
			int iTileY = 0;

			fread(&iTileX, sizeof(int), 1, pFile);
			fread(&iTileY, sizeof(int), 1, pFile);

			if (m_vecTile_Stage2.empty() != true)
			{
				for (size_t i = 0; i < m_vecTile_Stage2.size(); ++i)
				{
					SAFE_DELETE(m_vecTile_Stage2[i]);
				}
				m_vecTile_Stage2.clear();
			}

			m_vecTile_Stage2.reserve(iTileX * iTileY);

			for (int i = 0; i < iTileX * iTileY; ++i)
			{
				TILE* pTile = new TILE;
				fread(pTile, sizeof(TILE), 1, pFile);
				m_vecTile_Stage2.push_back(pTile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 2)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/Stage3_Tile.dat", "rb");

			int iTileX = 0;
			int iTileY = 0;

			fread(&iTileX, sizeof(int), 1, pFile);
			fread(&iTileY, sizeof(int), 1, pFile);

			if (m_vecTile_Stage3.empty() != true)
			{
				for (size_t i = 0; i < m_vecTile_Stage3.size(); ++i)
				{
					SAFE_DELETE(m_vecTile_Stage3[i]);
				}
				m_vecTile_Stage3.clear();
			}

			m_vecTile_Stage3.reserve(iTileX * iTileY);

			for (int i = 0; i < iTileX * iTileY; ++i)
			{
				TILE* pTile = new TILE;
				fread(pTile, sizeof(TILE), 1, pFile);
				m_vecTile_Stage3.push_back(pTile);
			}

			fclose(pFile);
		}
		else if (m_iChangeCount == 3)
		{
			FILE* pFile = NULL;
			fopen_s(&pFile, "../Data/BStage_Tile.dat", "rb");

			int iTileX = 0;
			int iTileY = 0;

			fread(&iTileX, sizeof(int), 1, pFile);
			fread(&iTileY, sizeof(int), 1, pFile);

			if (m_vecTile_BStage.empty() != true)
			{
				for (size_t i = 0; i < m_vecTile_BStage.size(); ++i)
				{
					SAFE_DELETE(m_vecTile_BStage[i]);
				}
				m_vecTile_BStage.clear();
			}

			m_vecTile_BStage.reserve(iTileX * iTileY);

			for (int i = 0; i < iTileX * iTileY; ++i)
			{
				TILE* pTile = new TILE;
				fread(pTile, sizeof(TILE), 1, pFile);
				m_vecTile_BStage.push_back(pTile);
			}

			fclose(pFile);
		}
		MessageBox(g_hWnd, L"Load Complete", L"System", MB_OK);
		bIsPress_Load = true;
	}
	if (!GetAsyncKeyState('6') && bIsPress_Load == true)
		bIsPress_Load = false;
}
