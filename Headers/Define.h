#ifndef Define_h__
#define Define_h__

#define PURE =0
#define SAFE_DELETE(p) if(p){delete p; p = NULL;}

#define PI 3.14159265f
#define To_Radian(angle) (angle * PI / 180.f)

#define DECLARE_SINGLETON(ClassName)			\
	private:									\
		static ClassName*	m_pInstance;		\
	public:										\
		static ClassName*	GetInstance(void)	\
		{										\
			if(m_pInstance == NULL)				\
				m_pInstance = new ClassName;	\
			return m_pInstance;					\
		}										\
		void	DestroyInstance(void)			\
		{										\
			if(m_pInstance)						\
			{									\
				delete m_pInstance;				\
				m_pInstance = NULL;				\
			}									\
		}										\
	private:									\
	ClassName(void);							\
	ClassName(ClassName& r){;}					\

#define IMPLEMENT_SINGLETON(ClassName)				\
		ClassName* ClassName::m_pInstance = NULL;	\

#define GETS(ClassName) ClassName::GetInstance()
#define GETDEV CDevice::GetInstance()

class CObj;
typedef list<CObj*>::iterator OBJITER;

//#define MSG(string) MessageBox(g_hWnd, string, L"System Messge", MB_OK);

#ifdef _DEBUG
#define CLEAR system("cls");
#define MSG(string) cout << string
#define END cout << endl;
#else
#define MSG(string)
#define END
#define CLEAR
#endif

#endif // Define_h_
