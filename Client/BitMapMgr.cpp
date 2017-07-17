#include "stdafx.h"
#include "BitMapMgr.h"
#include "BitMap.h"

IMPLEMENT_SINGLETON(CBitMapMgr)

CBitMapMgr::CBitMapMgr(void)
{

}

CBitMapMgr::~CBitMapMgr(void)
{
	Release();
}

void CBitMapMgr::Initialize(void)
{

}

void CBitMapMgr::LoadImage(const TCHAR * pFileName, const TCHAR * pKey)
{
	CBitMap* pBitMap = new CBitMap;
	pBitMap->LoadBmp(pFileName);
	m_MapBit.insert(map<const TCHAR*, CBitMap*>::value_type(pKey, pBitMap));
}

CBitMap * CBitMapMgr::FindImage(const TCHAR * pKey)
{
	map<const TCHAR*, CBitMap*>::iterator iter = m_MapBit.find(pKey);

	if (iter == m_MapBit.end())
		return NULL;

	return iter->second;
}

void CBitMapMgr::LoadImageByScene(eSceneType eType)
{
	switch(eType)
	{
	case SCENE_LOGO:

		break;
	case SCENE_SGININ:

		break;
	case SCENE_LOGIN:

		break;
	case SCENE_PLAYERSELECT:

		break;
	case SCENE_STAGE1:

		break;
	case SCENE_STAGE2:

		break;
	case SCENE_STAGE3:

		break;
	case SCENE_BOSS:

		break;
	}
}

void CBitMapMgr::Release(void)
{
	map<const TCHAR*, CBitMap*>::iterator iter = m_MapBit.begin();
	
	for (iter; iter != m_MapBit.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_MapBit.clear();
}
