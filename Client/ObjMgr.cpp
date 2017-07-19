#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr(void)
{

}

CObjMgr::~CObjMgr(void)
{
	Release();
}

inline bool CObjMgr::Compare(CObj* pDest, CObj* pSour)
{
	return pDest->GetInfo()->fy < pSour->GetInfo()->fy;
}

void CObjMgr::AddObject(eObjType eType, CObj * pObj)
{
	m_ObjList[eType].push_back(pObj);
}

list<CObj*>* CObjMgr::GetObjList(eObjType eType)
{
	return &m_ObjList[eType];
}

void CObjMgr::Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();

		for (iter; iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == 1)
			{
				delete *iter;
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Render(HDC _dc)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();
		OBJITER iter_End = m_ObjList[i].end();

		for (; iter != iter_End; ++iter)
		{
			m_vecRender[(*iter)->GetRenderType()].push_back((*iter));
		}
	}

	//Sort
	sort(m_vecRender[RENDER_WORLDOBJ].begin(), m_vecRender[RENDER_WORLDOBJ].end(), CObjMgr::Compare);

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		for (int j = 0, iCnt = m_vecRender[i].size(); j < iCnt; ++j)
		{
			m_vecRender[i][j]->Render(_dc);
		}
		m_vecRender[i].clear();
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		OBJITER iter = m_ObjList[i].begin();

		for (iter; iter != m_ObjList[i].end(); ++iter)
		{
			delete *iter;
		}
		m_ObjList[i].clear();
	}
}

