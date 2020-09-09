#pragma once
#include "gameobject.h"
#include "minwindef.h"
#include "afxwin.h"
class Clanping :public CGameObject
{
public:
	Clanping(void);
	~Clanping(void);
	BOOL Draw(CDC* pDC, BOOL bPause);
	static BOOL LoadImage();
	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + LANPING_HEIGHT, m_ptPos.y + LANPING_HEIGHT));
	}
	int GetMontion() const
	{
		return m_nMotion;
	}
private:
private:
	static const int LANPING_HEIGHT = 45;
	static CImageList m_Images;
	int    m_nMotion;//方向 1->向下 0->停止 -1->向上
					 //图像索引
	int m_nImgIndex;
	//速度
	int m_V;
	int    m_nWait;//发射延时
};

