#include "stdafx.h"
#include "UI.h"

CUi::CUi(void)
{
	ZeroMemory(&m_ptMouse, sizeof(POINT));
	m_eUiType = UI_END;
}

CUi::~CUi(void)
{
}
