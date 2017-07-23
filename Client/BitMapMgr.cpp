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
	GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/BackBuffer/BackBuffer.bmp", L"BackBuffer");

	switch(eType)
	{
	case SCENE_LOGO:
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Logo.bmp", L"Logo");
		break;
	case SCENE_SGININ:
		
		break;
	case SCENE_LOGIN:

		break;
	case SCENE_PLAYERSELECT:

		break;
	case SCENE_STAGE1:
		//Stage1 BackGround & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_BackGround.bmp", L"Stage1_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_Field.bmp", L"Stage1_Map");

		//Player
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_LEFT.bmp", L"Player_Left");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");
		break;
	case SCENE_STAGE2:
		//Stage2 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage2_Field.bmp", L"Stage2_Map");
		break;
	case SCENE_STAGE3:
		//Stage3 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage3_Field.bmp", L"Stage3_Map");
		break;
	case SCENE_EDIT:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box1.bmp", L"Tile1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box2.bmp", L"Tile2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3.bmp", L"Tile3");

		//Stage1 BackGround & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_BackGround.bmp", L"Stage1_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_Field.bmp", L"Stage1_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage2_Field.bmp", L"Stage2_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage3_Field.bmp", L"Stage3_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Back.bmp", L"Boss_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Field.bmp", L"Boss_Map");
		break;
	case SCENE_BOSS:
		//Boss Stage Back & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Back.bmp", L"Boss_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Field.bmp", L"Boss_Map");
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
