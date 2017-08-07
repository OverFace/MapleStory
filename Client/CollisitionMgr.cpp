#include "stdafx.h"
#include "CollisitionMgr.h"
#include "Obj.h"

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


