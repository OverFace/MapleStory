#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"

//Stage Header Include
//--------------------------------------
#include "Logo.h"
#include "Stage1.h"
#include "Edit.h"
#include "LogIn.h"
//--------------------------------------

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr(void)
	: m_pScene(NULL), m_pNextScene(NULL)
{
	m_bChangeScene = false;
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
		break;
	case SCENE_SGININ:
		
		break;
	case SCENE_LOGIN:
		m_pNextScene = new CLogIn();
		break;
	case SCENE_PLAYERSELECT:

		break;
	case SCENE_STAGE1:
		m_pNextScene = new CStage1();
		break;
	case SCENE_STAGE2:

		break;
	case SCENE_STAGE3:

		break;
	case SCENE_EDIT:
		m_pNextScene = new CEdit();
		break;
	case SCENE_BOSS:

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
