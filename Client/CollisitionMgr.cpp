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
	fTempY : ScrollY �� ����ÿ� Ÿ�Ϻ��� ���� �÷��̾ �� �����Ƿ�
	         �� ���� �ٴڿ� �°� ���� �ֱ� ���ؼ� �ִ� Y ��.
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
				//�Ʒ��� �� �浹
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


