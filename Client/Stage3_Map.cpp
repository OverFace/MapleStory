#include "stdafx.h"
#include "Stage3_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage3_Map::CStage3_Map(void)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = false;
}

CStage3_Map::CStage3_Map(bool bCheck)
{
	m_bRender = false;
	m_bRender_Tile = false;
	m_bStage_Check = bCheck;
}

CStage3_Map::~CStage3_Map(void)
{
	Release();
}

void CStage3_Map::LoadData(void)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, "../Data/Stage3_Tile.dat", "rb");

	int iTileX = 0;
	int iTileY = 0;

	fread(&iTileX, sizeof(int), 1, pFile);
	fread(&iTileY, sizeof(int), 1, pFile);

	if (m_vecStage3_Tile.empty() != true)
	{
		for (size_t i = 0; i < m_vecStage3_Tile.size(); ++i)
		{
			SAFE_DELETE(m_vecStage3_Tile[i]);
		}
		m_vecStage3_Tile.clear();
	}

	m_vecStage3_Tile.reserve(iTileX * iTileY);

	for (int i = 0; i < iTileX * iTileY; ++i)
	{
		TILE* pTile = new TILE;
		fread(pTile, sizeof(TILE), 1, pFile);
		m_vecStage3_Tile.push_back(pTile);
	}

	fclose(pFile);
}

void CStage3_Map::Initialize(void)
{
	m_tInfo.fcx = 1510.f;
	m_tInfo.fcy = 768.f;

	m_eRenderType = RENDER_BACKGROUND;

	if (m_bStage_Check == false)
		LoadData();
}

int CStage3_Map::Update(void)
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

void CStage3_Map::Render(HDC _dc)
{
	if (m_bRender == true)
	{
		BitBlt(_dc,
			int(0 + g_fScrollX), int(0 + g_fScrollY),
			int(m_tInfo.fcx), int(m_tInfo.fcy),
			GETS(CBitMapMgr)->FindImage(L"Stage3_Map")->GetMemDC(),
			0, 0, SRCCOPY);
	}	

	if (m_bStage_Check == false)
	{
		int iMapSizeX, iMapSizeY, iTileSizeX, iTileSizeY, iCullX, iCullY, iCullEndX, iCullEndY;

		iMapSizeX = STAGE3_MAPSIZEX;
		iMapSizeY = STAGE3_MAPSIZEY;
		iTileSizeX = STAGE3_TILESIZEX;
		iTileSizeY = STAGE3_TILESIZEY;
		iCullX = ((int)-g_fScrollX) / STAGE3_TILESIZEX;
		iCullY = ((int)-g_fScrollY) / STAGE3_TILESIZEY;
		iCullEndX = STAGE3_MAPSIZEX / STAGE3_TILESIZEX + 2;
		iCullEndY = STAGE3_MAPSIZEY / STAGE3_TILESIZEY + 2;

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
						(int)m_vecStage3_Tile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
						(int)m_vecStage3_Tile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
						iTileSizeX,
						iTileSizeY,
						GETS(CBitMapMgr)->FindImage(L"Tile_58")->GetMemDC(),
						m_vecStage3_Tile[iIndex]->iDrawID * iTileSizeX, 0,
						iTileSizeX, iTileSizeY,
						RGB(255, 255, 255));
				}
			}
		}
	}
}

void CStage3_Map::Release(void)
{
	if (m_bStage_Check == false)
	{
		vector<TILE*>::iterator iter = m_vecStage3_Tile.begin();
		for (iter; iter != m_vecStage3_Tile.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		m_vecStage3_Tile.clear();
	}
}
