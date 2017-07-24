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
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Login_Back.bmp", L"Login");
		break;
	case SCENE_PLAYERSELECT:

		break;
	case SCENE_STAGE1:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box1.bmp", L"Tile1");

		//Stage1 BackGround & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_BackGround.bmp", L"Stage1_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_Field.bmp", L"Stage1_Map");

		//Player
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_LEFT.bmp", L"Player_Left");
		//GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		//GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");
		
		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory.bmp", L"Inventory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		break;
	case SCENE_STAGE2:
		//Stage2 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage2_Field.bmp", L"Stage2_Map");

		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory.bmp", L"Inventory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		break;
	case SCENE_STAGE3:
		//Stage3 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage3_Field.bmp", L"Stage3_Map");
	
		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory.bmp", L"Inventory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		break;
	case SCENE_EDIT:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box1.bmp", L"Tile1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box2.bmp", L"Tile2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3.bmp", L"Tile3");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box2(62).bmp", L"Tile_62");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3(55).bmp", L"Tile_55");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3(58).bmp", L"Tile_58");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3(63).bmp", L"Tile_63");

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
		
		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory.bmp", L"Inventory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
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
