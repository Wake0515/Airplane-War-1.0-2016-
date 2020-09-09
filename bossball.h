#pragma once
#include "GameObject.h"

class Cbossball :public CGameObject
{
public:
	Cbossball(int x, int y, int nMontion, int nn);
	~Cbossball(void);

	BOOL Draw(CDC* pDC, BOOL bPause);

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BOSSBALL_HEIGHT, m_ptPos.y + BOSSBALL_HEIGHT));
	}
private:
	static const int BOSSBALL_HEIGHT = 60;
	static CImageList m_Images;
	int    m_nMotion;
	int n;
};

