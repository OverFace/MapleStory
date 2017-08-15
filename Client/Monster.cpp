#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster(void)
{
	m_eState = MSTATE_END;
	m_ePreState = MSTATE_END;
}

CMonster::~CMonster(void)
{
}
