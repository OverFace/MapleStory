#include "stdafx.h"
#include "Stage2_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage2_Map::CStage2_Map(void)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = false;

	m_eBGType = BG_END;
}

CStage2_Map::CStage2_Map(bool bCheck)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = bCheck;

	m_eBGType = BG_END;
}

CStage2_Map::~CStage2_Map(void)
{
	Release();
}

void CStage2_Map::LoadDate(void)
{
	//Tile Load
	FILE* pFile = NULL;
	fopen_s(&pFile, "../Data/Stage2_Tile.dat", "rb");

	int iTileX = 0;
	int iTileY = 0;

	fread(&iTileX, sizeof(int), 1, pFile);
	fread(&iTileY, sizeof(int), 1, pFile);

	if (m_vecStage2_Tile.empty() != true)
	{
		for (size_t i = 0; i < m_vecStage2_Tile.size(); ++i)
		{
			SAFE_DELETE(m_vecStage2_Tile[i]);
		}
		m_vecStage2_Tile.clear();
	}

	m_vecStage2_Tile.reserve(iTileX * iTileY);

	for (int i = 0; i < iTileX * iTileY; ++i)
	{
		TILE* pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);
		m_vecStage2_Tile.push_back(pTile);
	}

	fclose(pFile);

	//Line Load
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

		m_Stage2_LineList.push_back(pLine);
	}
	CloseHandle(hFile);
}

void CStage2_Map::Initialize(void)
{
	m_tInfo.fcx = 3056.f;
	m_tInfo.fcy = 1462.f;

	m_eBGType = BG_MAP;
	m_eRenderType = RENDER_BACKGROUND;
	if (m_bStage_Check == false)
		LoadDate();
}

int CStage2_Map::Update(void)
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

void CStage2_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		BitBlt(_dc,
			int(0 + g_fScrollX), int(0 + g_fScrollY),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stage2_Map")->GetMemDC(),
			0, 0, SRCCOPY);
	}	

	//���߿� Ư��Ű�� ������ Render �ǰ� �ؾߵ�
	if (m_bStage_Check == false)
	{
		int iMapSizeX, iMapSizeY, iTileSizeX, iTileSizeY, iCullX, iCullY, iCullEndX, iCullEndY;

		iMapSizeX = STAGE2_MAPSIZEX;
		iMapSizeY = STAGE2_MAPSIZEY;
		iTileSizeX = STAGE2_TILESIZEX;
		iTileSizeY = STAGE2_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE2_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE2_TILESIZEY;
		iCullEndX = STAGE2_MAPSIZEX / STAGE2_TILESIZEX + 2;
		iCullEndY = STAGE2_MAPSIZEY / STAGE2_TILESIZEY + 2;

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
						(int)m_vecStage2_Tile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
						(int)m_vecStage2_Tile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
						iTileSizeX,
						iTileSizeY,
						GETS(CBitMapMgr)->FindImage(L"Tile_62")->GetMemDC(),
						m_vecStage2_Tile[iIndex]->iDrawID * iTileSizeX, 0,
						iTileSizeX, iTileSizeY,
						RGB(255, 255, 255));

					//Line Render
					HPEN old_pen;
					m_Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
					old_pen = (HPEN)SelectObject(_dc, m_Pen);

					MoveToEx(_dc, int(m_Stage2_LineList.front()->tLeft_Point.fx), int(m_Stage2_LineList.front()->tLeft_Point.fy), NULL);

					list<LINE*>::iterator iter_Line = m_Stage2_LineList.begin();
					list<LINE*>::iterator iter_Line_End = m_Stage2_LineList.end();
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

void CStage2_Map::Release(void)
{
	if (m_bStage_Check == false)
	{
		vector<TILE*>::iterator iter = m_vecStage2_Tile.begin();
		for (iter; iter != m_vecStage2_Tile.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		m_vecStage2_Tile.clear();

		list<LINE*>::iterator iter_Line = m_Stage2_LineList.begin();
		for (iter_Line; iter_Line != m_Stage2_LineList.end(); ++iter_Line)
		{
			SAFE_DELETE(*iter_Line);
		}
		m_Stage2_LineList.clear();

		DeleteObject(m_Pen);
	}
}
