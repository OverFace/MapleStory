#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "Stage1_Back.h"
#include "Stage1_Map.h"

CStage1::CStage1(void)
{
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

	//Stage1 Map Object Create
	pObj = new CStage1_Map();
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
}

int CStage1::Update(void)
{
	GETS(CObjMgr)->Update();

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
