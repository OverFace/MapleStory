#include "stdafx.h"
#include "Store_Npc.h"
#include "BitMapMgr.h"
#include "BitMap.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "Store.h"

CStore_Npc::CStore_Npc(void)
{
	ZeroMemory(&m_tNpc_Frame, sizeof(FRAME));
	ZeroMemory(&m_tNpc_Rect, sizeof(RECT));
	
	m_pStore = NULL;
	m_bStoreOpen_Check = false;
	m_dwFrameTime = 0;

}

CStore_Npc::~CStore_Npc(void)
{
	Release();
}

void CStore_Npc::FrameMove(void)
{
	m_tNpc_Frame.iFrameStart = 0;
	m_tNpc_Frame.iFrameEnd = 0;
	m_tNpc_Frame.iYIndex = 0;
	m_tNpc_Frame.dwFrameTime = 600;

	if (m_dwFrameTime + m_tNpc_Frame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tNpc_Frame.iFrameStart;
	}

	if (m_tNpc_Frame.iFrameStart > m_tNpc_Frame.iFrameEnd)
m_tNpc_Frame.iFrameStart = 0;
}

void CStore_Npc::Initialize(void)
{
	m_tInfo.fcx = 135.f;
	m_tInfo.fcy = 130.f;

	m_tNpc_Frame = FRAME(0, 0, 0, 150);
	m_dwFrameTime = GetTickCount();

	//Store
	m_pStore = new CStore;
	m_pStore->Initialize();
	GETS(CObjMgr)->AddObject(OBJ_UI, m_pStore);

	//Rect
	m_tNpc_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) - m_tInfo.fcx / 2);
	m_tNpc_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) + m_tInfo.fcx / 2);
	m_tNpc_Rect.top = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) - m_tInfo.fcy / 2);
	m_tNpc_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) + m_tInfo.fcy / 2);

	m_eRenderType = RENDER_WORLDOBJ;
}

int CStore_Npc::Update(void)
{
	//Npc Frame
	FrameMove();

	//Store Open
	Rect_Check();

	//Store Key
	Store_Key();

	//Rect
	m_tNpc_Rect.left = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) - m_tInfo.fcx / 2);
	m_tNpc_Rect.right = long(m_tInfo.fx + (m_tInfo.fcx / 2.f) + m_tInfo.fcx / 2);
	m_tNpc_Rect.top = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) - m_tInfo.fcy / 2);
	m_tNpc_Rect.bottom = long(m_tInfo.fy + (m_tInfo.fcy / 2.f) + m_tInfo.fcy / 2);

	m_tNpc_Rect.left += g_fScrollX;
	m_tNpc_Rect.right += g_fScrollX;
	m_tNpc_Rect.top += g_fScrollY;
	m_tNpc_Rect.bottom += g_fScrollY;

	CObj::Update();

	return 0;
}

void CStore_Npc::Render(HDC _dc)
{
	TransparentBlt(_dc,
		int(m_tInfo.fx) + g_fScrollX, int(m_tInfo.fy) + g_fScrollY,
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		GETS(CBitMapMgr)->FindImage(L"Store_Npc")->GetMemDC(),
		int(m_tNpc_Frame.iFrameStart * m_tInfo.fcx),
		int(m_tNpc_Frame.iYIndex * m_tInfo.fcy),
		int(m_tInfo.fcx), int(m_tInfo.fcy),
		RGB(0, 0, 255));

	/*
	Rectangle(_dc,
		m_tNpc_Rect.left,
		m_tNpc_Rect.top,
		m_tNpc_Rect.right,
		m_tNpc_Rect.bottom);
	*/
}

void CStore_Npc::Release(void)
{
}

void CStore_Npc::Rect_Check(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(&m_tNpc_Rect, pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bStoreOpen_Check == false)
	{
		((CStore*)m_pStore)->SetVisible();
		m_bStoreOpen_Check = true;
	}	
}

void CStore_Npc::Store_Key(void)
{
	POINT pt;
	pt = CMouse::GetPos();

	if (PtInRect(((CStore*)m_pStore)->GetEscButton_Rect(), pt) && GETS(CKeyMgr)->OnceKeyDown(VK_LBUTTON) && m_bStoreOpen_Check == true)
	{
		((CStore*)m_pStore)->SetUnVisible();
		m_bStoreOpen_Check = false;
	}

	/*
	system("cls");
	cout << "Rect.left : " << ((CStore*)m_pStore)->GetEscButton_Rect()->left << endl;
	cout << "Rect.Right : " << ((CStore*)m_pStore)->GetEscButton_Rect()->right << endl;
	cout << "Rect.Top : " << ((CStore*)m_pStore)->GetEscButton_Rect()->top << endl;
	cout << "Rect.Bottom : " << ((CStore*)m_pStore)->GetEscButton_Rect()->bottom << endl;
	cout << "----------------------------------------" << endl;
	cout << pt.x << endl;
	cout << pt.y << endl;
	*/
}

