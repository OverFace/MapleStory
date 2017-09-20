#ifndef Struct_h__
#define Struct_h__

//Object ��ġ & ������ ���� ���� ����ü.
//---------------------------------------------------------------------------------
typedef struct tagInfo
{
	float	fx;				
	float	fy;				
	float	fcx;			
	float	fcy;			
}INFO;
//---------------------------------------------------------------------------------

//Player Stat ���� ����ü
//---------------------------------------------------------------------------------
typedef struct tagStatInfo
{
	TCHAR   m_szName[128];		//�̸�
	TCHAR	m_szJop[128];		//����
	int		m_iLevel;			//����
	int		m_iExp;				//����ġ
	int		m_iHonorLevel;		//������
	int		m_iFameValue;		//��ġ
	TCHAR	m_szGuild[128];		//���
	int		m_iHp;				//HP
	int		m_iMp;				//MP
	int		m_iPopularity;		//�α⵵
	int		m_iSTR;				//��
	int		m_iDEX;				//��ø
	int	    m_iINT;				//����
	int		m_iLUK;				//��
	int		m_iSkillPoint;		//Skill Point
}STAT;
//---------------------------------------------------------------------------------

// Line �� ���� ����ü 
//---------------------------------------------------------------------------------
typedef struct tagLinePoint
{
	float	fx;
	float	fy;
	
	tagLinePoint(void){}
	tagLinePoint(float _fx, float _fy)
		: fx(_fx), fy(_fy){}
}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT tLeft_Point;
	LINEPOINT tRight_Point;

	tagLine(void){}
	tagLine(LINEPOINT _lPoint, LINEPOINT _rPoint)
		:tLeft_Point(_lPoint), tRight_Point(_rPoint){}
}LINE;
//---------------------------------------------------------------------------------

//Frame (Texture Animation) �� ���� ����ü
//---------------------------------------------------------------------------------
typedef struct tagFrame
{
	int		iFrameStart;		//Image X�� ���� �ε���.
	int		iFrameEnd;			//Image X�� ������ �ε���.
	int		iYIndex;			//Image Y�� �ε���.
	DWORD	dwFrameTime;		//Image ��� �ӵ� �����ϱ� ���� ����.
	
	tagFrame(void) { ; }
	tagFrame(int _iFrameStart, int _iFrameEnd, int _iYIndex, DWORD _dwFrameTime)
		: iFrameStart(iFrameStart), iFrameEnd(iFrameEnd), iYIndex(iYIndex), dwFrameTime(_dwFrameTime) { ; }
}FRAME;
//---------------------------------------------------------------------------------

//Tile �� ���� ����ü
//---------------------------------------------------------------------------------
typedef struct tagTile
{
	float	fx;
	float	fy;
	float	fcx;
	float	fcy;
	int		iOption;
	int		iDrawID;
}TILE;
//---------------------------------------------------------------------------------

//Item �� ���� ����ü
//---------------------------------------------------------------------------------
typedef struct tagItem
{
	TCHAR		m_szName[128];			//������ �̸�
	TCHAR		m_szDescription[128];	//������ ����.
	int			m_iStr;					//STR
	int			m_iDex;					//DEX
	int			m_iInt;					//INT
	int			m_iLuk;					//LUK
	int			m_iHp;					//HP
	int			m_iMp;					//MP
	int			m_iPrice;				//PRICE
	int			m_iSalePrice;			//SALE PRICE
	int			m_iCount;				//�Һ� ������ COUNT ��
	eItemType	m_eType;				//Ÿ��
	eEquipType  m_eEquip_Type;			//������ ���� ������ Ÿ��
	DWORD		m_dwOption;				//������ �ֱ� ���� �ɼǰ�.
	DWORD		m_dwInven_SlotNumber;	//Inven�� Slot ��ȣ.
	DWORD		m_dwEquip_Status;		//Equipâ�� ���� ���� üũ.
}ITEM;
//---------------------------------------------------------------------------------

//TCHAR �˻�� ����� ���ڿ� �� �ϱ� ���� Compare ����ü
//---------------------------------------------------------------------------------
struct CStringCompare
{
	const TCHAR* m_pString;
	explicit CStringCompare(const TCHAR* pKey)
		: m_pString(pKey) {
		;
	}
	~CStringCompare() { ; }

	template<typename T>
	bool operator()(T data)
	{
		return !lstrcmp(data.first, m_pString);
	}
};
//---------------------------------------------------------------------------------

//Slot
//---------------------------------------------------------------------------------
typedef struct tagSlot
{
	RECT	tRect;
	INFO	tInfo;
	ITEM	tItem;
}SLOT;
//---------------------------------------------------------------------------------

//SKILL
//---------------------------------------------------------------------------------
typedef struct tagSkill
{
	TCHAR			m_szName[128];			//��ų �̸�
	TCHAR			m_szDescription[128];	//��ų ����
	float			m_fSkill_Att;			//��ų ���ݷ�
	int				m_iSkill_Level;			//��ų ����
	eCutDown_Key	m_eSkill_CutDownKey;	//��ų ����� ���尪.
}SKILL;
//---------------------------------------------------------------------------------
#endif // !Struct_h__
