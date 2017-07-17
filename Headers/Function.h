#ifndef Function_h__
#define Function_h__

//Factory
//---------------------------------------------------------------------------------
class CObj;
template<typename T>
class CAbstractFactory
{
public:
	static inline CObj* CreateObj(void)
	{
		CObj* p = new T;
		p->Initialize();
		return p;
	}

	CAbstractFactory(void) { ; }
	~CAbstractFactory(void) { ; }
};
//---------------------------------------------------------------------------------

//�Ÿ��� �����ִ� �Լ�
//---------------------------------------------------------------------------------
static inline float GetDistance(INFO* p1, INFO* p2)
{
	float fWidth    = p1->fx - p2->fx;
	float fHeight   = p1->fy - p2->fy;
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fDistance;
}
//---------------------------------------------------------------------------------

//Keyboard �� ���� �Լ�.
//---------------------------------------------------------------------------------
static inline bool GetKey(int iKey)
{
	if (g_bFocus == false)
		return false;

	if (GetAsyncKeyState(iKey))
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------------


#endif // !Function_h__
