#include "stdafx.h"
#include "BStage_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CBstage_Map::CBstage_Map(void)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = false;
}

CBstage_Map::CBstage_Map(bool bCheck)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = bCheck;
}

CBstage_Map::~CBstage_Map(void)
{
	Release();
}

void CBstage_Map::LoadData(void)
{
	//Tile Load
	FILE* pFile = NULL;
	fopen_s(&pFile, "../Data/BStage_Tile.dat", "rb");

	int iTileX = 0;
	int iTileY = 0;

	fread(&iTileX, sizeof(int), 1, pFile);
	fread(&iTileY, sizeof(int), 1, pFile);

	if (m_vecBtage_Tile.empty() != true)
	{
		for (size_t i = 0; i < m_vecBtage_Tile.size(); ++i)
		{
			SAFE_DELETE(m_vecBtage_Tile[i]);
		}
		m_vecBtage_Tile.clear();
	}

	m_vecBtage_Tile.reserve(iTileX * iTileY);

	for (int i = 0; i < iTileX * iTileY; ++i)
	{
		TILE* pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);
		m_vecBtage_Tile.push_back(pTile);
	}

	fclose(pFile);

	//Line Load
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

		m_StageBoss_LineList.push_back(pLine);
	}
	CloseHandle(hFile);
}

void CBstage_Map::Initialize(void)
{
	m_tInfo.fcx = 1799.f;
	m_tInfo.fcy = 781.f;

	m_eRenderType = RENDER_BACKGROUND;

	if (m_bStage_Check == false)
		LoadData();
}

int CBstage_Map::Update(void)
{
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

void CBstage_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		TransparentBlt(_dc,
			0 + g_fScrollX, 0 + g_fScrollY,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Boss_Map")->GetMemDC(),
			0, 0,
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			RGB(66, 66, 66));
	}	

	if (m_bStage_Check == false)
	{
		int iMapSizeX, iMapSizeY, iTileSizeX, iTileSizeY, iCullX, iCullY, iCullEndX, iCullEndY;

		iMapSizeX = BSTAGE_MAPSIZEX;
		iMapSizeY = BSTAGE_MAPSIZEY;
		iTileSizeX = BSTAGE_TILESIZEX;
		iTileSizeY = BSTAGE_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / BSTAGE_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / BSTAGE_TILESIZEY;
		iCullEndX = BSTAGE_MAPSIZEX / BSTAGE_TILESIZEX + 2;
		iCullEndY = BSTAGE_MAPSIZEY / BSTAGE_TILESIZEY + 2;

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
						(int)m_vecBtage_Tile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
						(int)m_vecBtage_Tile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
						iTileSizeX,
						iTileSizeY,
						GETS(CBitMapMgr)->FindImage(L"Tile_63")->GetMemDC(),
						m_vecBtage_Tile[iIndex]->iDrawID * iTileSizeX, 0,
						iTileSizeX, iTileSizeY,
						RGB(255, 255, 255));

					//Line Render
					HPEN old_pen;
					m_Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					old_pen = (HPEN)SelectObject(_dc, m_Pen);

					MoveToEx(_dc, int(m_StageBoss_LineList.front()->tLeft_Point.fx), int(m_StageBoss_LineList.front()->tLeft_Point.fy), NULL);

					list<LINE*>::iterator iter_Line = m_StageBoss_LineList.begin();
					list<LINE*>::iterator iter_Line_End = m_StageBoss_LineList.end();
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
}

void CBstage_Map::Release(void)
{
	if (m_bStage_Check == false)
	{
		vector<TILE*>::iterator iter = m_vecBtage_Tile.begin();
		for (iter; iter != m_vecBtage_Tile.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		m_vecBtage_Tile.clear();

		list<LINE*>::iterator iter_Line = m_StageBoss_LineList.begin();
		for (iter_Line; iter_Line != m_StageBoss_LineList.end(); ++iter_Line)
		{
			SAFE_DELETE(*iter_Line);
		}
		m_StageBoss_LineList.clear();

		DeleteObject(m_Pen);
	}
}
