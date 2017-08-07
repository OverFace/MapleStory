#pragma once

class CCollisitionMgr
{
	DECLARE_SINGLETON(CCollisitionMgr);

public:
	bool BoxCollision(CObj* p1, TILE* p2, float* pX, float* pY);

public:
	~CCollisitionMgr(void);
};