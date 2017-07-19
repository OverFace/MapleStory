#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "Logo_Back.h"

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_LOGO);

	//Back Ground Object
	CObj* pObj = new CLogo_Back;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
}

int CLogo::Update(void)
{
	if (GETS(CKeyMgr)->GetKeyDown(VK_RETURN))
	{
		GETS(CSceneMgr)->SetScene(SCENE_EDIT);
		return 1;
	}	

	GETS(CObjMgr)->Update();

	return 0;
}

void CLogo::Render(HDC _dc)
{	
	GETS(CObjMgr)->Render(_dc);
}

void CLogo::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
}
