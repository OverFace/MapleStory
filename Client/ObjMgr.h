#pragma once
class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)
private:	
	list<CObj*>			m_ObjList[OBJ_END];			//Object Contanier
	vector<CObj*>		m_vecRender[RENDER_END];	//Y Sorting  

private:
	static inline bool  Compare(CObj* pDest, CObj* pSour);

public:
	void				AddObject(eObjType eType, CObj* pObj);
	list<CObj*>*		GetObjList(eObjType eType);

public:
	void				Update(void);
	void				Render(HDC _dc);
	void				Release(void);

public:
	~CObjMgr(void);
};