#include "stdafx.h"
#include "Stage2.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "CollisitionMgr.h"
#include "ObjMgr.h"
#include "Stage2_Map.h"
#include "Player.h"

//UI
//-------------------------------------
#include "Status.h"
#include "Inven.h"
#include "Equip.h"
#include "Skill.h"
#include "Store.h"
#include "Stat.h"
#include "HpBar.h"
#include "MpBar.h"
#include "ExpBar.h"
//-------------------------------------

CStage2::CStage2(void)
{
}

CStage2::~CStage2(void)
{
	Release();
}

void CStage2::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_STAGE2);

	//Stage2 Map Object Create
	CObj* pObj = new CStage2_Map();
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
	((CStage2_Map*)pObj)->SetRedner(true);

	//Player
	pObj = new CPlayer;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_PLAYER, pObj);
	
	//UI
	//---------------------------------------------------------------------
	//Status
	pObj = new CStatus;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Inven
	pObj = new CInven;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Equip
	pObj = new CEquip;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pObj);
	//Skill
	CObj* pSkill = new CSkill_UI;
	pSkill->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, pSkill);
	//Store
	pObj = new CStore;
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

int CStage2::Update(void)
{
	GETS(CObjMgr)->Update();

	//Stage2_Tile Check
	Stage2_TileCheck();

	return 0;
}

void CStage2::Render(HDC _dc)
{
	GETS(CObjMgr)->Render(_dc);
}

void CStage2::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
}

void CStage2::Stage2_TileCheck(void)
{
	//Stage2 Tile
	OBJITER iter_Map = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->begin();
	OBJITER iter_Map_End = GETS(CObjMgr)->GetObjList(OBJ_BACKGROUND)->end();
	for (iter_Map; iter_Map != iter_Map_End; ++iter_Map)
	{
		if (((CStage2_Map*)(*iter_Map))->GetBgType() == BG_MAP)
			m_pMap = (*iter_Map);
	}

	TILEITER iter_Tile = ((CStage2_Map*)m_pMap)->GetStage2_Tile()->begin();
	TILEITER iter_Tile_End = ((CStage2_Map*)m_pMap)->GetStage2_Tile()->end();

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