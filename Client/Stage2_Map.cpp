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

	//나중에 특정키를 누르면 Render 되게 해야됨
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
	}
}
