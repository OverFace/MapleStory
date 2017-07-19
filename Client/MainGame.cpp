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

CMainGame::CMainGame(void)
{
	m_DC = GetDC(g_hWnd);
	m_dwFrameTime = GetTickCount();
	m_iFps = 0;

	lstrcpy(m_szFrameBuf, L"FPS : 0");

	//Consol 창 띄우기
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
}

int CMainGame::Update(void)
{
	//Scene Mgr Update
	GETS(CSceneMgr)->Update();

	return 0;
}

void CMainGame::Render(void)
{
	//Back Buffer Image Render 
	//Stage1 로 넘어갈때 Stage1_Map 객체에서 사용하는 Stage1_Map.bmp 파일을
	//출력 못한다. 여기서 지금 BackBuffer에 문제가 있는것 같다.
	//여기 부분을 좀 살펴 봐야 될듯.
	HDC BackDC = GETS(CBitMapMgr)->FindImage(L"BackBuffer")->GetMemDC();

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
