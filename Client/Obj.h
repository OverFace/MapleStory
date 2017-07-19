#pragma once
class CObj
{
public:
	CObj(void);
	virtual ~CObj(void);

protected:
	RECT				m_Rect;
	INFO				m_tInfo;
	bool				m_bDead;
	float				m_fRadius;
	float				m_fAngle;
	float				m_fSpeed;
	static POINT		m_ptScroll;
	eRenderType			m_eRenderType;

public:	//Get
	inline eRenderType  GetRenderType(void) { return m_eRenderType; }
	inline bool			GetDead(void) { return m_bDead; }
	inline INFO*		GetInfo(void) { return &m_tInfo; }
	inline RECT*        GetRect(void) { return &m_Rect; }
	inline float		GetRadius(void) { return m_fRadius; }

public:	//Set
	inline void			SetDead(void) { m_bDead = true; }
	inline void			SetInfo(INFO& rInfo) { m_tInfo.fx = rInfo.fx; m_tInfo.fy = rInfo.fy; m_tInfo.fcx = rInfo.fcx; m_tInfo.fcy = rInfo.fcy; }
	inline void			SetPos(float _fx, float _fy) { m_tInfo.fx = _fx; m_tInfo.fy = _fy; }
	inline void			SetSize(float _fcx, float _fcy) { m_tInfo.fcx = _fcx; m_tInfo.fcy = _fcy; }
	inline void			SetRadius(float _fRadius) { m_fRadius = _fRadius; }
	inline void			SetAngle(float _fAngle) { m_fAngle = _fAngle; }
	inline void			SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Render(HDC _dc)PURE;
	virtual void	    Release(void)PURE;
};