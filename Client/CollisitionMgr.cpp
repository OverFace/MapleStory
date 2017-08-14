#include "stdafx.h"
#include "CollisitionMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Stage1_Map.h"

IMPLEMENT_SINGLETON(CCollisitionMgr)
CCollisitionMgr::CCollisitionMgr(void)
{
}

CCollisitionMgr::~CCollisitionMgr(void)
{
}

bool CCollisitionMgr::TileCollision(CObj* p1, TILE* p2, float* pX, float* pY, float _fTempY)
{
	/*
	fTempY : ScrollY 값 적용시에 타일보다 위에 플레이어가 떠 있으므로
	         그 값을 바닥에 맞게 맞춰 주기 위해서 주는 Y 값.
	*/

	float fWidth = abs(p1->GetInfo()->fx - p2->fx - g_fScrollX);
	float fHeight = abs(p1->GetInfo()->fy - p2->fy - g_fScrollY - _fTempY);

	float fSizeX = p1->GetInfo()->fcx / 2 + p2->fcx / 2;
	float fSizeY = p1->GetInfo()->fcy / 2 + p2->fcy / 2;

	if (p2->iOption == 1)
	{
		if (pX != NULL && pY != NULL)
		{
			*pX = abs(fSizeX - fWidth);
			*pY = abs(fSizeY - fHeight);

			if (*pX > *pY)
			{
				//아래서 온 충돌
				if (p1->GetInfo()->fy > p2->fy)
				{
					*pY *= -1;
				}
			}
			else
			{
				if (p1->GetInfo()->fx > p2->fx)
				{
					*pX *= -1;
				}
			}
		}		

		if (fWidth < fSizeX && fHeight < fSizeY)
			return true;
	}

	return false;
}

bool CCollisitionMgr::RopeCollision(void)
{
	/*
	OBJITER iter_map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_map_end = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();

	CObj* pMap = NULL;

	for (iter_map; iter_map != iter_map_end; ++iter_map)
	{
		if (((CStage1_Map*)(*iter_map))->GetBgType() == BG_MAP)
		{
			pMap = (*iter_map);
		}
	}

	CObj* pPlayer = GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->front();
	*/
	CObj * pPlayer = GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->front();
	
	OBJITER iter_map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_map_end = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();
	
	CObj* pMap = NULL;

	for (iter_map; iter_map != iter_map_end; ++iter_map) {
		if (((CStage1_Map*)(*iter_map))->GetBgType() == BG_MAP) {
			pMap = (*iter_map);
		}
	}

	RECT rc;
	if ((IntersectRect(&rc, pPlayer->GetRect(), &((CStage1_Map*)(pMap))->GetRope())) == true) {
		return true;
	}

	return false;
}

bool CCollisitionMgr::OverTileCollision(CObj * p1, CObj * p2, float * pX, float * pY, float _fTempY)
{

	CStage1_Map* pMap = ((CStage1_Map*)(p2));

	float fWidth = abs(p1->GetInfo()->fx - pMap->GetOverTileInfo().fx - g_fScrollX);
	float fHeight = abs(p1->GetInfo()->fy - pMap->GetOverTileInfo().fy - g_fScrollY - _fTempY);

	float fSizeX = p1->GetInfo()->fcx / 2 + pMap->GetOverTileInfo().fcx / 2;
	float fSizeY = p1->GetInfo()->fcy / 2 + pMap->GetOverTileInfo().fcy / 2;
	
	if (pX != NULL && pY != NULL)
	{
		*pX = abs(fSizeX - fWidth);
		*pY = abs(fSizeY - fHeight);

		if (*pX > *pY)
		{
			if (p1->GetRect()->bottom <= pMap->GetOverTIleRect().top)	//충돌 했을 때
			{
				//p1->GetInfo()->fy = pMap->GetOverTileInfo().fy + g_fScrollY;
			}
		}

		cout << p1->GetInfo()->fy << endl;
		cout << pMap->GetOverTileInfo().fy + g_fScrollY << endl;

		if (fWidth < fSizeX && fHeight < fSizeY)
			return true;
	}
	/*
	float fWidth = abs(p1->GetInfo()->fx - p2->fx - g_fScrollX);
	float fHeight = abs(p1->GetInfo()->fy - p2->fy - g_fScrollY - _fTempY);

	float fSizeX = p1->GetInfo()->fcx / 2 + p2->fcx / 2;
	float fSizeY = p1->GetInfo()->fcy / 2 + p2->fcy / 2;

	if (p2->iOption == 1)
	{
		if (pX != NULL && pY != NULL)
		{
			*pX = abs(fSizeX - fWidth);
			*pY = abs(fSizeY - fHeight);

			if (*pX > *pY)
			{
				//아래서 온 충돌
				if (p1->GetInfo()->fy > p2->fy)
				{
					*pY *= -1;
				}
			}
			else
			{
				if (p1->GetInfo()->fx > p2->fx)
				{
					*pX *= -1;
				}
			}
		}

		if (fWidth < fSizeX && fHeight < fSizeY)
			return true;
	}
	*/

	return false;
}


