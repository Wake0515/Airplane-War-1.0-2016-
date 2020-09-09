#pragma once
#include "gameobject.h"

class CZidan :
	public CGameObject
{
public:
	CZidan(int x, int y);
	~CZidan(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + 10, m_ptPos.y + ZIDAN_HEIGHT));
	}
private:
	static const int ZIDAN_HEIGHT = 20;
	static CImageList m_Images;

};
