#include "stdafx.h"
#include "CollisitionMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Player.h"
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

bool CCollisitionMgr::OverTileCollision(CObj * p1, TILE * p2, float * pX, float * pY, float _fTempY)
{
	/*
	Ÿ�� �浹 �̿ϼ�......
	*/
	
	if (p2->iOption == 2)
	{
		float fHeight = abs(p1->GetInfo()->fy - p2->fy - g_fScrollY + 20);
		float fSizeY = p1->GetInfo()->fcy / 2 + p2->fcy / 2;

		if (pX != NULL && pY != NULL)
		{
			*pY = abs(fSizeY - fHeight);

			/*
			if (*pX > *pY)
			{
				if (p1->GetRect()->bottom <= pMap->GetOverTIleRect().top)	//�浹 ���� ��
				{
					((CPlayer*)p1)->SetRope_CollStop(true);		//���� �浹 ���߱�

					//overtile Ÿ��
					//p1->GetInfo()->fy = pMap->GetOverTileInfo().fy + g_fScrollY;
					//*pY *= -1;
				}
			}
			*/

			static bool bCheck = false;

			if (p1->GetInfo()->fy < p2->fy + g_fScrollY + _fTempY)
			{
				((CPlayer*)p1)->SetRope_CollStop(true);		//�����浹 ���߱�
				*pY *= -1;
				bCheck = true;
			}
						
			if (bCheck == true)
			{
				if (fHeight < fSizeY)
					return true;
			}			
		}
	}

	return false;
}


