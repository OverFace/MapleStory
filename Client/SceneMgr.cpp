#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
//Stage Header Include
//--------------------------------------
#include "Logo.h"
#include "Edit.h"
#include "LineTool.h"
#include "LogIn.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Boss_Stage.h"
//--------------------------------------

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
	: m_pScene(NULL), m_pNextScene(NULL)
{
	m_bChangeScene = false;
	m_eSceneType = SCENE_END;
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

const CScene * CSceneMgr::GetCurrentScene(void)
{
	return m_pScene;
}

void CSceneMgr::SetScene(eSceneType eType)
{
	switch (eType)
	{
	case SCENE_LOGO:
		m_pNextScene = new CLogo();
		m_eSceneType = SCENE_LOGO;
		break;
	case SCENE_SGININ:
		m_eSceneType = SCENE_SGININ;
		break;
	case SCENE_LOGIN:
		m_pNextScene = new CLogIn();
		m_eSceneType = SCENE_LOGIN;
		break;
	case SCENE_PLAYERSELECT:
		m_eSceneType = SCENE_PLAYERSELECT;
		break;
	case SCENE_STAGE1:
		m_pNextScene = new CStage1();
		m_eSceneType = SCENE_STAGE1;
		break;
	case SCENE_STAGE2:
		m_pNextScene = new CStage2();
		m_eSceneType = SCENE_STAGE2;
		break;
	case SCENE_STAGE3:
		m_pNextScene = new CStage3();
		m_eSceneType = SCENE_STAGE3;
		break;
	case SCENE_EDIT:
		m_pNextScene = new CEdit();
		m_eSceneType = SCENE_EDIT;
		break;
	case SCENE_EDIT_LINE:
		m_pNextScene = new CLine_Tool();
		m_eSceneType = SCENE_EDIT_LINE;
		break;
	case SCENE_BOSS:
		m_pNextScene = new CBoss_Stage();
		m_eSceneType = SCENE_BOSS;
		break;
	}

	if (m_pScene == NULL)
	{
		m_pScene = m_pNextScene;
		m_pScene->Initialize();
	}
	else
	{
		m_bChangeScene = true;
	}
}
int CSceneMgr::Update(void)
{
	return m_pScene->Update();
}

void CSceneMgr::Render(HDC _dc)
{
	if (m_bChangeScene == true)
	{
		delete m_pScene;
		m_pScene = m_pNextScene;
		m_pScene->Initialize();
		m_bChangeScene = false;
	}

	m_pScene->Render(_dc);
}

void CSceneMgr::Release(void)
{
	if (m_pScene != NULL)
	{
		SAFE_DELETE(m_pScene);
	}
}