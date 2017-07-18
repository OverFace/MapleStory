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

#endif // !Struct_h__
