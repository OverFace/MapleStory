#include "stdafx.h"
#include "Stage1_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage1_Map::CStage1_Map(void)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = false;

	ZeroMemory(&m_tRopeInfo, sizeof(INFO));
	ZeroMemory(&m_tRopeRect, sizeof(RECT));		

	ZeroMemory(&m_tOverTile_Info, sizeof(INFO));
	ZeroMemory(&m_tOverTile_Rect, sizeof(RECT));

	m_eBGType = BG_END;
}

CStage1_Map::CStage1_Map(bool bCheck)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = bCheck;

	m_eBGType = BG_END;
}

CStage1_Map::~CStage1_Map(void)
{
	Release();
}

void CStage1_Map::LoadData(void)
{
	//Tile Load
	FILE* pFile = NULL;
	fopen_s(&pFile, "../Data/Stage1_Tile.dat", "rb");

	int iTileX = 0;
	int iTileY = 0;

	fread(&iTileX, sizeof(int), 1, pFile);
	fread(&iTileY, sizeof(int), 1, pFile);

	if (m_vecStage1_Tile.empty() != true)
	{
		for (size_t i = 0; i < m_vecStage1_Tile.size(); ++i)
		{
			SAFE_DELETE(m_vecStage1_Tile[i]);
		}
		m_vecStage1_Tile.clear();
	}

	m_vecStage1_Tile.reserve(iTileX * iTileY);

	for (int i = 0; i < iTileX * iTileY; ++i)
	{
		TILE* pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);
		m_vecStage1_Tile.push_back(pTile);
	}

	fclose(pFile);

	//Line Load
	DWORD dwByte;
	HANDLE hFile = CreateFile(L"../Data/Line_Stage1.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	while (true)
	{
		LINE* pLine = new LINE;
		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

		if(dwByte == 0)
		{ 
			SAFE_DELETE(pLine);
			break;
		}

		m_Stage1_LineList.push_back(pLine);
	}
	CloseHandle(hFile);
}

void CStage1_Map::Initialize(void)
{
	m_tInfo.fcx = 1620.f;
	m_tInfo.fcy = 1025.f;

	//Stage1 Rope Info
	m_tRopeInfo.fx = 1095.f;
	m_tRopeInfo.fy = 500.f;
	m_tRopeInfo.fcx = 5.f;
	m_tRopeInfo.fcy = 420.f;

	//Stage1 Rope Rect
	m_tRopeRect.left = long(m_tRopeInfo.fx - m_tRopeInfo.fcx / 2);
	m_tRopeRect.right = long(m_tRopeInfo.fx + m_tRopeInfo.fcx / 2);
	m_tRopeRect.top = long(m_tRopeInfo.fy - m_tRopeInfo.fcy / 2);
	m_tRopeRect.bottom = long(m_tRopeInfo.fy + m_tRopeInfo.fcy / 2);

	//Stage1 Over Tile Info
	m_tOverTile_Info.fx = 1340.f;
	m_tOverTile_Info.fy = 310.f;
	m_tOverTile_Info.fcx = 560.f;
	m_tOverTile_Info.fcy = 20.f;

	//Stage1 Over Tile Rect
	m_tOverTile_Rect.left = long(m_tOverTile_Info.fx - m_tOverTile_Info.fcx / 2);
	m_tOverTile_Rect.right = long(m_tOverTile_Info.fx + m_tOverTile_Info.fcx / 2);
	m_tOverTile_Rect.top = long(m_tOverTile_Info.fy - m_tOverTile_Info.fcy / 2);
	m_tOverTile_Rect.bottom = long(m_tOverTile_Info.fy + m_tOverTile_Info.fcy / 2);


	m_eBGType = BG_MAP;
	m_eRenderType = RENDER_BACKGROUND;

	if(m_bStage_Check == false)
		LoadData();
}

int CStage1_Map::Update(void)
{
	/*
	system("cls");
	cout << m_tRopeRect.left << endl;
	cout << m_tRopeRect.right << endl;
	cout << m_tRopeRect.top << endl;
	cout << m_tRopeRect.bottom << endl;
	*/	

	//Stage1 Rope Rect
	m_tRopeRect.left	= long(m_tRopeInfo.fx + g_fScrollX - m_tRopeInfo.fcx / 2);
	m_tRopeRect.right	= long(m_tRopeInfo.fx + g_fScrollX + m_tRopeInfo.fcx / 2);
	m_tRopeRect.top		= long(m_tRopeInfo.fy + g_fScrollY - m_tRopeInfo.fcy / 2);
	m_tRopeRect.bottom	= long(m_tRopeInfo.fy + g_fScrollY + m_tRopeInfo.fcy / 2);

	//Stage1 Over Tile Rect
	m_tOverTile_Rect.left	= long(m_tOverTile_Info.fx + g_fScrollX - m_tOverTile_Info.fcx / 2);
	m_tOverTile_Rect.right	= long(m_tOverTile_Info.fx + g_fScrollX + m_tOverTile_Info.fcx / 2);
	m_tOverTile_Rect.top	= long(m_tOverTile_Info.fy + g_fScrollY - m_tOverTile_Info.fcy / 2);
	m_tOverTile_Rect.bottom = long(m_tOverTile_Info.fy + g_fScrollY + m_tOverTile_Info.fcy / 2);


	static bool bIsPress_Five = false;
	if (GetAsyncKeyState('5') && bIsPress_Five == false)
	{
		m_bRender_Tile = true;
		bIsPress_Five = true;
	}
	if (!GetAsyncKeyState('5') && bIsPress_Five == true)
	{
		m_bRender_Tile = false;
		bIsPress_Five = false;
	}

	return 0;
}

void CStage1_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		TransparentBlt(_dc,
			0 + g_fScrollX, 0 + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stage1_Map")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(0, 0, 255));		
	}	

	//나중에 특정키를 누르면 Render 되게 해야됨
	if (m_bStage_Check == false)
	{
		int iMapSizeX, iMapSizeY, iTileSizeX, iTileSizeY, iCullX, iCullY, iCullEndX, iCullEndY;

		iMapSizeX = STAGE1_MAPSIZEX;
		iMapSizeY = STAGE1_MAPSIZEY;
		iTileSizeX = STAGE1_TILESIZEX;
		iTileSizeY = STAGE1_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE1_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE1_TILESIZEY;
		iCullEndX = WINCX / STAGE1_TILESIZEX + 2;
		iCullEndY = WINCY / STAGE1_TILESIZEY + 2;

		for (int i = iCullY; i < iCullY + iCullEndY; ++i)
		{
			for (int j = iCullX; j < iCullX + iCullEndX; ++j)
			{
				int iIndex = i * (iMapSizeX / iTileSizeX) + j;

				if (iIndex < 0 || (iMapSizeX / iTileSizeX)  * (iMapSizeY / iTileSizeY) - 2  < iIndex)
					continue;

				if (m_bRender_Tile == true)
				{
					TransparentBlt(_dc,
						(int)m_vecStage1_Tile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
						(int)m_vecStage1_Tile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
						iTileSizeX,
						iTileSizeY,
						GETS(CBitMapMgr)->FindImage(L"Tile1")->GetMemDC(),
						m_vecStage1_Tile[iIndex]->iDrawID * iTileSizeX, 0,
						iTileSizeX, iTileSizeY,
						RGB(255, 255, 255));

					//Line Render
					HPEN old_pen;
					m_Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					old_pen = (HPEN)SelectObject(_dc, m_Pen);

					MoveToEx(_dc, int(m_Stage1_LineList.front()->tLeft_Point.fx), int(m_Stage1_LineList.front()->tLeft_Point.fy), NULL);

					list<LINE*>::iterator iter_Line = m_Stage1_LineList.begin();
					list<LINE*>::iterator iter_Line_End = m_Stage1_LineList.end();
					for (iter_Line; iter_Line != iter_Line_End; ++iter_Line)
					{
						if ((*iter_Line)->tLeft_Point.fx == 0 && (*iter_Line)->tLeft_Point.fy == 0)
							continue;
						if ((*iter_Line)->tRight_Point.fx == 0 && (*iter_Line)->tRight_Point.fy == 0)
							continue;

						MoveToEx(_dc, int((*iter_Line)->tLeft_Point.fx + g_fScrollX), int((*iter_Line)->tLeft_Point.fy + g_fScrollY), NULL);
						LineTo(_dc, int((*iter_Line)->tRight_Point.fx + g_fScrollX), int((*iter_Line)->tRight_Point.fy + g_fScrollY));
					}

					SelectObject(_dc, old_pen);
				}
			}
		}
	}

	/*
	Rectangle(_dc,
		m_tRopeRect.left,
		m_tRopeRect.top,
		m_tRopeRect.right,
		m_tRopeRect.bottom);
	

	Rectangle(_dc,
		m_tOverTile_Rect.left,
		m_tOverTile_Rect.top,
		m_tOverTile_Rect.right,
		m_tOverTile_Rect.bottom);
	*/
}

void CStage1_Map::Release(void)
{
	if (m_bStage_Check == false)
	{
		vector<TILE*>::iterator iter = m_vecStage1_Tile.begin();
		for (iter; iter != m_vecStage1_Tile.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		m_vecStage1_Tile.clear();

		list<LINE*>::iterator iter_Line = m_Stage1_LineList.begin();
		for (iter_Line; iter_Line != m_Stage1_LineList.end(); ++iter_Line)
		{
			SAFE_DELETE(*iter_Line);
		}
		m_Stage1_LineList.clear();

		DeleteObject(m_Pen);
	}	
}
