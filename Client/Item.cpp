#include "stdafx.h"
#include "Item.h"

CItem::CItem(void)
{
	ZeroMemory(&m_tItem, sizeof(ITEM));
}

CItem::CItem(TCHAR * pName)
{
	lstrcpy(m_tItem.m_szName, pName);
}

CItem::~CItem(void)
{
}

void CItem::SetItemDescription(TCHAR * pstr)
{
	lstrcpy(m_tItem.m_szDescription, pstr);
}

void CItem::SetItemDescription_Render(HDC _dc, float fx, float fy)
{
	HFONT myFont = CreateFont(11, 5, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"±¼¸²");
	HFONT oldFont = (HFONT)SelectObject(_dc, myFont);

	//Price
	TCHAR szPrice[128] = { 0 };
	_stprintf_s(szPrice, _countof(szPrice), L"%d", m_tItem.m_iPrice);

	SetBkMode(_dc, TRANSPARENT);

	TextOut(_dc, int(fx), int(fy), m_tItem.m_szDescription, lstrlen(m_tItem.m_szDescription));
	TextOut(_dc, int(fx + 15.f), int(fy + 19.f), szPrice, lstrlen(szPrice));

	SelectObject(_dc, oldFont);
}

