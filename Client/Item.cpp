#include "stdafx.h"
#include "Item.h"

CItem::CItem(void)
{
	ZeroMemory(&m_tItem, sizeof(ITEM));
}

CItem::~CItem(void)
{
}

