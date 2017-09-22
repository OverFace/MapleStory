#include "stdafx.h"
#include "UI_QuickSlot.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"

//UI
#include "UI.h"
#include "Skill.h"
#include "Inven.h"
#include "Quick_Slot.h"

typedef list<CQuick_Slot*>::iterator ITER_SLOT;

CUi_QuickSlot::CUi_QuickSlot(void)
{
}

CUi_QuickSlot::~CUi_QuickSlot(void)
{
	Release();
}

void CUi_QuickSlot::Initialize(void)
{
	//Quick Slot Create
	for (int i = 0; i < 8; ++i)
	{
		CQuick_Slot* pSlot = NULL;
		
	}
}

int CUi_QuickSlot::Update(void)
{
	ITER_SLOT iter = m_QuickSlot_List.begin();
	ITER_SLOT iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Update();
	}

	return 0;
}

void CUi_QuickSlot::Render(HDC _dc)
{
	ITER_SLOT iter = m_QuickSlot_List.begin();
	ITER_SLOT iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Render(_dc);
	}
}

void CUi_QuickSlot::Release(void)
{
	ITER_SLOT iter = m_QuickSlot_List.begin();
	ITER_SLOT iter_End = m_QuickSlot_List.end();
	for (iter; iter != iter_End; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_QuickSlot_List.clear();
}
