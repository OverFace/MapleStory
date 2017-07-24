#include "stdafx.h"
#include "Stage1_Map.h"
#include "BitMapMgr.h"
#include "BitMap.h"

CStage1_Map::CStage1_Map(void)
{
	m_bRender = false;
}

CStage1_Map::~CStage1_Map(void)
{
	Release();
}

void CStage1_Map::LoadData(void)
{
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
}

void CStage1_Map::Initialize(void)
{
	m_tInfo.fcx = 1620.f;
	m_tInfo.fcy = 1025.f;

	m_eRenderType = RENDER_BACKGROUND;

	LoadData();
}

int CStage1_Map::Update(void)
{
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

			TransparentBlt(_dc,
				(int)m_vecStage1_Tile[iIndex]->fx - iTileSizeX / 2 + (int)g_fScrollX,
				(int)m_vecStage1_Tile[iIndex]->fy - iTileSizeY / 2 + (int)g_fScrollY,
				iTileSizeX,
				iTileSizeY,
				GETS(CBitMapMgr)->FindImage(L"Tile1")->GetMemDC(),
				m_vecStage1_Tile[iIndex]->iDrawID * iTileSizeX, 0,
				iTileSizeX, iTileSizeY,
				RGB(255, 255, 255));
		}
	}
}

void CStage1_Map::Release(void)
{
}
