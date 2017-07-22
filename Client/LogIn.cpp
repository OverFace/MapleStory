#include "stdafx.h"
#include "LogIn.h"
#include "ObjMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "LogIn_Back.h"

CLogIn::CLogIn(void)
{
	m_bLogin_Check = false;
	m_pLogin = NULL;
}

CLogIn::~CLogIn(void)
{
	Release();
}

void CLogIn::Initialize(void)
{
	GETS(CBitMapMgr)->LoadImageByScene(SCENE_LOGIN);

	m_pLogin = new CLogin_Back;
	m_pLogin->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_BACKGROUND, m_pLogin);

	m_bLogin_Check = true;
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
