#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "Logo.h"
#include "Player.h"

CMainGame::CMainGame(void)
{
	m_DC = GetDC(g_hWnd);
	m_dwFrameTime = GetTickCount();
	m_iFps = 0;

	lstrcpy(m_szFrameBuf, L"FPS : 0");

	//Consol Ã¢ ¶ç¿ì±â
#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
#endif
}

CMainGame::~CMainGame(void)
{
	Release();
	FreeConsole();
}

void CMainGame::Initialize(void)
{
	//Init Sound
	GETS(CSoundMgr)->Initialize();
	GETS(CSoundMgr)->LoadSoundFile();

	//Scene Logo
	GETS(CSceneMgr)->SetScene(SCENE_LOGO);
	m_pPlayer = new CPlayer;
	m_pPlayer->Initialize();
}

int CMainGame::Update(void)
{
	m_pPlayer->Update();

	//Scene Mgr Update
	GETS(CSceneMgr)->Update();

	return 0;
}

void CMainGame::Render(void)
{
	//Back Buffer Image Render
	HDC BackDC = GETS(CBitMapMgr)->FindImage(L"BackBuffer")->GetMemDC();
	m_pPlayer->Render(BackDC);
	
	//Scene Mgr Render
	GETS(CSceneMgr)->Render(BackDC);

	//Frame Redner
	++m_iFps;
	if (m_dwFrameTime + 1000 < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		wsprintf(m_szFrameBuf, L"FPS : %d", m_iFps);
		m_iFps = 0;
	}	
	TextOut(BackDC, 960, 20, m_szFrameBuf, lstrlen(m_szFrameBuf));

	//BackBuffer
	//if (typeid(*CSceneMgr::GetInstance()->GetCurrentScene()).name() == typeid(CLogo).name())
		//return;

	BitBlt(m_DC, 0, 0, WINCX, WINCY, BackDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	GETS(CObjMgr)->DestroyInstance();
	GETS(CSceneMgr)->DestroyInstance();
	GETS(CBitMapMgr)->DestroyInstance();
	GETS(CSoundMgr)->DestroyInstance();
}
