#ifndef Struct_h__
#define Struct_h__

//Object 위치 & 사이즈 값을 위한 구조체.
//---------------------------------------------------------------------------------
typedef struct tagInfo
{
	float	fx;				
	float	fy;				
	float	fcx;			
	float	fcy;			
}INFO;
//---------------------------------------------------------------------------------

//Player Stat 정보 구조체
//---------------------------------------------------------------------------------
typedef struct tagStatInfo
{
	TCHAR   m_szName[128];		//이름
	TCHAR	m_szJop[128];		//직업
	int		m_iLevel;			//레벨
	int		m_iExp;				//경험치
	int		m_iHonorLevel;		//명예레벨
	int		m_iFameValue;		//명성치
	TCHAR	m_szGuild[128];		//길드
	int		m_iHp;				//HP
	int		m_iMp;				//MP
	int		m_iPopularity;		//인기도
	int		m_iSTR;				//힘
	int		m_iDEX;				//민첩
	int	    m_iINT;				//지능
	int		m_iLUK;				//운
	int		m_iSkillPoint;		//Skill Point
}STAT;
//---------------------------------------------------------------------------------

// Line 을 위한 구조체 
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

//Frame (Texture Animation) 을 위한 구조체
//---------------------------------------------------------------------------------
typedef struct tagFrame
{
	int		iFrameStart;		//Image X축 시작 인덱스.
	int		iFrameEnd;			//Image X축 마지막 인덱스.
	int		iYIndex;			//Image Y축 인덱스.
	DWORD	dwFrameTime;		//Image 재생 속도 조절하기 위한 변수.
	
	tagFrame(void) { ; }
	tagFrame(int _iFrameStart, int _iFrameEnd, int _iYIndex, DWORD _dwFrameTime)
		: iFrameStart(iFrameStart), iFrameEnd(iFrameEnd), iYIndex(iYIndex), dwFrameTime(_dwFrameTime) { ; }
}FRAME;
//---------------------------------------------------------------------------------

//Tile 을 위한 구조체
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

//Item 을 위한 구조체
//---------------------------------------------------------------------------------
typedef struct tagItem
{
	TCHAR		m_szName[128];			//아이템 이름
	TCHAR		m_szDescription[128];	//아이템 설명.
	int			m_iStr;					//STR
	int			m_iDex;					//DEX
	int			m_iInt;					//INT
	int			m_iLuk;					//LUK
	int			m_iHp;					//HP
	int			m_iMp;					//MP
	int			m_iPrice;				//PRICE
	int			m_iSalePrice;			//SALE PRICE
	int			m_iCount;				//소비 아이템 COUNT 값
	eItemType	m_eType;				//타입
	eEquipType  m_eEquip_Type;			//장착을 위한 아이템 타입
	DWORD		m_dwOption;				//조건을 주기 위한 옵션값.
	DWORD		m_dwInven_SlotNumber;	//Inven의 Slot 번호.
	DWORD		m_dwEquip_Status;		//Equip창의 착용 상태 체크.
}ITEM;
//---------------------------------------------------------------------------------

//TCHAR 검사시 제대로 문자열 비교 하기 위한 Compare 구조체
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
	TCHAR			m_szName[128];			//스킬 이름
	TCHAR			m_szDescription[128];	//스킬 설명
	float			m_fSkill_Att;			//스킬 공격력
	int				m_iSkill_Level;			//스킬 레벨
	eCutDown_Key	m_eSkill_CutDownKey;	//스킬 단축기 저장값.
}SKILL;
//---------------------------------------------------------------------------------
#endif // !Struct_h__
