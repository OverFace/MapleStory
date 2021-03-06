#pragma once

class CCollisitionMgr
{
	DECLARE_SINGLETON(CCollisitionMgr);

public:
	bool TileCollision(CObj* p1, TILE* p2, float* pX, float* pY, float _fTempY);
	bool RopeCollision(void);
	bool OverTileCollision(CObj* p1, TILE* p2, float* pX, float* pY, float _fTempY);

public:
	~CCollisitionMgr(void);
};