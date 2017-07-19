#include "stdafx.h"
#include "Scene.h"
#include "BitMapMgr.h"

CScene::CScene(void)
{
}

CScene::~CScene(void)
{
	//BitMapMgr Destory
	GETS(CBitMapMgr)->DestroyInstance();
}
