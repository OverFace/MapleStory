#pragma once
#include "UI.h"

enum eInvenMode
{
	INVEN_EQUIP,
	INVEN_CONSUME,
	INVEN_ETC,
	INVEN_END
};

class CItem;
class CInven : public CUi
{
public:
	CInven(void);
	virtual	~CInven(void);

private:
	list<CItem*>	m_Inven_ItemList;
	DWORD			m_dwTime;
	bool			m_bStoreInven_Check;
	bool			m_bInvenMode[INVEN_END];

private: //Button
	RECT			m_tInvenMove_Rect;

public: //Getter
	inline list<CItem*>* GetInven_ItemList(void) { return &m_Inven_ItemList; }

public: //Setter
	inline void		Set_InvenItem(CItem* pItem) { m_Inven_ItemList.push_back(pItem); }
	inline void		Set_StoreCheck(bool _bCheck) { m_bStoreInven_Check = _bCheck; }

private:
	void			Inven_Key(void);
	void			Inven_Move(void);
	void			Inven_ViewItem(void);

private:
	void			Save_InvenData(void);
	void			Load_InvenData(void);

public:
	virtual void	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(HDC _dc);
	virtual void	Release(void);
};