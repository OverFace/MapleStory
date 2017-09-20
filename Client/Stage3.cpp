#include "stdafx.h"
#include "Stage3.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "ObjMgr.h"
#include "Stage3_Map.h"
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

CStage3::CStage3(void)
{
}

CStage3::~CStage3(void)
{
	Release();
}

void CStage3::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_STAGE3);

	//Stage3 Map Object Create
	CObj* pObj = new CStage3_Map();
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
	((CStage3_Map*)pObj)->SetRedner(true);

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

int CStage3::Update(void)
{
	GETS(CObjMgr)->Update();

	return 0;
}

void CStage3::Render(HDC _dc)
{
	GETS(CObjMgr)->Render(_dc);
}

void CStage3::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
}
