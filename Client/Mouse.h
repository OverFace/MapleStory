#pragma once

class CMouse
{
public:
	CMouse(void);
	~CMouse(void);

public:
	static POINT GetPos(void)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		return pt;
	}

	static void Render(HDC _dc)
	{
		POINT pt = GetPos();
		Ellipse(_dc, pt.x - 5, pt.y - 10, pt.x + 10, pt.y + 10);
	}
};
