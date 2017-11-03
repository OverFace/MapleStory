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
	map<const TCHAR*, CBitMap*>::iterator iter = m_MapBit.begin();
	
	//const TCHAR* 형이라서 못찾는 경우가 생긴다.
	//그래서 STRCOMPARE에서 비교, find_if로 찾아준다.
	iter = find_if(iter, m_MapBit.end(), STRCOMPARE(pKey));
	
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
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");

		//Monster Slim
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Monster/Slim/SlimL.bmp", L"Slim_L");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Monster/Slim/SlimR.bmp", L"Slim_R");
		
		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Etc.bmp", L"Inventory_Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Equip.bmp", L"Inventory_Equip");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Consume.bmp", L"Inventory_Consume");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		//UI_Button
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton1.bmp", L"Button_Plus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton2.bmp", L"Button_Minus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/XButton.bmp", L"Button_Esc");
		//UI_Scroll
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Scroll.bmp", L"UI_Scroll");
		//Npc
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/NPC/Npc_Store.bmp", L"Store_Npc");
#pragma region Item Resource
		//Item_Accessory
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory.bmp", L"Accessory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory1.bmp", L"Accessory1");
		//Item_Armor
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor.bmp", L"Armor");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor1.bmp", L"Armor1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor2.bmp", L"Armor2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor3.bmp", L"Armor3");
		//Item_Etc
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc.bmp", L"Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc1.bmp", L"Etc1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc2.bmp", L"Etc2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc3.bmp", L"Etc3");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc4.bmp", L"Etc4");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc5.bmp", L"Etc5");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc6.bmp", L"Etc6");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc7.bmp", L"Etc7");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc8.bmp", L"Etc8");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc9.bmp", L"Etc9");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc10.bmp", L"Etc10");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc11.bmp", L"Etc11");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc12.bmp", L"Etc12");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc13.bmp", L"Etc13");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc14.bmp", L"Etc14");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc15.bmp", L"Etc15");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc16.bmp", L"Etc16");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc17.bmp", L"Etc17");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc18.bmp", L"Etc18");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc19.bmp", L"Etc19");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc20.bmp", L"Etc20");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc21.bmp", L"Etc21");
		//Item_Glove
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove.bmp", L"Glove");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove1.bmp", L"Glove1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove2.bmp", L"Glove2");
		//Item_Helmet
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Helmet/Helmet.bmp", L"Helmet");
		//Item_Messo
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Messo/Messo.bmp", L"Messo");
		//Item_Pants
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Pants/Pants.bmp", L"Pants");
		//Item_Potion
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion.bmp", L"Hp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion.bmp", L"Mp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion_Nothing.bmp", L"Mp_Potion_Nothing");
		//Item_Shoes
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes.bmp", L"Shoes");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes1.bmp", L"Shoes1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes2.bmp", L"Shoes2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes3.bmp", L"Shoes3");
		//Item_Weapon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon.bmp", L"Weapon");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon1.bmp", L"Weapon1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon2.bmp", L"Weapon2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon3.bmp", L"Weapon3");
#pragma endregion

#pragma region Skill_Icon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_On.bmp", L"MeanStrike_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_Off.bmp", L"MeanStrike_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_On.bmp", L"Blot_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_Off.bmp", L"Blot_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_On.bmp", L"Ascension_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_Off.bmp", L"Ascension_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_On.bmp", L"Annihilation_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_Off.bmp", L"Annihilation_Icon_Off");
#pragma endregion
	break;
	case SCENE_STAGE2:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box2(62).bmp", L"Tile_62");
		
		//Stage2 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage2_Field.bmp", L"Stage2_Map");

		//Player
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_LEFT.bmp", L"Player_Left");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");

		//Monster Slim
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Monster/Slim/SlimL.bmp", L"Slim_L");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Monster/Slim/SlimR.bmp", L"Slim_R");

		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Etc.bmp", L"Inventory_Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Equip.bmp", L"Inventory_Equip");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Consume.bmp", L"Inventory_Consume");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		//UI_Button
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton1.bmp", L"Button_Plus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton2.bmp", L"Button_Minus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/XButton.bmp", L"Button_Esc");
		//UI_Scroll
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Scroll.bmp", L"UI_Scroll");
#pragma region Item Resource
		//Item_Accessory
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory.bmp", L"Accessory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory1.bmp", L"Accessory1");
		//Item_Armor
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor.bmp", L"Armor");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor1.bmp", L"Armor1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor2.bmp", L"Armor2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor3.bmp", L"Armor3");
		//Item_Etc
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc.bmp", L"Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc1.bmp", L"Etc1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc2.bmp", L"Etc2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc3.bmp", L"Etc3");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc4.bmp", L"Etc4");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc5.bmp", L"Etc5");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc6.bmp", L"Etc6");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc7.bmp", L"Etc7");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc8.bmp", L"Etc8");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc9.bmp", L"Etc9");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc10.bmp", L"Etc10");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc11.bmp", L"Etc11");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc12.bmp", L"Etc12");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc13.bmp", L"Etc13");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc14.bmp", L"Etc14");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc15.bmp", L"Etc15");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc16.bmp", L"Etc16");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc17.bmp", L"Etc17");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc18.bmp", L"Etc18");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc19.bmp", L"Etc19");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc20.bmp", L"Etc20");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc21.bmp", L"Etc21");
		//Item_Glove
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove.bmp", L"Glove");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove1.bmp", L"Glove1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove2.bmp", L"Glove2");
		//Item_Helmet
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Helmet/Helmet.bmp", L"Helmet");
		//Item_Messo
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Messo/Messo.bmp", L"Messo");
		//Item_Pants
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Pants/Pants.bmp", L"Pants");
		//Item_Potion
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion.bmp", L"Hp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion.bmp", L"Mp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		//Item_Shoes
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes.bmp", L"Shoes");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes1.bmp", L"Shoes1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes2.bmp", L"Shoes2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes3.bmp", L"Shoes3");
		//Item_Weapon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon.bmp", L"Weapon");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon1.bmp", L"Weapon1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon2.bmp", L"Weapon2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon3.bmp", L"Weapon3");
#pragma endregion

#pragma region Skill_Icon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_On.bmp", L"MeanStrike_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_Off.bmp", L"MeanStrike_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_On.bmp", L"Blot_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_Off.bmp", L"Blot_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_On.bmp", L"Ascension_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_Off.bmp", L"Ascension_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_On.bmp", L"Annihilation_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_Off.bmp", L"Annihilation_Icon_Off");
#pragma endregion
		break;
	case SCENE_STAGE3:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3(58).bmp", L"Tile_58");

		//Stage3 Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage3_Field.bmp", L"Stage3_Map");
	
		//Player
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_LEFT.bmp", L"Player_Left");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");

		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Etc.bmp", L"Inventory_Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Equip.bmp", L"Inventory_Equip");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Consume.bmp", L"Inventory_Consume");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		//UI_Button
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton1.bmp", L"Button_Plus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton2.bmp", L"Button_Minus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/XButton.bmp", L"Button_Esc");
		//UI_Scroll
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Scroll.bmp", L"UI_Scroll");
#pragma region Item Resource
		//Item_Accessory
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory.bmp", L"Accessory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory1.bmp", L"Accessory1");
		//Item_Armor
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor.bmp", L"Armor");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor1.bmp", L"Armor1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor2.bmp", L"Armor2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor3.bmp", L"Armor3");
		//Item_Etc
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc.bmp", L"Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc1.bmp", L"Etc1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc2.bmp", L"Etc2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc3.bmp", L"Etc3");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc4.bmp", L"Etc4");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc5.bmp", L"Etc5");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc6.bmp", L"Etc6");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc7.bmp", L"Etc7");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc8.bmp", L"Etc8");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc9.bmp", L"Etc9");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc10.bmp", L"Etc10");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc11.bmp", L"Etc11");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc12.bmp", L"Etc12");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc13.bmp", L"Etc13");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc14.bmp", L"Etc14");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc15.bmp", L"Etc15");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc16.bmp", L"Etc16");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc17.bmp", L"Etc17");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc18.bmp", L"Etc18");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc19.bmp", L"Etc19");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc20.bmp", L"Etc20");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc21.bmp", L"Etc21");
		//Item_Glove
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove.bmp", L"Glove");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove1.bmp", L"Glove1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove2.bmp", L"Glove2");
		//Item_Helmet
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Helmet/Helmet.bmp", L"Helmet");
		//Item_Messo
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Messo/Messo.bmp", L"Messo");
		//Item_Pants
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Pants/Pants.bmp", L"Pants");
		//Item_Potion
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion.bmp", L"Hp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion.bmp", L"Mp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		//Item_Shoes
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes.bmp", L"Shoes");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes1.bmp", L"Shoes1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes2.bmp", L"Shoes2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes3.bmp", L"Shoes3");
		//Item_Weapon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon.bmp", L"Weapon");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon1.bmp", L"Weapon1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon2.bmp", L"Weapon2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon3.bmp", L"Weapon3");
#pragma endregion

#pragma region Skill_Icon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_On.bmp", L"MeanStrike_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_Off.bmp", L"MeanStrike_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_On.bmp", L"Blot_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_Off.bmp", L"Blot_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_On.bmp", L"Ascension_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_Off.bmp", L"Ascension_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_On.bmp", L"Annihilation_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_Off.bmp", L"Annihilation_Icon_Off");
#pragma endregion
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
	case SCENE_EDIT_LINE:
		//Stage1 BackGround & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_BackGround.bmp", L"Stage1_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Ereve_Field.bmp", L"Stage1_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage2_Field.bmp", L"Stage2_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Stage3_Field.bmp", L"Stage3_Map");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Back.bmp", L"Boss_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Field.bmp", L"Boss_Map");
		break;
	case SCENE_BOSS:
		//Tile Image
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Tile/Box3(63).bmp", L"Tile_63");

		//Boss Stage Back & Map
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Back.bmp", L"Boss_Back");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Stage/Boss_Stage_Field.bmp", L"Boss_Map");
		
		//Player
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_LEFT.bmp", L"Player_Left");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_RIGHT.bmp", L"Player_Right");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Player/Player_UP.bmp", L"Player_Up");

		//UI
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/StateBar.bmp", L"Status");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Equipment.bmp", L"Equipment");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/ExpBar.bmp", L"Exp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/HPBar.bmp", L"Hp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/MPBar.bmp", L"Mp_Bar");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Etc.bmp", L"Inventory_Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Equip.bmp", L"Inventory_Equip");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Inventory_Consume.bmp", L"Inventory_Consume");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Shop.bmp", L"Store");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill.bmp", L"Skill");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Skill_Input.bmp", L"Skill_Input");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Stat.bmp", L"Stat");
		//UI_Button
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton1.bmp", L"Button_Plus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/Botton2.bmp", L"Button_Minus");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Button/XButton.bmp", L"Button_Esc");
		//UI_Scroll
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/UI/Scroll.bmp", L"UI_Scroll");
#pragma region Item Resource
		//Item_Accessory
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory.bmp", L"Accessory");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Accessory/Accessory1.bmp", L"Accessory1");
		//Item_Armor
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor.bmp", L"Armor");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor1.bmp", L"Armor1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor2.bmp", L"Armor2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Armor/Armor3.bmp", L"Armor3");
		//Item_Etc
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc.bmp", L"Etc");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc1.bmp", L"Etc1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc2.bmp", L"Etc2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc3.bmp", L"Etc3");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc4.bmp", L"Etc4");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc5.bmp", L"Etc5");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc6.bmp", L"Etc6");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc7.bmp", L"Etc7");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc8.bmp", L"Etc8");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc9.bmp", L"Etc9");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc10.bmp", L"Etc10");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc11.bmp", L"Etc11");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc12.bmp", L"Etc12");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc13.bmp", L"Etc13");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc14.bmp", L"Etc14");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc15.bmp", L"Etc15");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc16.bmp", L"Etc16");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc17.bmp", L"Etc17");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc18.bmp", L"Etc18");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc19.bmp", L"Etc19");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc20.bmp", L"Etc20");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Etc/Etc21.bmp", L"Etc21");
		//Item_Glove
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove.bmp", L"Glove");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove1.bmp", L"Glove1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Glove/Glove2.bmp", L"Glove2");
		//Item_Helmet
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Helmet/Helmet.bmp", L"Helmet");
		//Item_Messo
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Messo/Messo.bmp", L"Messo");
		//Item_Pants
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Pants/Pants.bmp", L"Pants");
		//Item_Potion
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion.bmp", L"Hp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion.bmp", L"Mp_Potion");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Hp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Potion/Mp_Potion_Nothing.bmp", L"Hp_Potion_Nothing");
		//Item_Shoes
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes.bmp", L"Shoes");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes1.bmp", L"Shoes1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes2.bmp", L"Shoes2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Shoes/Shoes3.bmp", L"Shoes3");
		//Item_Weapon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon.bmp", L"Weapon");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon1.bmp", L"Weapon1");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon2.bmp", L"Weapon2");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Item/Weapon/Weapon3.bmp", L"Weapon3");
#pragma endregion

#pragma region Skill_Icon
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_On.bmp", L"MeanStrike_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/MeanStrike/Icon/MeanStrike_Off.bmp", L"MeanStrike_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_On.bmp", L"Blot_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Blot/Icon/Blot_Off.bmp", L"Blot_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_On.bmp", L"Ascension_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Ascension/Icon/Ascension_Off.bmp", L"Ascension_Icon_Off");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_On.bmp", L"Annihilation_Icon_On");
		GETS(CBitMapMgr)->LoadImage(L"../Resource/Texture/Skill/Annihilation/Icon/Annihilation_Off.bmp", L"Annihilation_Icon_Off");
#pragma endregion
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
