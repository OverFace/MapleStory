#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "CollisitionMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "Stage1_Back.h"
#include "Stage1_Map.h"
#include "Player.h"
#include "Slim.h"

//Npc
//-------------------------------------
#include "Store_Npc.h"
//-------------------------------------
//UI
//-------------------------------------
#include "Store.h"
#include "Status.h"
#include "Inven.h"
#include "Equip.h"
#include "Skill.h"
#include "Skill_Input.h"
#include "Stat.h"
#include "HpBar.h"
#include "MpBar.h"
#include "ExpBar.h"
//-------------------------------------

CStage1::CStage1(void)
{
	m_pMap = NULL;
	m_pPlayer = NULL;
	m_bCollisiton_Check = false;
}

CStage1::~CStage1(void)
{
	Release();
}

void CStage1::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_STAGE1);

	//Stage1 Back Object Create
	CObj* pObj = new CStage1_Back();
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
	((CStage1_Back*)pObj)->SetRedner(true);

	//Stage1 Map Object Create
	pObj = new CStage1_Map();
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
	((CStage1_Map*)pObj)->SetRedner(true);

	//Player
	pObj = new CPlayer;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_PLAYER, pObj);

	//Monster
	pObj = new CSlim;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_MONSTER, pObj);

	//Store
	CObj* pStore = new CStore;
	pStore->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pStore);

	//NPC
	pObj = new CStore_Npc(pStore);
	pObj->Initialize();
	pObj->SetPos(WINCX / 2 + 600.f, WINCY / 2 + 305.f);
	GETS(CObjMgr)->AddObject(OBJ_NPC, pObj);

	//UI
	//---------------------------------------------------------------------
	//Status
	pObj = new CStatus;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Equip
	pObj = new CEquip;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Inven
	pObj = new CInven;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Skill
	CObj* pSkill = new CSkill_UI;
	pSkill->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pSkill);
	pObj = new CSkill_Input(*(pSkill->GetInfo()));
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Stat
	pObj = new CStat;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Hp_Bar
	pObj = new CHpBar;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Mp_Bar
	pObj = new CMpBar;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Exp_Bar
	pObj = new CExpBar;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//---------------------------------------------------------------------
}

int CStage1::Update(void)
{
	GETS(CObjMgr)->Update();

	//Stage1_Tile Check
	Stage1_TileCheck();
	//OverTile_Check();

	//Rope Check
	Rope_Check();

	return 0;
}

void CStage1::Render(HDC _dc)
{
	GETS(CObjMgr)->Render(_dc);
}

void CStage1::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
}

void CStage1::Stage1_TileCheck(void)
{
	//Stage1 Tile
	OBJITER iter_Map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_Map_End = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();

	for (iter_Map; iter_Map != iter_Map_End; ++iter_Map)
	{
		if (((CStage1_Map*)(*iter_Map))->GetBgType() == BG_MAP)
			m_pMap = (*iter_Map);
	}

	TILEITER iter_Tile = ((CStage1_Map*)m_pMap)->GetStage1_Tile()->begin();
	TILEITER iter_Tile_End = ((CStage1_Map*)m_pMap)->GetStage1_Tile()->end();

	//Player
	m_pPlayer = GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->front();

	//Coliistion value
	float fx = 0.f;
	float fy = 0.f;

	for (iter_Tile; iter_Tile != iter_Tile_End; ++iter_Tile)
	{
		if (GETS(CCollisitionMgr)->TileCollision(m_pPlayer, (*iter_Tile), &fx, &fy, 20.f) == true)
		{
			if (fx > fy)
				m_pPlayer->GetInfo()->fy -= fy;
			else
				m_pPlayer->GetInfo()->fx -= fx;

			m_bCollisiton_Check = true;
		}
		else
		{
			m_bCollisiton_Check = false;
		}
	}	
}

void CStage1::Rope_Check(void)
{
	bool bCheck = false;

	bCheck = GETS(CCollisitionMgr)->RopeCollision();

	CObj* pPlayer = GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->front();

	((CPlayer*)pPlayer)->SetRope_Check(bCheck);
}

void CStage1::OverTile_Check(void)
{
	//Stage1 Tile
	OBJITER iter_Map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_Map_End = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();

	for (iter_Map; iter_Map != iter_Map_End; ++iter_Map)
	{
		if (((CStage1_Map*)(*iter_Map))->GetBgType() == BG_MAP)
			m_pMap = (*iter_Map);
	}

	//Player
	m_pPlayer = GETS(CObjMgr)->GetObjList(OBJ_PLAYER)->front();

	//Tile
	TILEITER iter_Tile = ((CStage1_Map*)m_pMap)->GetStage1_Tile()->begin();
	TILEITER iter_Tile_End = ((CStage1_Map*)m_pMap)->GetStage1_Tile()->end();
	
	float fx = 0.f, fy = 0.f;

	for (iter_Tile; iter_Tile != iter_Tile_End; ++iter_Tile)
	{
		if (GETS(CCollisitionMgr)->OverTileCollision(m_pPlayer, *iter_Tile, &fx, &fy, -40.f) == true)
		{
			//if (fx > fy)
				m_pPlayer->GetInfo()->fy -= fy;

			m_bCollisiton_Check = true;
		}
		else
		{
			m_bCollisiton_Check = false;
		}
	}
}
