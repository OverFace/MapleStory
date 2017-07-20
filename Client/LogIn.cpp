#include "stdafx.h"
#include "LogIn.h"
#include "ObjMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "LogIn_Back.h"

CLogIn::CLogIn(void)
{
}

CLogIn::~CLogIn(void)
{
	Release();
}

void CLogIn::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_LOGIN);

	CObj* pObj = new CLogin_Back;
	pObj->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, pObj);
}

int CLogIn::Update(void)
{
	GETS(CObjMgr)->Update();

	return 0;
}

void CLogIn::Render(HDC _dc)
{
	GETS(CObjMgr)->Render(_dc);
}

void CLogIn::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
}
