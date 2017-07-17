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

#endif // !Struct_h__
